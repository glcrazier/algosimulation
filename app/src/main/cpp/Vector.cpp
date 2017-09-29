//
// Created by 罗其平 on 9/28/17.
//

#include "Vector.h"

GLfloat dot(Vector3& v1, Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void Vector3::normalize() {
    GLfloat length = length();
    x = x / length;
    y = y / length;
    z = z / length;
}

Vector3 cross(Vector3& v1, Vector3& v2) {
    return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}