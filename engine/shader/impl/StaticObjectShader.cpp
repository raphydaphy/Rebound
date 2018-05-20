#include "StaticObjectShader.h"

StaticObjectShader::StaticObjectShader() : ShaderProgram("D:\\C++\\LearnCPP\\engine\\shader\\src\\barebones", { "position" })
{
    storeUniforms({});
}