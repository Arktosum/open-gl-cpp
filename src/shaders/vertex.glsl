#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aColor;

uniform mat4 MVP;

out vec3 color;
out vec2 texCoord;
void main() {
    // gl_Position =  projection*view * model * vec4(aPos,1.0);
    gl_Position = MVP*vec4(aPos,1.0);
    color = aColor;
    texCoord = aTex;
}