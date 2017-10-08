//
// Created by 罗其平 on 9/28/17.
//

#ifndef FIRST3D_CAMERA_H
#define FIRST3D_CAMERA_H


#include "Geometry.h"
#include "Vector.h"

class Camera {
public:
    Camera(Point position, Vector3 lookDirection, GLfloat near, GLfloat far);

private:
    Point mPosition;
    Vector3 mLookDirection;
    GLfloat mNear, mFar;
};


#endif //FIRST3D_CAMERA_H
