//
// Created by 罗其平 on 07/01/2018.
//

#ifndef FIRST3D_SCENE_H
#define FIRST3D_SCENE_H

#include <vector>
#include "ShaderLoader.h"
#include "Geometry.h"
#include "Vector.h"

class Shape;
class Scene;
class Camera;
class android_app;

class SceneBuilder {
public:
    Scene* create();

    SceneBuilder* setVertexShader(const char* path) {
        mVertexShaderPath = path;
        return this;
    }

    SceneBuilder* setFragmentShader(const char* path) {
        mFragmentShaderPath = path;
        return this;
    }

    SceneBuilder* setWidth(float width) {
        mWidth = width;
        return this;
    }

    SceneBuilder* setHeight(float height) {
        mHeight = height;
        return this;
    }

    SceneBuilder* setAppContext(android_app *app) {
        mApp = app;
        return this;
    }

private:
    float mHeight;
    float mWidth;
    const char* mVertexShaderPath;
    const char* mFragmentShaderPath;
    android_app *mApp;

    bool validate();
};

class Scene {
public:

    void render();

    bool setup();

    ~Scene();

    friend class SceneBuilder;

    void addShape(Shape* shape);

    void setPerspectiveCamera(Point pos, Vector3 lookDirection, Vector3 upDirection, float near, float far);

private:
    float mWidth;
    float mHeight;
    const char* mVertexShaderName;
    const char* mFragmentShaderName;
    Scene(android_app *app);
    std::vector<Shape*> mShapes;
    ShaderLoader mVertexShader;
    ShaderLoader mFragmentShader;
    android_app *mApp;
    GLuint mProgram;
    GLuint* mVboIds;
    size_t mVboNum;
    size_t mTotalNumVertices;
    size_t mTotalNumIndices;
    Camera* mCamera;
};


#endif //FIRST3D_SCENE_H
