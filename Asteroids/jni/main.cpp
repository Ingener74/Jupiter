#include <cstring>
#include <memory>

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

#include <glm/glm.hpp>

#include <Engine/Engine.h>
using namespace ndk_game;

const char *TAG = "Asteroids";
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))

class AndLog: public Log::ILog
{
public:
    AndLog()
    {
    }
    virtual ~AndLog()
    {
    }

    virtual void Error(const std::string& message) throw ()
    {
        LOGE("%s", message.c_str());
    }
    virtual void Debug(const std::string& message) throw ()
    {
        LOGD("%s", message.c_str());
    }

private:
};

struct saved_state
{
    float angle;
    int32_t x;
    int32_t y;
};

struct engine
{
    struct android_app* app;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
    struct saved_state state;
};

/*
 * Game objects
 */

Scene::Ptr startScene;
Scene::Ptr mainScene;

IDrawEngine::Ptr drawEngine;
Scene::Ptr currentScene;

static int engine_init_display(struct engine* engine)
{
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RED_SIZE,   8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE,  8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 8,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_NONE, EGL_NONE };

    EGLint w, h, dummy, format;
    EGLint numConfigs;
    EGLConfig config;
    EGLSurface surface;
    EGLContext context;

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);
    eglChooseConfig(display, attribs, &config, 1, &numConfigs);
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(engine->app->window, 0, 0, format);

    surface = eglCreateWindowSurface(display, config,
            static_cast<EGLNativeWindowType>(engine->app->window), NULL);

    EGLint contextAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2,
            EGL_NONE
    };
    context = eglCreateContext(display, config, NULL, contextAttr);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
    {
        LOGW("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);


    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;
    engine->state.angle = 0;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, w, h);

    /*
     * 1. Start screen
     *
     */

    try
    {
        Log::pushLog(std::make_shared<AndLog>());
        Log() << "Load resources...";

        Log() << "View port " << w << " x " << h;

        glm::mat4 ortho = glm::ortho<float>(-w/2, w/2, -h/2, h/2, -100, 100);

        drawEngine = std::make_shared<GLES20Engine>(
                std::make_shared<SimpleShaderLoader>(
                        "uniform   mat4  uMVP;"
                        "attribute vec4  aPOS;"
                        "attribute vec2  aTEX;"
                        "varying   vec2  vTEX;"
                        "void main(){"
                        "    gl_Position = uMVP * aPOS;"
                        "    vTEX = aTEX;"
                        "}",

                        "precision mediump float;"
                        "varying vec2      vTEX;"
                        "uniform sampler2D uTEX;"
                        "void main(){"
                        "    gl_FragColor = texture2D(uTEX, vTEX);"
                        "}"
                        ), ortho);

        mainScene = std::make_shared<Scene>();

        /*
         * Create start scene
         */
        startScene = std::make_shared<Scene>();

        auto background = std::make_shared<Sprite>(
                Texture::create(std::make_shared<AssetTextureLoader>(engine->app, "images/bg.png")),
                std::make_shared<RectSpriteLoader>(w, w, 0, 0, 1, 0, 1)
        );
        startScene->objects.push_back(background);

        float startButtonW = w * 0.7, startButtonH = w * 0.4;
        auto startButton = std::make_shared<Sprite>(
                Texture::create(std::make_shared<AssetTextureLoader>(engine->app, "images/start.png")),
                std::make_shared<RectSpriteLoader>(startButtonW, startButtonH, 1, 0, 0.91, 1, 0.4)
                );
        startScene->objects.push_back(startButton);

        float shipW = w * 0.2f, shipH = w * 0.2f;
        auto ship = std::make_shared<Sprite>(
                Texture::create(std::make_shared<AssetTextureLoader>(engine->app, "images/ship.png")),
                std::make_shared<RectSpriteLoader>(shipW, shipH, 2, 0, 0.5, 0, 0.5)
                );
        startScene->objects.push_back(ship);

        /*
         *
         *           1
         *           0 R
         *
         *
         *          0 0
         *
         *
         * 2                   3
         * -R -R               R -R
         */
        float R = 100.3f, rV[]{
                0.f, R, 1.f,   0.1f, 0.4f,
                -R, -R, 1.f,   0.2f, 0.5f,
                R, -R, 1.f,    0.1f, 0.2f
        };
        auto rock1 = std::make_shared<Sprite>(
                Texture::create(std::make_shared<AssetTextureLoader>(engine->app, "images/rocks.png")),
                std::make_shared<SimpleSpriteLoader>(rV, 3)
                );
//        startScene->objects.push_back(rock1);

        currentScene = startScene;

        /*
         *
         */
//        class BattleShip: public GameObject
//        {
//        public:
//            BattleShip()
//            {
//            }
//            virtual ~BattleShip()
//            {
//            }
//
//            virtual void update(double elapsed) throw (std::runtime_error)
//            {
//                Log() << "Battle ship update elapsed = " << elapsed;
//            }
//            virtual void input(int x, int y) throw (std::runtime_error){
//                Log() << "Battle ship input";
//            }
//
//        private:
//        };
//
//        class Rock : public GameObject{
//        public:
//            Rock(){
//            }
//            virtual ~Rock(){
//            }
//
//            virtual void update(double elapsed) throw (std::runtime_error){
//                Log() << "Rock update elapsed = " << elapsed;
//            }
//            virtual void input(int x, int y) throw (std::runtime_error){
//                Log() << "Rock input";
//            }
//
//        private:
//        };
//
//        class Animate {
//        public:
//            Animate(){
//            }
//            virtual ~Animate(){
//            }
//
//            using UpdateCallback = std::function<void(double)>;
//
//            Animate& operator<<(UpdateCallback updateCallback)
//            {
//                callback.push_back(updateCallback);
//                return *this;
//            }
//
//            void animateAll()
//            {
//                for(auto &a: callback){
//                    a(0.001);
//                }
//            }
//
//        private:
//            std::list<UpdateCallback> callback;
//        };
//        BattleShip ship;
//        Rock rock;
//        Animate anim;
//
//        anim << std::bind(&BattleShip::update, &ship, std::placeholders::_1)
//                << std::bind(&Rock::update, &rock, std::placeholders::_1);
//
//        anim.animateAll();

        Log() << "done";
    }
    catch (std::exception const & e)
    {
        Log(ERROR) << "Load resource error: " << e.what();
    }

    return 0;
}

