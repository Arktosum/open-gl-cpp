#version 330 core
precision highp float;

// uniform vec2 mousePos; // Mouse position passed from the application
uniform float time; // Time variable passed from the application
in vec3 FragPos;
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main() {
  // gl_FragColor = texture(tex0,texCoord);
  // gl_FragColor = vec4(color.xyz,1.0);
  gl_FragColor = vec4(color.xyz,1.0);
}

