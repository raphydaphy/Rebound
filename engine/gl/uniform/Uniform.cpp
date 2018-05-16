#include "Uniform.h"

Uniform::Uniform(GLchar *name)
{
    this->name = name;
}

void Uniform::store(GLuint program)
{
    location = glGetUniformLocation(program, this->name);
    if (location == -1)
    {
        std::cerr << "No uniform variable called " << this->name << " found in program #" << program << std::endl;
    }
}

GLint Uniform::getLocation()
{
    return this->location;
}