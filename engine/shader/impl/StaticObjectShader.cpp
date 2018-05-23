#include "StaticObjectShader.h"

StaticObjectShader::StaticObjectShader() : ShaderProgram(R"(engine/shader/src/static_object)", { "position" })
{
    storeUniforms(&projection, &view, &model);
}
