//
// Created by 罗其平 on 9/28/17.
//

#ifndef FIRST3D_VECTOR_H
#define FIRST3D_VECTOR_H

#include <GLES3/gl3.h>
#include <cmath>

class Vector3 {
public:
    Vector3(GLfloat x, GLfloat y, GLfloat z) : x(x), y(y), z(z){

    }

    GLfloat length() {
        return sqrtf(x * x + y * y + z * z);
    }

    void normalize();

    friend GLfloat dot(Vector3& v1, Vector3& v2);
    friend Vector3 cross(Vector3& v1, Vector3& v2);
private:
    GLfloat x, y, z;
};

GLfloat dot(Vector3& v1, Vector3& v2);

Vector3 cross(Vector3& v1, Vector3& v2);

#endif //FIRST3D_VECTOR_H
