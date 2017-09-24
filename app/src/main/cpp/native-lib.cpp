#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include "NativeEngine.h"

void handle_app_cmd(struct android_app* state, int32_t cmd);

void android_main(struct android_app* app) {

    app_dummy();

    NativeEngine *engine = new NativeEngine(app);

    engine->Run();

    delete engine;


}

void init_display(struct android_app* state);

void handle_app_cmd(struct android_app* state, int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            if (state->window != NULL) {
                init_display(state);
            }
            break;
    }
}

void init_display(struct android_app* state) {
    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_NONE
    };

    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

    eglInitialize(display, 0, 0);

    EGLConfig config;

    EGLint numConfigs;

    EGLint format, width, height;

    eglChooseConfig(display, attribs, &config, 1, &numConfigs);


    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

    ANativeWindow_setBuffersGeometry(state->window, 0, 0, format);

    EGLSurface surface;

    surface = eglCreateWindowSurface(display, config, state->window, NULL);
    EGLContext  context;
    context = eglCreateContext(display, config, NULL, NULL);

    if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE) {
        return ;
    }

    eglQuerySurface(display, surface, EGL_WIDTH, &width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &height);


    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    eglSwapBuffers(display, surface);
}
