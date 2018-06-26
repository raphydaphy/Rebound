#include "StaticShader.hpp"

void StaticShader::loadLight(Light light, int id)
{
    light_positions.load(light.getPosition(), id);
    light_colors.load(light.getColor(), id);
    light_attenuations.load(light.getAttenuation(), id);
}

StaticShader::StaticShader(const std::string &vertex, const std::string &fragment, std::initializer_list<const GLchar *> attributes) : ShaderProgram(vertex, fragment, attributes)
{
    storeUniforms(&projection, &view, &model, &light_positions, &light_colors, &light_attenuations, &sky_color);

    bind();
    for (int i = 0; i < 4; i++)
    {
        light_attenuations.load(glm::vec3(1, 0, 0), i);
    }
    unbind();
}

StaticTexturedShader::StaticTexturedShader() : StaticShader(R"(../engine/shader/src/static_textured_object)", R"(../engine/shader/src/static_object)", { "position", "normal", "uvs" })
{ }

StaticColoredShader::StaticColoredShader() : StaticShader(R"(../engine/shader/src/static_colored_object)", R"(../engine/shader/src/static_object)", { "position", "normal", "color" })
{ }