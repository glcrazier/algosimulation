//
// Created by 罗其平 on 9/23/17.
//

#ifndef FIRST3D_SHADERLOADER_H
#define FIRST3D_SHADERLOADER_H

#include <cstdio>
#include <android_native_app_glue.h>
#include <string>
#include <GLES3/gl3.h>

class ShaderLoader {
public:
    GLuint loadShader(std::string assetName);

    ShaderLoader(android_app *app, GLenum shaderType);

    void unload();

    ~ShaderLoader();

    GLuint getShader() {
        return mShader;
    }

private:

    android_app* mApp;

    GLuint mShader;
    GLenum mType;
};


#endif //FIRST3D_SHADERLOADER_H
