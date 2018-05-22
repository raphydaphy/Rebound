#ifndef LEARNCPP_STATICOBJECTSHADER_H
#define LEARNCPP_STATICOBJECTSHADER_H

#include "../ShaderProgram.h"

class StaticObjectShader: public ShaderProgram
{
public:
    StaticObjectShader();
    UniformMatrix projection = UniformMatrix("projection");
    UniformMatrix view = UniformMatrix("view");
    UniformMatrix model = UniformMatrix("model");
};

#endif