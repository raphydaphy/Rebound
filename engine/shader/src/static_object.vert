#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 light_positions[4];

out vec2 pass_uvs;
out vec3 pass_normal;
out vec3 pass_light_vectors[4];
out vec3 pass_camera_vector;
out float pass_visibility;

const float fog_density = 0.005;
const float fog_gradient = 4;

void main()
{
    vec4 world_position = model * vec4(position, 1);
    vec4 relative_position = view * world_position;
    gl_Position = projection * relative_position;

    pass_uvs = uvs;
    pass_normal = (model * vec4(normal, 0)).xyz;
    for (int light = 0; light < 4; light++)
    {
        pass_light_vectors[light] = light_positions[light] - world_position.xyz;
    }
    pass_camera_vector = (inverse(view) * vec4(0, 0, 0, 1)).xyz - world_position.xyz;
    pass_visibility = clamp(exp(-pow((length(relative_position.xyz)*fog_density), fog_gradient)), 0, 1);
}