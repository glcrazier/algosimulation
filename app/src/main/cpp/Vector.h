//
// Created by 罗其平 on 9/28/17.
//

#ifndef FIRST3D_VECTOR_H
#define FIRST3D_VECTOR_H

#include <GLES3/gl3.h>
#include <cmath>

class Vector3 {
public:
    Vector3(GLfloat x, GLfloat y, GLfloat z) {
        v[0] = x;
        v[1] = y;
        v[2] = z;
    }

    float length() const {
        return sqrtf(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    void normalize();

    Vector3& scale(float x, float y, float z);

    friend Vector3 normalize(const Vector3& v);
    friend float dot(Vector3& v1, Vector3& v2);
    friend Vector3 cross(const Vector3& v1, const Vector3& v2);
    friend Vector3 operator*(const Vector3& v, float f);
    friend Vector3 operator-(const Vector3& v1, const Vector3& v2);

    float x() {
        return v[0];
    }

    float y() {
        return v[1];
    }

    float z() {
        return v[2];
    }
private:
    float v[3];
};

#endif //FIRST3D_VECTOR_H
