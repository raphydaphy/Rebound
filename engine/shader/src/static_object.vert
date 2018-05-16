#version 400 core

in vec2 position;

void main()
{
    gl_Position = vec4(position.xy, 0, 1);
}