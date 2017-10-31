//
// Created by 罗其平 on 10/30/17.
//
#include "Matrix.h"

Matrix4x4& loadIdentity(Matrix4x4& matrix) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix.m[i][j] = i == j ? 1.0f : 0.0f;
        }
    }
    return matrix;
}

Matrix4x4::Matrix4x4() {
    loadIdentity(*this);
}


Matrix4x4::Matrix4x4(float m00, float m01, float m02, float m03, float m10, float m11, float m12,
                     float m13, float m20, float m21, float m22, float m23, float m30, float m31,
                     float m32, float m33) {
    m[0][0] = m00;
    m[0][1] = m01;
    m[0][2] = m02;
    m[0][3] = m03;

    m[1][0] = m10;
    m[1][1] = m11;
    m[1][2] = m12;
    m[1][3] = m13;

    m[2][0] = m20;
    m[2][1] = m21;
    m[2][2] = m22;
    m[2][3] = m23;

    m[3][0] = m30;
    m[3][1] = m31;
    m[3][2] = m32;
    m[3][3] = m33;
}


Matrix4x4& Matrix4x4::translate(float x, float y, float z) {
    this->m[0][3] += x;
    this->m[1][3] += y;
    this->m[2][3] += z;

    return *this;
}

Matrix4x4 operator*(const Matrix4x4 &m1, const Matrix4x4 &m2) {
    Matrix4x4 m;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m.m[i][j] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                m.m[i][j] += (m1.m[i][k] * m2.m[k][j]);
            }
        }
    }
    return m;
}

Matrix4x4 &Matrix4x4::scale(float x, float y, float z) {
    m[0][0] *= x;
    m[1][1] *= y;
    m[2][2] *= z;
    return *this;
}
