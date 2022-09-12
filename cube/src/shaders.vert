attribute highp vec4 posAttr;
attribute lowp vec3 colAttr;
varying lowp vec3 col;
uniform highp mat4 matrix;

void main() {
   col = colAttr;
   gl_Position = matrix * posAttr;
}
