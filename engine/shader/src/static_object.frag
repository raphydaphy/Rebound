#version 400 core

in vec2 pass_uvs;
in vec3 pass_normal;

uniform sampler2D tex;

out vec4 out_color;

void main()
{
    vec3 unit_normal = normalize(pass_normal);
    vec3 unit_light_vector = normalize(vec3(5, 8, -20));

    float light_angle = dot(unit_normal, unit_light_vector);
    float brightness = max(light_angle, 0.2);

    out_color = brightness * vec4(texture(tex, pass_uvs).rgb, 1);
}