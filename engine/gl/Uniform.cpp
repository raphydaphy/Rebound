#include "Uniform.hpp"
#include <utility>

Uniform::Uniform(std::string name) : name{std::move(name)} { }

void Uniform::store(GLuint program)
{
    location = glGetUniformLocation(program, name.c_str());
    if (location == -1)
    {
        std::cerr << "No uniform variable called " << name << " found in program #" << program << std::endl;
    }
}

GLint Uniform::getLocation()
{
    return this->location;
}

std::string Uniform::getName()
{
    return name;
}

void UniformMatrix::load(glm::mat4 value)
{
    glUniformMatrix4fv(getLocation(), 1, GL_FALSE, &value[0][0]);
}

void UniformVector3::load(glm::vec3 value)
{
    glUniform3fv(getLocation(), 1, &value[0]);
}

UniformVector3Array::UniformVector3Array(std::string name, int size) : Uniform(name)
{
    for (int vec = 0; vec < size; vec++)
    {
        std::string cname = name + "[" + std::to_string(vec) + "]";
        vectors.push_back(std::make_unique<UniformVector3>(cname));
    }
}

void UniformVector3Array::store(GLuint program)
{
    for (auto &vector : vectors)
    {
        vector->store(program);
    }
}

void UniformVector3Array::load(const std::initializer_list<glm::vec3> &attributes)
{
    unsigned int n = 0;
    for (glm::vec3 vec : attributes)
    {
        vectors.at(n)->load(vec);
        n++;
    }
}

void UniformVector3Array::load(glm::vec3 vec, unsigned int id)
{
    vectors.at(id)->load(vec);
}
