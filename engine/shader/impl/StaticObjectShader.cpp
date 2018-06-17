#include "StaticObjectShader.hpp"

StaticObjectShader::StaticObjectShader() : ShaderProgram(R"(../engine/shader/src/static_object)", { "position", "uvs", "normal" })
{
    std::cout << "called constructor " << std::endl;
    storeUniforms(&projection, &view, &model, &light_positions, /*&light_colors, &light_attenuations,*/ &sky_color);
}

void StaticObjectShader::loadLight(Light light, int id)
{
    light_positions.load(light.getPosition(), id);
   // light_colors.load(light.getColor(), id);
    //light_attenuations.load(light.getAttenuation(), id);
}
