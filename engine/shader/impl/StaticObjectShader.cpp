#include "StaticObjectShader.hpp"

StaticObjectShader::StaticObjectShader() : ShaderProgram(R"(../engine/shader/src/static_object)", { "position", "uvs", "normal" })
{
    storeUniforms(&projection, &view, &model, &light_position, &light_color, &light_attenuation, &sky_color);
}