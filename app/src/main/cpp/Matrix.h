//
// Created by 罗其平 on 10/30/17.
//

#ifndef FIRST3D_MATRIX_H
#define FIRST3D_MATRIX_H

#include "Vector.h"

class Matrix4x4 {
public:
    Matrix4x4();

    Matrix4x4(float m00, float m01, float m02, float m03,
                float m10, float m11, float m12, float m13,
                float m20, float m21, float m22, float m23,
                float m30, float m31, float m32, float m33);

    Matrix4x4& translate(float x, float y, float z);

    Matrix4x4& scale(float x, float y, float z);

    friend Matrix4x4& loadIdentity(Matrix4x4& matrix);

    friend Matrix4x4 operator*(const Matrix4x4& m1, const Matrix4x4& m2);
private:
    float m[4][4];
};

#endif //FIRST3D_MATRIX_H
