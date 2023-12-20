#version 330 core
precision highp float;

uniform vec2 mousePos; // Mouse position passed from the application
uniform float time; // Time variable passed from the application
in vec3 FragPos;
void main() {
  gl_FragColor = vec4(1,0,0,1.0);
}

