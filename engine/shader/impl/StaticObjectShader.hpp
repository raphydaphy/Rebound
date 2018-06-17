#ifndef LEARNCPP_STATICOBJECTSHADER_H
#define LEARNCPP_STATICOBJECTSHADER_H

#include "../ShaderProgram.hpp"
#include "../../scene/Light.hpp"

class StaticObjectShader: public ShaderProgram
{
public:
    StaticObjectShader();
    UniformMatrix projection = UniformMatrix("projection");
    UniformMatrix view = UniformMatrix("view");
    UniformMatrix model = UniformMatrix("model");
    UniformVector3 sky_color = UniformVector3("sky_color");
    void loadLight(Light light, int id);
private:

    //UniformVector3Array light_colors = UniformVector3Array("light_colors", 4);
    //UniformVector3Array light_attenuations = UniformVector3Array("light_attenuations", 4);
    UniformVector3Array light_positions = UniformVector3Array("light_positions", 4);
};

#endif