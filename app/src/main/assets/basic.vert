#version 300 es
layout(location = 0) in vec4 vPosition;
layout(location = 1) in vec3 aColor;
out vec3 vColor;
void main() {
    gl_Position = vPosition;
    vColor = aColor;
}