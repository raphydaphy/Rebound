#version 400 core

in vec2 pass_uvs;

uniform sampler2D tex;

out vec4 out_color;

void main()
{
    out_color = vec4(texture(tex, pass_uvs).rgb, 1);
}