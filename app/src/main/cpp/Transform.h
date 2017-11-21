//
// Created by 罗其平 on 11/1/17.
//

#ifndef FIRST3D_TRANSFORM_H
#define FIRST3D_TRANSFORM_H

#include "Matrix.h"
class Transform {
public:
    void translate(float x, float y, float z);
    void applyMatrix(Matrix4x4& matrix);
    void scale(float x, float y, float z);
    void applyMatrix(float matrix[4][4]);

    float* getData() {
        return (float *) mTransformMatrix.m;
    }

    static Matrix<4> createTransformFromVectors(Vector3 &u, Vector3 &v, Vector3 &w);
private:
    Matrix<4> mTransformMatrix;
};


#endif //FIRST3D_TRANSFORM_H
