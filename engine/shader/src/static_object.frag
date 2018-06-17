#version 400 core

in float visibility;
in vec3 diffuse;
in vec4 texture_color;

uniform vec3 sky_color;

out vec4 out_color;

void main()
{
    if (texture_color.a < 0.5)
    {
        discard;
    }
    out_color = vec4(diffuse, 1) * texture_color;
    out_color = mix(vec4(sky_color, 1), out_color, visibility);
}