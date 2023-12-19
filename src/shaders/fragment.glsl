#version 330 core
precision highp float;

uniform vec2 mousePos; // Mouse position passed from the application
uniform float time; // Time variable passed from the application
in vec3 FragPos;
void main() {
    int radius = 0.1f; // radius
    float dist = length(FragPos - )
  gl_FragColor = vec4(FragPos.xyz,1.0);
}

