//
// Created by 罗其平 on 9/28/17.
//

#ifndef FIRST3D_CAMERA_H
#define FIRST3D_CAMERA_H


#include "Geometry.h"
#include "Vector.h"
#include "Matrix.h"
class Camera {
public:
    Camera(Point& position, Vector3& lookDirection, Vector3& upDirection
            , float near, float far, float aspectRatio);

private:
    Matrix4x4 mFrustum;
};


#endif //FIRST3D_CAMERA_H
