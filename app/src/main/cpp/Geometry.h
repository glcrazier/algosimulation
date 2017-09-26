//
// Created by 罗其平 on 9/25/17.
//

#ifndef FIRST3D_BASICSHAPE_H
#define FIRST3D_BASICSHAPE_H

#include <GLES3/gl3.h>

struct Point {
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

class Cube {
public:
    Cube(Point& p1, Point& p2);
private:
    GLfloat mVertices[24];

};

class Sphere {
public:
    Sphere(GLfloat radius, Point& origin);
};

#endif //FIRST3D_BASICSHAPE_H
