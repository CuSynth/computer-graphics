#version 460 
//VERTEX SHADER

uniform highp mat4 view;
uniform highp mat4 object_transformation;

in highp vec4 attr_pos;
in highp vec4 attr_normal;
in highp vec4 attr_texture_pos;
in lowp vec4 attr_color;

out highp vec4 position;
out highp vec4 normal;
out highp vec4 texturePosition;
out lowp vec4 color;

uniform highp sampler2D uniform_texture;
uniform highp sampler2D uniform_normal_texture;

void main(void)
{   
    
    position = object_transformation * attr_pos;
    normal = normalize(attr_normal);
    color = attr_color;
    texturePosition = attr_texture_pos;
    gl_Position = view * position;
};
