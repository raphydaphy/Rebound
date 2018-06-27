#ifndef REBOUND_STATICOBJECTSHADER_H
#define REBOUND_STATICOBJECTSHADER_H

#include "../ShaderProgram.hpp"
#include "../../scene/Light.hpp"

class StaticShader: public ShaderProgram
{
public:
    StaticShader(const std::string &vertex, const std::string &fragment, std::initializer_list<const GLchar *> attributes);
    UniformMatrix projection = UniformMatrix("projection");
    UniformMatrix view = UniformMatrix("view");
    UniformMatrix model = UniformMatrix("model");
    UniformVector3 sky_color = UniformVector3("sky_color");
    void loadLight(Light light, unsigned int id);
protected:
    UniformVector3Array light_positions = UniformVector3Array("light_positions", 4);
    UniformVector3Array light_colors = UniformVector3Array("light_colors", 4);
    UniformVector3Array light_attenuations = UniformVector3Array("light_attenuations", 4);
};

class StaticTexturedShader: public StaticShader
{
public:
    StaticTexturedShader();
};

class StaticColoredShader: public StaticShader
{
public:
    StaticColoredShader();
};

#endif