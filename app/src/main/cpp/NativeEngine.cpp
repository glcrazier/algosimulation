//
// Created by 罗其平 on 17/2/23.
//

#include "NativeEngine.h"
#include <GLES3/gl3.h>
#include <EGL/eglext.h>

static void handle_app_cmd(struct android_app *app, int32_t cmd) {
    NativeEngine *engine = (NativeEngine *) app->userData;
    if (engine != NULL) {
        engine->HandleAppCmd(cmd);
    }
}

NativeEngine::NativeEngine(struct android_app *app): mIsVisible(false), mHasWindow(false),
                                                     mVertexShaderLoader(app, GL_VERTEX_SHADER),
                                                     mFragShaderLoader(app, GL_FRAGMENT_SHADER)
{
    mApp = app;
    mApp->onAppCmd = handle_app_cmd;
    mApp->userData = this;
}

void NativeEngine::HandleAppCmd(int32_t cmd) {
    switch (cmd) {
        case APP_CMD_INIT_WINDOW:
            mHasWindow = true;
            break;
        case APP_CMD_TERM_WINDOW:
            break;
        case APP_CMD_START:
            mIsVisible = true;
            break;
        case APP_CMD_STOP:
            mIsVisible = false;
            break;
        case APP_CMD_DESTROY:
            DestroyRenderer();
            break;
    }
}

void NativeEngine::Run() {
    while (1) {
        int events;
        struct android_poll_source *source;
        while (ALooper_pollAll(IsAnimating() ? 0 : -1, NULL, &events, (void **) &source) > 0) {
            if (source != NULL) {
                source->process(mApp, source);
            }
            if (mApp->destroyRequested) {
                return ;
            }
        }
        if (IsAnimating()) {
            RenderFrame();
        }
    }
}

bool NativeEngine::InitRenderer() {
    if (mEGLDisplay != EGL_NO_DISPLAY && mEGLSurface != EGL_NO_SURFACE
            && mEGLContext != EGL_NO_CONTEXT) {
        return true;
    }
    mEGLDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (mEGLDisplay == EGL_NO_DISPLAY) {
        LOG("NO EGL Display");
        return false;
    }

    if (EGL_FALSE == eglInitialize(mEGLDisplay, 0, 0)) {
        return false;
    }

    const EGLint attribs[] = {
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT_KHR,
            EGL_NONE
    };

    EGLint numConfigs, format;

    if (EGL_FALSE == eglChooseConfig(mEGLDisplay, attribs, &mEGLConfig, 1, &numConfigs)) {
        return false;
    }

    if (EGL_FALSE == eglGetConfigAttrib(mEGLDisplay, mEGLConfig, EGL_NATIVE_VISUAL_ID, &format)) {
        return false;
    }

    ANativeWindow_setBuffersGeometry(mApp->window, 0, 0, format);

    mEGLSurface = eglCreateWindowSurface(mEGLDisplay, mEGLConfig, mApp->window, NULL);
    if (mEGLSurface == EGL_NO_SURFACE) {
        return false;
    }

    const EGLint attribList[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };

    mEGLContext = eglCreateContext(mEGLDisplay, mEGLConfig, EGL_NO_CONTEXT, attribList);
    if (EGL_NO_CONTEXT == mEGLContext) {
        return false;
    }

    if (EGL_FALSE == eglMakeCurrent(mEGLDisplay, mEGLSurface, mEGLSurface, mEGLContext)) {
        return false;
    }

    eglQuerySurface(mEGLDisplay, mEGLSurface, EGL_WIDTH, &mWidth);
    eglQuerySurface(mEGLDisplay, mEGLSurface, EGL_HEIGHT, &mHeight);

    if (!mVertexShaderLoader.loadShader("vertex.glsl")) {
        LOG("unable to load vertex shader.");
        return false;
    }
    if (!mFragShaderLoader.loadShader("fragment.glsl")) {
        LOG("unable to load fragment shader.");
        return false;
    }

    mProgram = glCreateProgram();
    if (mProgram == 0) {
        return false;
    }

    glAttachShader(mProgram, mVertexShaderLoader.getShader());
    glAttachShader(mProgram, mFragShaderLoader.getShader());

    glLinkProgram(mProgram);

    GLint linked;

    glGetProgramiv(mProgram, GL_LINK_STATUS, &linked);

    if (!linked) {
        LOG("unable to link program.");
        glDeleteProgram(mProgram);
        return false;
    }

    glViewport(0, 0, mWidth, mHeight);

    glUseProgram(mProgram);




    return true;
}

void NativeEngine::DestroyRenderer() {


    mVertexShaderLoader.unload();
    mFragShaderLoader.unload();

    glDeleteProgram(mProgram);

    eglMakeCurrent(mEGLDisplay, EGL_NO_SURFACE, EGL_NO_CONTEXT, EGL_NO_CONTEXT);
    if (mEGLContext != EGL_NO_CONTEXT) {
        eglDestroyContext(mEGLDisplay, mEGLContext);
        mEGLContext = EGL_NO_CONTEXT;
    }

    if (mEGLSurface != EGL_NO_SURFACE) {
        eglDestroySurface(mEGLDisplay, mEGLSurface);
        mEGLSurface = EGL_NO_SURFACE;
    }

    if (mEGLDisplay != EGL_NO_DISPLAY) {
        eglTerminate(mEGLDisplay);
        mEGLDisplay = EGL_NO_DISPLAY;
    }

}

void NativeEngine::RenderFrame() {
    if (!InitRenderer()) {
        DestroyRenderer();
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    //let's build a cubic.
    //vertices, transforms, colors
    //
    //    e - - - f
    //  / |      /|
    // a -| - - b |
    // |  h - - - g
    // | /      |/
    // d - - - -c
    GLfloat vertices[] = {
          0.0f, 0.5f, 0.0f,
          -0.5f, -0.5f, 0.0f,
          0.5f, -0.5f, 0.0f
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, 3);
    //bind vertex data
//    GLuint vbo;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) / sizeof(GLfloat), vertices, GL_STATIC_DRAW);
//    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //build a frustum matrix


//    glDeleteBuffers(1, &vbo);





    eglSwapBuffers(mEGLDisplay, mEGLSurface);
}




