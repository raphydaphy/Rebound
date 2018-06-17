#include "Uniform.hpp"

Uniform::Uniform(std::string name)
{
    std::cout << "called uniform constructor" << std::endl;
    this->name = name.c_str();
}

void Uniform::store(GLuint program)
{
    std::cout << "Storing time has arrived for " << getName() << std::endl;
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

const GLchar *Uniform::getName()
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
    std::cout << " calling uniformvector3array constructor " << std::endl;
    for (int vec = 0; vec < size; vec++)
    {
        std::string cname = name + "[" + std::to_string(vec) + "]";
        auto *vector3 = new UniformVector3(cname);

        std::cout << "MAKING uniformVector3 [" << vec << "]:" << vector3->getName() << " --> " << getName() << " @ " << vector3 << std::endl;

        vectors.push_back(vector3);

        std::cout << "CONFIRMING uniformVector3 [" << vec << "]: " << vectors[vec]->getName() << " @ " << vectors[vec] <<  std::endl;
    }
}

void UniformVector3Array::store(GLuint program)
{
    for (int vec = 0; vec < vectors.size(); vec++)
    {
        UniformVector3 *vector = vectors[vec];

        std::cout << "STORING uniformVector3 [" << vec << "]: " << vectors[vec]->getName() << " @ " << vectors[vec] << std::endl;
        vector->store(program);
    }
}

void UniformVector3Array::load(const std::initializer_list<glm::vec3> &attributes)
{
    int n = 0;
    for (glm::vec3 vec : attributes)
    {
        vectors[n]->load(vec);
        n++;
    }
}

void UniformVector3Array::load(glm::vec3 vec, int id)
{
    vectors[id]->load(vec);
}
