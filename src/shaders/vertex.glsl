#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTex;
layout (location = 2) in vec3 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 color;
out vec2 texCoord;
void main() {
    gl_Position =  view * model * vec4(aPos,1.0);
    FragPos = aPos;
    color = aColor;
    texCoord = aTex;
}