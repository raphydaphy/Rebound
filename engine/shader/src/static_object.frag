#version 400 core

in vec2 pass_uvs;
in vec3 pass_normal;
in vec3 pass_light_vector;
in vec3 pass_camera_vector;
in float pass_visibility;

uniform sampler2D tex;
uniform vec3 light_color;
uniform vec3 light_attenuation;
uniform vec3 sky_color;

out vec4 out_color;

void main()
{
    vec3 unit_normal = normalize(pass_normal);
    vec3 unit_camera_vector = normalize(pass_camera_vector);

    vec3 diffuse = vec3(0);

    // per light:
        float distance = length(pass_light_vector);
        float att_factor = light_attenuation.x + (light_attenuation.y * distance) + (light_attenuation.z * distance * distance);
        vec3 unit_light_vector = normalize(pass_light_vector);

        float light_angle = dot(unit_normal, unit_light_vector);
        float brightness = max(light_angle, 0.2);

        diffuse = diffuse + (brightness * light_color) / att_factor;

    diffuse = max(diffuse, 0.2);

    vec4 texture_color = texture(tex, pass_uvs);

    if (texture_color.a < 0.5)
    {
        discard;
    }

    out_color = vec4(diffuse, 1) * texture_color;
    out_color = mix(vec4(sky_color, 1), out_color, pass_visibility);
}