#version 460
//FRAGMENT SHADER

uniform highp vec4 uniform_camera_pos;
uniform highp mat4 object_transformation;

uniform bool uniform_light_ambient_enabled;
uniform float uniform_light_ambient_intensity;
uniform lowp vec4 uniform_light_ambient_color;

uniform bool uniform_light_point_enabled;
uniform float uniform_light_point_intensity;
uniform lowp vec4 uniform_light_point_color;
uniform highp vec4 uniform_light_point_position;

uniform bool uniform_light_directional_enabled;
uniform highp float uniform_light_directional_intensity;
uniform lowp vec4 uniform_light_directional_color;
uniform highp vec4 uniform_light_directional_direction;

uniform bool uniform_light_spotlight_enabled;
uniform highp float uniform_light_spotlight_intensity;
uniform lowp vec4 uniform_light_spotlight_color;
uniform highp vec4 uniform_light_spotlight_position;
uniform highp vec4 uniform_light_spotlight_direction;
uniform highp float uniform_light_spotlight_angle_min;
uniform highp float uniform_light_spotlight_angle_max;

uniform bool uniform_texture0_enabled;
uniform bool uniform_texture1_enabled;
uniform bool uniform_texture2_enabled;
uniform bool uniform_texture3_enabled;

uniform highp sampler2D uniform_texture0;
uniform highp sampler2D uniform_texture1;
uniform highp sampler2D uniform_texture2;
uniform highp sampler2D uniform_texture3;


in highp vec4 position;
in highp vec4 normal;
in lowp vec4 color;
in highp vec4 texturePosition;
out lowp vec4 diffuseColor;

const float ambient_power = 0.2f;
const int specular_power = 100; 

vec3 N;
vec3 V = normalize((uniform_camera_pos-position).xyz);

vec4 phong_light(void);

void main(void)
{
    N = normal.xyz;
    N = normalize((transpose(inverse(object_transformation)) * vec4(N, 1.0f)).xyz);

    //tex0 = (uniform_texture0_enabled?1:1)*(texture2D(uniform_texture0, texturePosition.xy));
    const vec2 scale1 = vec2(0.25f, 0.25f);
    const vec2 scale2 = vec2(1.0f, 1.0f);
    const vec2 scale3 = vec2(1.0f, 1.0f);

    const vec3 tex0 = texture2D(uniform_texture0, texturePosition.xy).xyz; // lines
    const vec3 tex1 = texture2D(uniform_texture1, position.xy/scale1).xyz; // asphalt
    const vec3 tex2 = texture2D(uniform_texture2, position.xy/scale2).xyz; // cracks
    const vec3 tex3 = texture2D(uniform_texture3, position.xy/scale3).xyz; // sand
    vec3 mix_color = vec3(0,0,0);
    
    mix_color += (tex0)*(length(tex2));
    mix_color += (tex3)/10*(1-length(tex2));
    mix_color += tex1*9/10*(1-length(tex2));

    //else    
    diffuseColor = vec4(mix_color, 1.0f) * phong_light();
};

vec4 phong_light_abstract(vec3 N, vec3 V, vec3 L, vec4 color)
{
    float diffused = max(dot(N,L),0);
    float specular = pow(max(dot(N,normalize(L+V)),0), specular_power);
    return (diffused + specular) * color;
}

vec4 phong_light_point(vec4 color, vec4 light_pos)
{
    const float dist = distance(light_pos, position);
    const float inverse_square = 1.0f/((dist*dist)+1.0f);
    return inverse_square * phong_light_abstract(N,V,normalize((light_pos-position).xyz), color);
}

vec4 phong_light_directional(vec4 color, vec4 light_dir)
{
    return phong_light_abstract(N, V, normalize(-light_dir.xyz), color);
}

vec4 phong_light_spotlight(vec4 color, vec4 light_pos, vec4 light_dir, float angle_min, float angle_max)
{
    const vec3 L = normalize((light_pos-position).xyz);
    const float real_angle = abs(acos(dot(normalize(light_dir.xyz), -L))); // radians
    float k = clamp((real_angle-radians(angle_min))/(radians(angle_max-angle_min)), 0.0f, 1.0f);
    return (1-k)*phong_light_point(color, light_pos);
}
    
vec4 phong_light(void)
{
    vec4 result_light_color = vec4(0,0,0,1.0f);
    result_light_color += (uniform_light_ambient_enabled?1:0)*uniform_light_ambient_color * uniform_light_ambient_intensity*ambient_power; 
    result_light_color += (uniform_light_point_enabled?1:0)*uniform_light_point_intensity*phong_light_point(uniform_light_point_color, uniform_light_point_position);
    result_light_color += (uniform_light_directional_enabled?1:0)*uniform_light_directional_intensity*phong_light_directional(uniform_light_directional_color, uniform_light_directional_direction);
    result_light_color += (uniform_light_spotlight_enabled?1:0)*uniform_light_spotlight_intensity*phong_light_spotlight(uniform_light_spotlight_color, uniform_light_spotlight_position, uniform_light_spotlight_direction, uniform_light_spotlight_angle_min, uniform_light_spotlight_angle_max);
    return vec4(result_light_color.xyz, 1.0f);
}