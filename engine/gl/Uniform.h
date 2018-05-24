#ifndef LEARNCPP_UNIFORM_H
#define LEARNCPP_UNIFORM_H

#include <iostream>
#include <GL/gl3w.h>
#include "../../lib/glm/glm/gtc/matrix_transform.hpp"

class Uniform
{
public:
    explicit Uniform(const GLchar *name);
    void store(GLuint program);
    GLint getLocation();
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

#endif
