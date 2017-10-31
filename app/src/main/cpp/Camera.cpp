//
// Created by 罗其平 on 9/28/17.
//

#include "Camera.h"

Camera::Camera(Point& position, Vector3& lookDirection, Vector3& upDirection, float near, float far, float aspectRatio)
{
    mFrustum.translate(-position.x, -position.y, -position.z);

    Vector3 w = normalize(lookDirection) * (-1.0f);

    Vector3 v = upDirection - w * dot(upDirection, w);
    v.normalize();

    Vector3 u = cross(v, w);

    mFrustum = Matrix4x4(u.x(), u.y(), u.z(), 0,
                         v.x(), v.y(), v.z(), 0,
                         w.x(), w.y(), w.z(), 0,
                         0,         0,     0, 1) * mFrustum;

    //TODO: Finish the remaining part.

}
