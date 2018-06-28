#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec3 color;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 light_positions[4];
uniform vec3 light_colors[4];
uniform vec3 light_attenuations[4];

uniform sampler2D tex;

out float visibility;

out vec3 diffuse;
out vec4 texture_color;

const float fog_density = 0.007;
const float fog_gradient = 10;

void main()
{
    vec4 world_position = model * vec4(position, 1);
    vec4 relative_position = view * world_position;
    gl_Position = projection * relative_position;

    vec3 actual_normal = (model * vec4(normal, 0)).xyz;

    vec3 camera_vector = (inverse(view) * vec4(0, 0, 0, 1)).xyz - world_position.xyz;
    visibility = clamp(exp(-pow((length(relative_position.xyz)*fog_density), fog_gradient)), 0, 1);

    vec3 unit_normal = normalize(actual_normal);
    vec3 unit_camera_vector = normalize(camera_vector);

    diffuse = vec3(0);

    for (int light = 0; light < 4; light++)
    {
        vec3 light_vector = light_positions[light] - world_position.xyz;

        float distance = length(light_vector);
        float att_factor = light_attenuations[light].x + (light_attenuations[light].y * distance) + (light_attenuations[light].z * distance * distance);
        vec3 unit_light_vector = normalize(light_vector);

        float light_angle = dot(unit_normal, unit_light_vector);
        float brightness = max(light_angle, 0.2);

        diffuse = diffuse + (brightness * light_colors[light]) / att_factor;
    }
    diffuse = max(diffuse, 0.2);

    texture_color = vec4(color, 1);
}