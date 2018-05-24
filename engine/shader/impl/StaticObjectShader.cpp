#include "StaticObjectShader.h"

StaticObjectShader::StaticObjectShader() : ShaderProgram(R"(C:\Users\HEN0017\CLionProjects\OpenGlCPP\engine\shader\src\static_object)", { "position" })
{
    storeUniforms(&projection, &view, &model);
}