#version 150
in vec3 col;
out vec4 outColor;
void main() {
   outColor = vec4(col, 1.0);
}
