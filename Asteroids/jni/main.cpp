#include <cstring>
#include <memory>

#include <jni.h>
#include <errno.h>

#include <EGL/egl.h>
#include <GLES/gl.h>

#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

//#include <Engine/Engine.h>

const char *TAG = "Android NDK Game";
#define LOGD(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__))
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__))

//class AndLog: public ndk_game::Log::ILog
//{
//public:
//    AndLog()
//    {
//    }
//    virtual ~AndLog()
//    {
//    }
//
//    virtual void Error(const std::string& message) throw ()
//    {
//        LOGE("%s", message.c_str());
//    }
//    virtual void Debug(const std::string& message) throw ()
//    {
//        LOGD("%s", message.c_str());
//    }
//
//private:
//};

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

//using namespace ndk_game;
//Texture::Ptr ballTexture;
//Sprite::Ptr ball;

static int engine_init_display(struct engine* engine)
{
    const EGLint attribs[] =
    {
    EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
    EGL_BLUE_SIZE, 8,
    EGL_GREEN_SIZE, 8,
    EGL_RED_SIZE, 8,
    EGL_NONE };
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
    context = eglCreateContext(display, config, NULL, NULL);

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

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glDisable(GL_DEPTH_TEST);

//    try
//    {
//        Log::pushLog(std::make_shared<AndLog>());
//
//        ballTexture = Texture::create();
//
//        ball = std::make_shared<Sprite>(ballTexture);
//    }
//    catch (std::exception const & e)
//    {
//        LOGE("Init game objects error: %s", e.what());
//    }

    return 0;
}

static void engine_draw_frame(struct engine* engine)
{
    if (engine->display == NULL)
    {
        return;
    }

    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat quad[] =
    {
            0.f, 0.f, 0.5f, 0.2f, 0.4f, 1.f,
            0.f, 10.f, 0.1f, 0.4f, 0.9f, 1.f,
            10.f, 0.f, 0.0f, 1.0f, 0.5f, 1.f
    };

    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glVertexPointer(2, GL_FLOAT, 6, &quad[0]);
//    glTexCoordPointer(2, GL_FLOAT, 4, &quad[2]);
    glColorPointer(4, GL_FLOAT, 6, &quad[2]);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableClientState(GL_VERTEX_ARRAY);
//    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    eglSwapBuffers(engine->display, engine->surface);
}

static void engine_term_display(struct engine* engine)
{
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
