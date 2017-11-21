//
// Created by 罗其平 on 11/1/17.
//

#include "Transform.h"


void Transform::translate(float x, float y, float z) {
    mTransformMatrix.m[0][3] += x;
    mTransformMatrix.m[1][3] += y;
    mTransformMatrix.m[2][3] += z;
}

Matrix4x4 Transform::createTransformFromVectors(Vector3 &u, Vector3 &v, Vector3 &w) {
    Matrix4x4 m = Matrix4x4();
    m.m[0][0] = u.x();
    m.m[0][1] = u.y();
    m.m[0][2] = u.z();
    m.m[1][0] = v.x();
    m.m[1][1] = v.y();
    m.m[1][2] = v.z();
    m.m[2][0] = w.x();
    m.m[2][1] = w.y();
    m.m[2][2] = w.z();

    return m;
}

void Transform::applyMatrix(Matrix4x4& matrix) {
    mTransformMatrix = matrix * mTransformMatrix;
}

void Transform::scale(float x, float y, float z) {
    mTransformMatrix.m[0][0] *= x;
    mTransformMatrix.m[1][1] *= y;
    mTransformMatrix.m[2][2] *= z;
}

void Transform::applyMatrix(float (*matrix)[4]) {
    Matrix4x4 matrix4x4;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix4x4.m[i][j] = matrix[i][j];
        }
    }

    applyMatrix(matrix4x4);
}


