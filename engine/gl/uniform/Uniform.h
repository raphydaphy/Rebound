#ifndef LEARNCPP_UNIFORM_H
#define LEARNCPP_UNIFORM_H

#include <iostream>
#include <GL/gl3w.h>

class Uniform
{
public:
    explicit Uniform(GLchar *name);
    void store(GLuint program);
    GLint getLocation();
private:
    GLchar *name;
    GLint location;
};

#endif