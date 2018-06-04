#version 400 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uvs;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 pass_uvs;

void main()
{
    pass_uvs = uvs;
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(position, 1);
}