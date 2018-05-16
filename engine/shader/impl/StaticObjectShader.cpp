#include "StaticObjectShader.h"

StaticObjectShader::StaticObjectShader() : ShaderProgram("D:/C++/LearnCPP/engine/shader/src/static_object", { "position" })
{
    storeUniforms({});
}