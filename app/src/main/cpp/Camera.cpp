//
// Created by 罗其平 on 9/28/17.
//

#include "Camera.h"

Camera::Camera(Point& position, Vector3& lookDirection, Vector3& upDirection, float near, float far,
               float farPlaneWidth, float farPlaneHeight)
{
    mFrustum.translate(-position.x, -position.y, -position.z);

    Vector3 w = normalize(lookDirection) * (-1.0f);

    Vector3 v = upDirection - w * dot(upDirection, w);
    v.normalize();

    Vector3 u = cross(v, w);

    Matrix4x4 m = Transform::createTransformFromVectors(u, v, w);

    mFrustum.applyMatrix(m);

    mFrustum.scale(2.0f / farPlaneWidth, 2.0f / farPlaneHeight, 1.0f / far);

    float d[4][4] = {1.0f, 0.0f, 0.0f, 0.0f,
                     0.0f, 1.0f, 0.0f, 0.0f,
                     0.0f, 0.0f, far / (far - near), near / (far - near),
                     0.0f, 0.0f, -1.0f, 0.0f};
    mFrustum.applyMatrix(d);
}
