#include "StaticObjectShader.h"

StaticObjectShader::StaticObjectShader() : ShaderProgram("C:\\Users\\HEN0017\\CLionProjects\\OpenGlCPP\\engine\\shader\\src\\static_object", { "position" })
{
    storeUniforms({});
}