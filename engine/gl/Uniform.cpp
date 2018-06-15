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

UniformVector3Array::UniformVector3Array(std::string name, int size) : Uniform(name.c_str())
{
    for (int vec = 0; vec < size; vec++)
    {
        std::string cname = name + "[" + std::to_string(vec) + "]";
        std::cout << cname << std::endl;
        vectors.emplace_back(cname.c_str());
    }
}

void UniformVector3Array::store(GLuint program)
{
    for (UniformVector3 vec : vectors)
    {
        vec.store(program);
    }
}

void UniformVector3Array::load(const std::initializer_list<glm::vec3> &attributes)
{
    int n = 0;
    for (glm::vec3 vec : attributes)
    {
        vectors[n].load(vec);
        n++;
    }
}

void UniformVector3Array::load(glm::vec3 vec, int id)
{
    vectors[id].load(vec);
}
