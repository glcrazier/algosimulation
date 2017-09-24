//
// Created by 罗其平 on 9/23/17.
//

#include "ShaderLoader.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

using namespace std;
GLuint ShaderLoader::loadShader(std::string assetName) {

    mShader = glCreateShader(mType);
    if (mShader == 0) {
        return 0;
    }

    AAsset *asset = AAssetManager_open(mApp->activity->assetManager,
                                       assetName.c_str(), AASSET_MODE_BUFFER);
    if (asset) {
        off_t sourceLength = AAsset_getLength(asset);
        if (sourceLength > 0) {
            char *buf = (char *) malloc(sizeof(off_t) * sourceLength);
            char *offset = buf;
            int readBytes = 0;
            while ((readBytes = AAsset_read(asset, offset, sourceLength)) > 0) {
                offset += readBytes;
            }

            glShaderSource(mShader, 1, (const GLchar *const *) buf, NULL);
            glCompileShader(mShader);

            GLint compiled;
            glGetShaderiv(mShader, GL_COMPILE_STATUS, &compiled);
            if (!compiled) {
                GLint len = 0;
                glGetShaderiv(mShader, GL_INFO_LOG_LENGTH, &len);
                if (len > 0) {
                    char* log = (char *) malloc(sizeof(char) * len);
                    glGetShaderInfoLog(mShader, len, NULL, log);
                    free(log);
                }
                glDeleteShader(mShader);
                mShader = 0;
            }

            free(buf);
            return mShader;
        }
    }

    return 0;
}

ShaderLoader::ShaderLoader(android_app *app, GLenum type) : mApp(app), mType(type) {

}

void ShaderLoader::unload() {
    if (mShader != 0) {
        glDeleteShader(mShader);
    }
    mShader = 0;
}

ShaderLoader::~ShaderLoader() {
    unload();
}