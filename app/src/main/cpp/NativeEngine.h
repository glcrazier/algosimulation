//
// Created by 罗其平 on 17/2/23.
//

#ifndef FIRST3D_NATIVEENGINE_H
#define FIRST3D_NATIVEENGINE_H

#include <android_native_app_glue.h>
#include <EGL/egl.h>
#include <android/log.h>
#include "ShaderLoader.h"

#define LOG(...) ((void)__android_log_print(ANDROID_LOG_DEBUG, "First3D", __VA_ARGS__))

class Scene;
class NativeEngine {
public:
    NativeEngine(struct android_app* app);

    void HandleAppCmd(int32_t cmd);

    void Run();

    bool IsAnimating() {
        return mIsVisible && mHasWindow;
    }

private:
    struct android_app* mApp;
    bool mIsVisible;
    bool mHasWindow;
    EGLDisplay mEGLDisplay;
    EGLConfig  mEGLConfig;
    EGLSurface mEGLSurface;
    EGLContext mEGLContext;
    int mWidth;
    int mHeight;

    bool InitRenderer();

    void DestroyRenderer();

    void RenderFrame();

    Scene* mScene;
};


#endif //FIRST3D_NATIVEENGINE_H
