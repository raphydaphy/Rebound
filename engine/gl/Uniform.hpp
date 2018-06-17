#ifndef LEARNCPP_UNIFORM_H
#define LEARNCPP_UNIFORM_H

#include <iostream>
#include <GL/gl3w.h>
#include "../../lib/glm/glm/gtc/matrix_transform.hpp"
#include <string>
#include <vector>
#include <initializer_list>

class Uniform
{
public:
    explicit Uniform(std::string name);
    virtual void store(GLuint program);
    GLint getLocation();
    const GLchar *getName();
private:
    const GLchar *name;
    GLint location = 0;
};

class UniformMatrix : public Uniform
{
public:
    using Uniform::Uniform;
    void load(glm::mat4 value);
};

class UniformVector3 : public Uniform
{
public:
    using Uniform::Uniform;
    void load(glm::vec3 value);
};

class UniformVector3Array : public Uniform
{
public:
    UniformVector3Array(std::string, int size);
    void store(GLuint program) override;
    void load(const std::initializer_list<glm::vec3> &attributes);
    void load(glm::vec3 vec, int id);
private:
    std::vector<UniformVector3*> vectors;
};

#endif
