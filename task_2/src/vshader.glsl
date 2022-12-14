#version 120

uniform mat4 mvp_matrix;
uniform float t;
uniform float offset_from_face;

attribute vec4 vertex_position;
attribute vec4 vertex_normal;
attribute vec4 vertex_color;

varying vec4 frag_color;

void main()
{
    float factor = (sin(t / 30.0F) + 1.0F) / 2.0F;

    vec3 cube_position_3d = vertex_position.xyz + offset_from_face * vertex_normal.xyz;
    vec3 sphere_position_3d = normalize(cube_position_3d);
    vec3 morphed_position_3d = factor * cube_position_3d + (1.0F - factor) * sphere_position_3d;

    gl_Position = mvp_matrix * vec4(morphed_position_3d, 1.0F);

    frag_color = vertex_color;
}
