#include "StaticObjectShader.hpp"

StaticObjectShader::StaticObjectShader() : ShaderProgram(R"(../engine/shader/src/static_object)", { "position", "uvs" })
{
    storeUniforms(&projection, &view, &model);
}