#version 330 core
precision highp float;

// uniform vec2 mousePos; // Mouse position passed from the application
uniform float time; // Time variable passed from the application
in vec3 FragPos;
// in vec3 color;
void main() {
  gl_FragColor = vec4((1+sin(time))/2,0,(1+cos(time)/2),1.0f);
}

