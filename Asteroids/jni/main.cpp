
#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

const char *TAG = "Asteroids";
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))

struct engine
{
    struct android_app* app;

    int animating;
    EGLDisplay display;
    EGLSurface surface;
    EGLContext context;
    int32_t width;
    int32_t height;
};



//#include <Game/GameBuilder.h>
//
//GameBuilder::Ptr game;

#include <Game/Game.h>
using namespace ndk_game;



static int engine_init_display(struct engine* engine)
{
    const EGLint attribs[] =
    {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_RED_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_BLUE_SIZE, 8,
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

    EGLint contextAttr[] =
    {
    EGL_CONTEXT_CLIENT_VERSION, 2,
    EGL_NONE };
    context = eglCreateContext(display, config, NULL, contextAttr);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
    {
        LOGE("Unable to eglMakeCurrent");
        return -1;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &w);
    eglQuerySurface(display, surface, EGL_HEIGHT, &h);

    engine->display = display;
    engine->context = context;
    engine->surface = surface;
    engine->width = w;
    engine->height = h;

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, w, h);

    try
    {
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
        };
        Log::pushLog(std::make_shared<AndLog>());

        Log() << "Creating game";

//        game = std::make_shared<GameBuilder>(
//                engine->app->savedState, engine->app->savedStateSize, w, h, engine->app);

        Game::instance()->startGame(engine->app, w, h);

        engine->animating = 1;

        Log() << "done";
    }
    catch (std::exception const & e)
    {
        Log(ERROR) << "Creating game error: " << e.what();
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
     * here animate and draw our game
     */
    try
    {
        using namespace std::chrono;
        static auto tp = system_clock::now();

        Game::Ptr game = Game::instance();

        auto now = system_clock::now();

        game->getEngine()->animateAll(duration_cast<microseconds>(now - tp).count() / 1000000.0);

        tp = now;

        game->getEngine()->draw();
    }
    catch (const std::exception& e)
    {
        Log() << "draw or animate error: " << e.what();
    }

    eglSwapBuffers(engine->display, engine->surface);
}

static void engine_term_display(struct engine* engine)
{
    Game::reset();

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
    int pc = AMotionEvent_getPointerCount(event);

    for (int i = 0, imax = pc; i < imax; ++i)
    {
        int x = AMotionEvent_getX(event, i);
        int y = AMotionEvent_getY(event, i);

        try
        {

            Game::instance()->getEngine()->inputToAll(x, y);

        }
        catch (const std::exception& e)
        {
            Log() << "Input error: " << e.what();
        }
    }

    return 0;
}

static void engine_handle_cmd(struct android_app* app, int32_t cmd)
{
    struct engine* engine = (struct engine*) app->userData;
    switch (cmd)
    {
        case APP_CMD_SAVE_STATE:
        {
            try
            {
//                Log() << "Saving state";
//
//                auto savedState = game->saveGame();
//
//                Log() << "Check state "
//                        << *(static_cast<int*>(std::get<0>(savedState)));
//
//                engine->app->savedState = std::get<0>(savedState);
//                engine->app->savedStateSize = std::get<1>(savedState);
//
//                Log() << "State saved";
            }
            catch (const std::exception& e)
            {
                Log() << "Saving state error: " << e.what();
            }
            break;
        }

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

    while (1)
    {
        int ident;
        int events;
        struct android_poll_source* source;

        while ((ident = ALooper_pollAll(engine.animating ? /* 0 too small */ 10 : -1, NULL,
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
        engine_draw_frame(&engine);
    }
}
