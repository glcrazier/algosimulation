//
// Created by 罗其平 on 9/25/17.
//

#ifndef FIRST3D_BASICSHAPE_H
#define FIRST3D_BASICSHAPE_H

#include <cstdio>

struct Point {
    float x;
    float y;
    float z;

    Point(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};

class Shape {
public:
    virtual float* vertices(size_t& number) = 0;
    virtual short* vertexIndices(size_t& number) = 0;
};

class Rect : public Shape {
public:
    Rect(Point p1, Point p2, Point p3, Point p4);

    float* vertices(size_t& number);

    short * vertexIndices(size_t& number);

private:
    float mVertices[4 * 3];
    short mIndices[4];
};

class Cube {
public:
    Cube(Point& p1, Point& p2);
private:
    float mVertices[24];
};

class Sphere {
public:
    Sphere(float radius, Point& origin);
};

#endif //FIRST3D_BASICSHAPE_H
