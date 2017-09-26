#include <android_native_app_glue.h>
#include "NativeEngine.h"


void android_main(struct android_app* app) {

    app_dummy();

    NativeEngine *engine = new NativeEngine(app);

    engine->Run();

    delete engine;

}

