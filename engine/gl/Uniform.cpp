#include "Uniform.hpp"

Uniform::Uniform(const GLchar *name)
{
    this->name = name;
}

void Uniform::store(GLuint program)
{
    location = glGetUniformLocation(program, name);
    if (location == -1)
    {
        std::cerr << "No uniform variable called " << name << " found in program #" << program << std::endl;
    }
}

GLint Uniform::getLocation()
{
    return this->location;
}

void UniformMatrix::load(glm::mat4 value)
{
    glUniformMatrix4fv(getLocation(), 1, GL_FALSE, &value[0][0]);
}

void UniformVector3::load(glm::vec3 value)
{
    glUniform3fv(getLocation(), 1, &value[0]);
}
