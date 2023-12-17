#version 330 core
precision highp float;

uniform vec2 mousePos; // Mouse position passed from the application
uniform float time; // Time variable passed from the application
in vec3 FragPos;
vec3 rgb;


void main() {
    vec2 fragCoord = FragPos.xy;

    // Define a small range around (0,0) to check
    float radius = 0.05; // Adjust as needed

    // Check if the current fragment is within the range of (0,0)
    if ((mousePos.x*mousePos.x + mousePos.y*mousePos.y) <= radius) {
        // Color the pixels around (0,0)
        gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red color, adjust as needed
    } else {
        // Color other pixels
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0); // Black color, adjust as needed
    }
}
