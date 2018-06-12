#ifndef LEARNCPP_STATICOBJECTSHADER_H
#define LEARNCPP_STATICOBJECTSHADER_H

#include "../ShaderProgram.hpp"

class StaticObjectShader: public ShaderProgram
{
public:
    StaticObjectShader();
    UniformMatrix projection = UniformMatrix("projection");
    UniformMatrix view = UniformMatrix("view");
    UniformMatrix model = UniformMatrix("model");

    UniformVector3 light_position = UniformVector3("light_position");
    UniformVector3 light_color = UniformVector3("light_color");
    UniformVector3 light_attenuation = UniformVector3("light_attenuation");

    UniformVector3 sky_color = UniformVector3("sky_color");
};

#endif