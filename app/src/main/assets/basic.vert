#version 300 es
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 aColor;
out vec3 vColor;
uniform mat4 gMatViewProj;
void main() {
    gl_Position = gMatViewProj * vPosition;
    //gl_Position = vPosition;
    vColor = gMatViewProj[1].xyz;
}