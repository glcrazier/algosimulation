//
// Created by 罗其平 on 9/28/17.
//

#include "Camera.h"

Camera::Camera(Point position, Vector3 lookDirection, GLfloat near, GLfloat far)
        : mPosition(position)
        , mLookDirection(lookDirection)
        , mNear(near)
        , mFar(far)
{

}
