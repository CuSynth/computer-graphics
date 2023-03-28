#version 110
// view and pos
uniform mat4 projection_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

// reflection comonents
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;


// light sources
uniform vec3 point_pos;
uniform vec3 point_col;
uniform float point_I;


uniform vec3 dir_pos;
uniform vec3 dir_col;
uniform float dir_I;


uniform vec3 spot_pos;
uniform vec3 spot_col;
uniform float spot_I;

uniform vec3 spot_dir;
uniform float spot_phi;
uniform float spot_k;

uniform float P;
uniform float d;
uniform float K;
uniform float specularFactor;


// vertices
attribute vec4 vertex_position;
attribute vec3 vertex_normal;
attribute vec3 vertex_color;


// out
varying vec3 frag_position;
varying vec3 frag_normal;
varying vec3 frag_color;

uniform bool f_phong;


vec3 compute(vec3 v_pos, vec3 v_n, vec3 viewPos, vec3 light_vect, vec3 lightColor, float light_I) {

    /* Diffusive lighting */
    float diff = max(dot(v_n, light_vect), 0.0);
    vec3 diffuse = diffuseColor * diff * diffuseStrength;

    /* Specular blick lighting */
    vec3 viewDir = normalize(viewPos - v_pos);
    vec3 reflectDir = reflect(-light_vect, v_n);
    float spec = pow(max(dot(reflectDir, viewDir), 0.0), specularFactor);
    vec3 specular = specularStrength * spec * specularColor;

    return lightColor * (diffuse + specular) * light_I;
}


void main() {

    mat4 mv_matrix = view_matrix * model_matrix;
    gl_Position = projection_matrix * mv_matrix * vec4(vertex_position.xyz, 1.0);

    vec3 v_position = vec3(mv_matrix * vec4(vertex_position.xyz, 1.0));
    vec3 v_normal = normalize(vec3(mv_matrix * vec4(vertex_normal, 0.0)));



    if(!f_phong) {

        /* Model */
        vec3 viewPos = vec3(0.0, 0.0, 0.0);
        vec3 norm = normalize(v_normal);

        vec3 pointLightDir = (point_pos - v_position);
        vec3 spotLightDir = (spot_pos - v_position);

        /* Ambient lighting */
        vec3 ambient = ambientStrength * ambientColor;

        float spot_coeff = 1.0 / (pow(length(spotLightDir), P) + K);
        float pt_coeff = 1.0 / (pow(length(pointLightDir), P) + K);

        vec3 n_dir_pos = normalize(dir_pos);

        pointLightDir = normalize(pointLightDir);

        spotLightDir = normalize(spotLightDir);
        vec3 n_spot_dir = normalize(spot_dir);

        float spot_angled_coef = dot(n_spot_dir, -spotLightDir);
    //    spot_k = 2;
        spot_angled_coef = max(pow(spot_angled_coef, spot_k), 0.0) * float(spot_angled_coef>spot_phi);

        frag_color = (ambient  +
                       pt_coeff * compute(v_position, norm, viewPos, pointLightDir, point_col, point_I)   // Point

                       + compute(v_position, norm, viewPos, n_dir_pos, dir_col, dir_I)     // Dir

                       + spot_angled_coef * spot_coeff * compute(v_position, norm, viewPos, spotLightDir, spot_col, spot_I)  // Spot
                       ) * vertex_color;
    }
    else {
        frag_color = vertex_color;
        frag_normal = v_normal;
        frag_position = v_position;
    }
}
