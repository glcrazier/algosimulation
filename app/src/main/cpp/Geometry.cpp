//
// Created by 罗其平 on 9/26/17.
//


#include "Geometry.h"

Cube::Cube(Point &p1, Point &p2) {
    //    e - - - f
    //  / |      /|
    // a -| - - b |
    // |  h - - - g
    // | /      |/
    // d - - - -c
    // a
    mVertices[0] = p1.x < p2.x ? p1.x : p2.x;
    mVertices[1] = p1.y > p2.y ? p1.y : p2.y;
    mVertices[2] = p1.z < p2.z ? p1.z : p2.z;
    // b
    mVertices[3] = p1.x > p2.x ? p1.x : p2.x;
    mVertices[4] = mVertices[1];
    mVertices[5] = mVertices[2];
    // d
    mVertices[6] = mVertices[0];
    mVertices[7] = p1.y < p2.y ? p1.y : p2.y;
    mVertices[8] = mVertices[2];
    // c
    mVertices[9] = mVertices[3];
    mVertices[10] = mVertices[7];
    mVertices[11] = mVertices[2];
    // e
    mVertices[12] = mVertices[0];
    mVertices[13] = mVertices[1];
    mVertices[14] = p1.z > p2.z ? p1.z : p2.z;
    // f
    mVertices[15] = mVertices[3];
    mVertices[16] = mVertices[4];
    mVertices[17] = mVertices[14];
    // h
    mVertices[18] = mVertices[6];
    mVertices[19] = mVertices[7];
    mVertices[20] = mVertices[14];
    // g
    mVertices[21] = mVertices[9];
    mVertices[22] = mVertices[10];
    mVertices[23] = mVertices[14];
}

Sphere::Sphere(float radius, Point &origin) {

}

Rect::Rect(Point p1, Point p2, Point p3, Point p4) {
    size_t i = 0;
    mVertices[i++] = p1.x;
    mVertices[i++] = p1.y;
    mVertices[i++] = p1.z;
    mVertices[i++] = p2.x;
    mVertices[i++] = p2.y;
    mVertices[i++] = p2.z;
    mVertices[i++] = p3.x;
    mVertices[i++] = p3.y;
    mVertices[i++] = p3.z;
    mVertices[i++] = p4.x;
    mVertices[i++] = p4.y;
    mVertices[i++] = p4.z;

    mIndices[0] = 0;
    mIndices[1] = 1;
    mIndices[2] = 2;
    mIndices[3] = 3;
}


short* Rect::vertexIndices(size_t &number) {
    number = 4;
    return mIndices;
}

float* Rect::vertices(size_t &number) {
    number = 12;
    return mVertices;
}