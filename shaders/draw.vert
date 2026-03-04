#version 130

#define PI 3.14159265358979323846
#define LAT_LIMIT 1.4844222297487079667669973978362

attribute float a_index;

uniform sampler2D u_particles;
uniform float u_particles_res;

// Projection
uniform vec4 u_proj_scale; // 0 = left, 1 = right, 2 = bottom, 3 = top (radians)
uniform mat4 u_proj;

varying vec2 v_particle_pos;

// Projection functions
float mercator_to_y(float rad) {
    rad = clamp(rad, -LAT_LIMIT, LAT_LIMIT);
    return log(tan(PI / 4.0 + rad / 2.0));
}

void main() {
    vec4 color = texture2D(u_particles, vec2(
                               fract(a_index / u_particles_res),
                               floor(a_index / u_particles_res) / u_particles_res));

    // decode current particle position from the pixel's RGBA value
    v_particle_pos = vec2(
                color.r / 255.0 + color.b,
                color.g / 255.0 + color.a);

    float lon = mix(u_proj_scale[0], u_proj_scale[1], v_particle_pos.x); // rad
    float lat = mix(u_proj_scale[2], u_proj_scale[3], 1.0 - v_particle_pos.y); // rad
    float mercY = mercator_to_y(lat);

    vec2 pos = vec2(lon, mercY);

    gl_Position = u_proj * vec4(pos, .0, 1.);
    gl_PointSize = 1.0;
}
