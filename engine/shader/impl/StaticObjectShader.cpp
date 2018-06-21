#include "StaticObjectShader.hpp"

StaticObjectShader::StaticObjectShader() : ShaderProgram(R"(../engine/shader/src/static_object)", { "position", "uvs", "normal" })
{
    storeUniforms(&projection, &view, &model, &light_positions, &light_colors, &light_attenuations, &sky_color);

    bind();
    for (int i = 0; i < 4; i++)
    {
        light_attenuations.load(glm::vec3(1, 0, 0), i);
    }
    unbind();
}

void StaticObjectShader::loadLight(Light light, int id)
{
    light_positions.load(light.getPosition(), id);
    light_colors.load(light.getColor(), id);
    light_attenuations.load(light.getAttenuation(), id);
}
