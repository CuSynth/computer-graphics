#version 110

uniform bool f_phong;

// reflection comonents
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;

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


varying vec3 frag_position;
varying vec3 frag_normal;
varying vec3 frag_color;

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
    if(!f_phong) {
        gl_FragColor = vec4(frag_color, 1.0);
    }
    else {
        /* Model */
        vec3 viewPos = vec3(0.0, 0.0, 0.0);
        vec3 norm = normalize(frag_normal);

        vec3 pointLightDir = (point_pos - frag_position);
        vec3 spotLightDir = (spot_pos - frag_position);

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

        vec3 resultColor = (ambient  +
                       pt_coeff * compute(frag_position, norm, viewPos, pointLightDir, point_col, point_I)   // Point

                       + compute(frag_position, norm, viewPos, n_dir_pos, dir_col, dir_I)     // Dir

                       + spot_angled_coef * spot_coeff * compute(frag_position, norm, viewPos, spotLightDir, spot_col, spot_I)  // Spot
                       ) * frag_color;
        gl_FragColor = vec4(resultColor, 1.0);

    }


}
