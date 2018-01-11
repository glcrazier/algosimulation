//
// Created by 罗其平 on 07/01/2018.
//

#include "Scene.h"
#include "Camera.h"

Scene* SceneBuilder::create() {
    if (!validate()) {
        return nullptr;
    }
    Scene *scene = new Scene(mApp);
    scene->mHeight = mHeight;
    scene->mWidth = mWidth;
    scene->mFragmentShaderName = mFragmentShaderPath;
    scene->mVertexShaderName = mVertexShaderPath;
    return scene;
}

bool SceneBuilder::validate() {
    if (mWidth < 0.0f || mHeight < 0.0f) {
        return false;
    }
    if (!mVertexShaderPath) {
        return false;
    }

    if (!mFragmentShaderPath) {
        return false;
    }

    if (!mApp) {
        return false;
    }
    return true;
}

Scene::Scene(android_app *app):
        mApp(app)
        , mVertexShader(app, GL_VERTEX_SHADER)
        , mFragmentShader(app, GL_FRAGMENT_SHADER) {

}

Scene::~Scene() {
    if (mProgram) {
        glDeleteProgram(mProgram);
    }
    if (mVboIds != nullptr) {
        glDeleteBuffers(mVboNum, mVboIds);
        delete[] mVboIds;
        mVboIds = nullptr;
        mVboNum = 0;
    }
    if (!mCamera) {
        delete mCamera;
        mCamera = nullptr;
    }
}

bool Scene::setup() {
    if (!mVertexShader.loadShader(mVertexShaderName)
            || !mFragmentShader.loadShader(mFragmentShaderName)) {
        return false;
    }

    mProgram = glCreateProgram();
    if (!mProgram) {
        return false;
    }

    glAttachShader(mProgram, mVertexShader.getShader());
    glAttachShader(mProgram, mFragmentShader.getShader());

    glLinkProgram(mProgram);

    GLint linked = 0;
    glGetProgramiv(mProgram, GL_LINK_STATUS, &linked);

    if (!linked) {
        return false;
    }
    return true;
}

void Scene::render() {
    if (!mProgram) {
        return ;
    }
    glUseProgram(mProgram);

    if (!mVboIds) {
        mVboNum = 2;
        mVboIds = new GLuint[mVboNum];
        glGenBuffers(mVboNum, mVboIds);


        float *vertices = new float[255];//FIXME
        short *indices = new short[255];
        size_t sizeFloat = sizeof(float);
        size_t sizeShort = sizeof(short);
        size_t totalNumVertex = 0;
        size_t totalNumIndex = 0;
        for (std::vector<Shape*>::const_iterator iter = mShapes.begin(); iter != mShapes.end(); iter++) {
            size_t numVertex = 0;
            float* v = (*iter)->vertices(numVertex);
            memcpy(vertices + totalNumVertex * sizeFloat, v, numVertex * sizeFloat);
            totalNumVertex += numVertex;
            size_t numIndex = 0;
            short* s = (*iter)->vertexIndices(numIndex);
            memcpy(indices + sizeShort * totalNumIndex, s, numIndex * sizeShort);
            totalNumIndex += numIndex;
        }

        glBindBuffer(GL_ARRAY_BUFFER, mVboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, totalNumVertex * sizeFloat, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIds[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalNumIndex * sizeShort, indices, GL_STATIC_DRAW);

        mTotalNumIndices = totalNumIndex;
        mTotalNumVertices = totalNumVertex;

    }

    glBindBuffer(GL_ARRAY_BUFFER, mVboIds[0]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

//    glVertexAttrib3f(1, 1.0f, 0.0f, 0.0f);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mVboIds[1]);
    glDrawElements(GL_TRIANGLE_STRIP, mTotalNumIndices, GL_UNSIGNED_SHORT, 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Scene::addShape(Shape *shape) {
    mShapes.push_back(shape);
}

void Scene::setPerspectiveCamera(Point pos
        , Vector3 lookDirection
        , Vector3 upDirection
        , float near
        , float far) {
    mCamera = new Camera(pos, lookDirection, upDirection, near, far, 5.0f * mWidth/mHeight, 5.0f);
    if (mProgram) {
        glUseProgram(mProgram);
        GLint location = glGetUniformLocation(mProgram, "gMatViewProj");
        glUniformMatrix4fv(location, 1, GL_TRUE, mCamera->getMatrixData());
    }
}