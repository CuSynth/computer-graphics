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

uniform bool uniform_texture_map_enabled;
uniform bool uniform_texture_night_map_enabled;
uniform bool uniform_normal_map_enabled;

uniform highp sampler2D uniform_texture;
uniform highp sampler2D uniform_texture_night;
uniform highp sampler2D uniform_normal_texture;

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
    vec3 T = normalize(cross(vec3(0,0,1), normal.xyz));
    vec3 B = normalize(cross(normal.xyz, T));
    mat3 TBN = mat3(T, B, normal);
    
    
    if (uniform_normal_map_enabled)
    {
        N = texture(uniform_normal_texture, texturePosition.xy).xyz;
        N = 2.0f*N-1.0f;
        N = TBN * N;
        N = normalize((transpose(inverse(object_transformation)) * vec4(N, 1.0f)).xyz);
    }
    else
    {
        N = normal.xyz;
        N = normalize((transpose(inverse(object_transformation)) * vec4(N, 1.0f)).xyz);
    }


    vec4 day_light = vec4(0,0,0,1);
    vec4 night_light = vec4(0,0,0,1);
    vec4 light = phong_light();
    float k = length(light.xyz);

    day_light = (uniform_texture_map_enabled?1:0)*(texture(uniform_texture, texturePosition.xy) * light);
    night_light = (uniform_texture_night_map_enabled?1:0)*(texture(uniform_texture_night, texturePosition.xy)*vec4((vec3(1,1,1)-light.xyz), 1.0f));

    if (uniform_texture_map_enabled || uniform_texture_night_map_enabled)
    {
        diffuseColor = vec4(mix(night_light.xyz, day_light.xyz, k), 1.0f);
    }
    else
    {
        diffuseColor = color * phong_light();
    }
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
