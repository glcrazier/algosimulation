//
// Created by 罗其平 on 9/28/17.
//

#include "Vector.h"

float dot(Vector3& v1, Vector3& v2) {
    float r = 0;
    for (int i = 0; i < 3; ++i) {
        r += (v1.v[i] * v2.v[i]);
    }
    return r;
}

void Vector3::normalize() {
    GLfloat l = length();
    for (int i = 0; i < 3; ++i) {
        v[i] /= l;
    }
}

Vector3 operator*(const Vector3& v, float f) {
    return Vector3(v.v[0] * f, v.v[1] * f, v.v[2] * f);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.v[0] - v2.v[0], v1.v[1] - v2.v[1], v1.v[2] - v2.v[2]);
}

Vector3 normalize(const Vector3& v) {
    float len = v.length();
    return Vector3(v.v[0]/len, v.v[1]/len, v.v[2]/len);
}

Vector3& Vector3::scale(float x, float y, float z) {
    v[0] *= x;
    v[1] *= y;
    v[2] *= z;
    return *this;
}

Vector3 cross(const Vector3& v1, const Vector3& v2) {
    return Vector3(v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1],
                   v1.v[2] * v2.v[0] - v1.v[0] * v2.v[2],
                   v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0]);
}