#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvs;
layout(location = 2) in vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 pass_uvs;
out vec3 pass_normal;

void main()
{
    pass_uvs = uvs;
    pass_normal = (model * vec4(normal, 0)).xyz;

    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(position, 1);
}