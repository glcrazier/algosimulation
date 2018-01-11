//
// Created by 罗其平 on 17/2/23.
//

#include "NativeEngine.h"
#include <GLES3/gl3.h>
#include <EGL/eglext.h>
#include "Camera.h"
#include "Geometry.h"
#include "Vector.h"
#include "Scene.h"

static void handle_app_cmd(struct android_app *app, int32_t cmd) {
    NativeEngine *engine = (NativeEngine *) app->userData;
    if (engine != NULL) {
        engine->HandleAppCmd(cmd);
    }
}

NativeEngine::NativeEngine(struct android_app *app): mIsVisible(false)
        , mHasWindow(false)
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
        default:
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

    glViewport(0, 0, mWidth, mHeight);

    mScene = SceneBuilder()
            .setAppContext(mApp)
            ->setVertexShader("basic.vert")
            ->setFragmentShader("basic.frag")
            ->setWidth(mWidth)
            ->setHeight(mHeight)
            ->create();

    if (!mScene || !mScene->setup()) {
        delete mScene;
        mScene = nullptr;
        return false;
    }

    Rect *rect = new Rect(Point(-0.25f, 0.25f, -0.1f),
                          Point(-0.25f, -0.25f, -0.1f),
                          Point(0.25F, 0.25f, -0.3f),
                          Point(0.25f, -0.25f, -0.1f));
    mScene->addShape(rect);
    mScene->setPerspectiveCamera(Point(0.0f, 0.0f, 0.4f), Vector3(0.0f, 0.0f, -1.0f),
                                 Vector3(0.0f, 1.0f, 0.0f),
                                 0.1f, 3.0f);
    return true;
}

void NativeEngine::DestroyRenderer() {

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

    if (mScene) {
        mScene->render();
    }

    eglSwapBuffers(mEGLDisplay, mEGLSurface);
}




