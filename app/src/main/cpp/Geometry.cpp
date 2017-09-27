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

Sphere::Sphere(GLfloat radius, Point &origin) {

}
