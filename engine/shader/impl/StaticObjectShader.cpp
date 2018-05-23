#include "StaticObjectShader.h"

StaticObjectShader::StaticObjectShader() : ShaderProgram(R"(D:\C++\LearnCPP\engine\shader\src\static_object)", { "position" })
{
    storeUniforms(&projection, &view, &model);
}