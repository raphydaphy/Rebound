#include "StaticShader.hpp"

// TODO: better shader code storage??
static constexpr char static_object_frag[] = "#version 400 core\n"
                                              "\n"
                                              "in float visibility;\n"
                                              "in vec3 diffuse;\n"
                                              "in vec4 texture_color;\n"
                                              "\n"
                                              "uniform vec3 sky_color;\n"
                                              "\n"
                                              "out vec4 out_color;\n"
                                              "\n"
                                              "void main()\n"
                                              "{\n"
                                              "    if (texture_color.a < 0.5)\n"
                                              "    {\n"
                                              "        discard;\n"
                                              "    }\n"
                                              "    out_color = vec4(diffuse, 1) * texture_color;\n"
                                              "    out_color = mix(vec4(sky_color, 1), out_color, visibility);\n"
                                              "}";

static constexpr char static_textured_object_vert[] = "#version 400 core\n"
                                                      "\n"
                                                      "layout(location = 0) in vec3 position;\n"
                                                      "layout(location = 1) in vec3 normal;\n"
                                                      "layout(location = 2) in vec2 uvs;\n"
                                                      "\n"
                                                      "uniform mat4 projection;\n"
                                                      "uniform mat4 view;\n"
                                                      "uniform mat4 model;\n"
                                                      "\n"
                                                      "uniform vec3 light_positions[4];\n"
                                                      "uniform vec3 light_colors[4];\n"
                                                      "uniform vec3 light_attenuations[4];\n"
                                                      "\n"
                                                      "uniform sampler2D tex;\n"
                                                      "\n"
                                                      "out float visibility;\n"
                                                      "\n"
                                                      "out vec3 diffuse;\n"
                                                      "out vec4 texture_color;\n"
                                                      "\n"
                                                      "const float fog_density = 0.007;\n"
                                                      "const float fog_gradient = 10;\n"
                                                      "\n"
                                                      "void main()\n"
                                                      "{\n"
                                                      "    vec4 world_position = model * vec4(position, 1);\n"
                                                      "    vec4 relative_position = view * world_position;\n"
                                                      "    gl_Position = projection * relative_position;\n"
                                                      "\n"
                                                      "    vec3 actual_normal = (model * vec4(normal, 0)).xyz;\n"
                                                      "\n"
                                                      "    vec3 camera_vector = (inverse(view) * vec4(0, 0, 0, 1)).xyz - world_position.xyz;\n"
                                                      "    visibility = clamp(exp(-pow((length(relative_position.xyz)*fog_density), fog_gradient)), 0, 1);\n"
                                                      "\n"
                                                      "    vec3 unit_normal = normalize(actual_normal);\n"
                                                      "    vec3 unit_camera_vector = normalize(camera_vector);\n"
                                                      "\n"
                                                      "    diffuse = vec3(0);\n"
                                                      "\n"
                                                      "    for (int light = 0; light < 4; light++)\n"
                                                      "    {\n"
                                                      "        vec3 light_vector = light_positions[light] - world_position.xyz;\n"
                                                      "\n"
                                                      "        float distance = length(light_vector);\n"
                                                      "        float att_factor = light_attenuations[light].x + (light_attenuations[light].y * distance) + (light_attenuations[light].z * distance * distance);\n"
                                                      "        vec3 unit_light_vector = normalize(light_vector);\n"
                                                      "\n"
                                                      "        float light_angle = dot(unit_normal, unit_light_vector);\n"
                                                      "        float brightness = max(light_angle, 0.2);\n"
                                                      "\n"
                                                      "        diffuse = diffuse + (brightness * light_colors[light]) / att_factor;\n"
                                                      "    }\n"
                                                      "    diffuse = max(diffuse, 0.2);\n"
                                                      "\n"
                                                      "    texture_color = texture(tex, uvs);\n"
                                                      "}";

static constexpr char static_colored_object_vert[] = "#version 400 core\n"
                                                     "\n"
                                                     "layout(location = 0) in vec3 position;\n"
                                                     "layout(location = 1) in vec3 normal;\n"
                                                     "layout(location = 2) in vec3 color;\n"
                                                     "\n"
                                                     "uniform mat4 projection;\n"
                                                     "uniform mat4 view;\n"
                                                     "uniform mat4 model;\n"
                                                     "\n"
                                                     "uniform vec3 light_positions[4];\n"
                                                     "uniform vec3 light_colors[4];\n"
                                                     "uniform vec3 light_attenuations[4];\n"
                                                     "\n"
                                                     "uniform sampler2D tex;\n"
                                                     "\n"
                                                     "out float visibility;\n"
                                                     "\n"
                                                     "out vec3 diffuse;\n"
                                                     "out vec4 texture_color;\n"
                                                     "\n"
                                                     "const float fog_density = 0.007;\n"
                                                     "const float fog_gradient = 10;\n"
                                                     "\n"
                                                     "void main()\n"
                                                     "{\n"
                                                     "    vec4 world_position = model * vec4(position, 1);\n"
                                                     "    vec4 relative_position = view * world_position;\n"
                                                     "    gl_Position = projection * relative_position;\n"
                                                     "\n"
                                                     "    vec3 actual_normal = (model * vec4(normal, 0)).xyz;\n"
                                                     "\n"
                                                     "    vec3 camera_vector = (inverse(view) * vec4(0, 0, 0, 1)).xyz - world_position.xyz;\n"
                                                     "    visibility = clamp(exp(-pow((length(relative_position.xyz)*fog_density), fog_gradient)), 0, 1);\n"
                                                     "\n"
                                                     "    vec3 unit_normal = normalize(actual_normal);\n"
                                                     "    vec3 unit_camera_vector = normalize(camera_vector);\n"
                                                     "\n"
                                                     "    diffuse = vec3(0);\n"
                                                     "\n"
                                                     "    for (int light = 0; light < 4; light++)\n"
                                                     "    {\n"
                                                     "        vec3 light_vector = light_positions[light] - world_position.xyz;\n"
                                                     "\n"
                                                     "        float distance = length(light_vector);\n"
                                                     "        float att_factor = light_attenuations[light].x + (light_attenuations[light].y * distance) + (light_attenuations[light].z * distance * distance);\n"
                                                     "        vec3 unit_light_vector = normalize(light_vector);\n"
                                                     "\n"
                                                     "        float light_angle = dot(unit_normal, unit_light_vector);\n"
                                                     "        float brightness = max(light_angle, 0.2);\n"
                                                     "\n"
                                                     "        diffuse = diffuse + (brightness * light_colors[light]) / att_factor;\n"
                                                     "    }\n"
                                                     "    diffuse = max(diffuse, 0.2);\n"
                                                     "\n"
                                                     "    texture_color = vec4(color, 1);\n"
                                                     "}";

void StaticShader::loadLight(Light light, unsigned int id)
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

StaticTexturedShader::StaticTexturedShader() : StaticShader(static_textured_object_vert, static_object_frag, { "position", "normal", "uvs" })
{ }

StaticColoredShader::StaticColoredShader() : StaticShader(static_colored_object_vert, static_object_frag, { "position", "normal", "color" })
{ }