static void engine_draw_frame(struct engine* engine)
{
    if (engine->display == NULL)
    {
        return;
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
     * here animate all objects, textures,
     */

    Log() << "draw all";
    if(drawEngine)
        drawEngine->draw(currentScene);

    eglSwapBuffers(engine->display, engine->surface);
}

static void engine_term_display(struct engine* engine)
{
    Log() << "close Engine";

    drawEngine.reset();
    mainScene.reset();
    currentScene.reset();

    Log() << "Engine closed";

    if (engine->display != EGL_NO_DISPLAY)
    {
        eglMakeCurrent(engine->display, EGL_NO_SURFACE, EGL_NO_SURFACE,
        EGL_NO_CONTEXT);
        if (engine->context != EGL_NO_CONTEXT)
        {
            eglDestroyContext(engine->display, engine->context);
        }
        if (engine->surface != EGL_NO_SURFACE)
        {
            eglDestroySurface(engine->display, engine->surface);
        }
        eglTerminate(engine->display);
    }
    engine->animating = 0;
    engine->display = EGL_NO_DISPLAY;
    engine->context = EGL_NO_CONTEXT;
    engine->surface = EGL_NO_SURFACE;
}

static int32_t engine_handle_input(struct android_app* app, AInputEvent* event)
{
    Log() << "Input event: ";

//    int x = AMotionEvent_getRawX(event, )
//
//    if(AMotionEvent_getAction(event) == AMOTION_EVENT_ACTION_DOWN){
//
//    }

    return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
    struct engine* engine = (struct engine*) app->userData;
    switch (cmd)
    {
    case APP_CMD_SAVE_STATE:
        engine->app->savedState = new saved_state;
        *((struct saved_state*) engine->app->savedState) = engine->state;
        engine->app->savedStateSize = sizeof(struct saved_state);
        break;
    case APP_CMD_INIT_WINDOW:
        if (engine->app->window != NULL)
        {
            engine_init_display(engine);
            engine_draw_frame(engine);
        }
        break;
    case APP_CMD_TERM_WINDOW:
        engine_term_display(engine);
        break;
    case APP_CMD_GAINED_FOCUS:
        break;
    case APP_CMD_LOST_FOCUS:
        engine->animating = 0;
        engine_draw_frame(engine);
        break;
    }
}

void android_main(struct android_app* state)
{
    struct engine engine;

    app_dummy();

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;

    if (state->savedState != NULL)
    {
        engine.state = *(struct saved_state*) state->savedState;
    }

    while (1)
    {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL,
                &events, (void**) &source)) >= 0)
        {
            if (source != NULL)
            {
                source->process(state, source);
            }

            if (state->destroyRequested != 0)
            {
                engine_term_display(&engine);
                return;
            }
        }

        if (engine.animating)
        {
            engine.state.angle += .01f;
            if (engine.state.angle > 1)
            {
                engine.state.angle = 0;
            }
            engine_draw_frame(&engine);
        }
    }
}
