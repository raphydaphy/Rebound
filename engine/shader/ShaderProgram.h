#ifndef LEARNCPP_SHADERPROGRAM_H
#define LEARNCPP_SHADERPROGRAM_H

#include <GL/gl3w.h>
#include <iostream>
#include <string>
#include <initializer_list>
#include <fstream>
#include <vector>
#include "../gl/uniform/Uniform.h"

class ShaderProgram
{
public:
    ShaderProgram(std::string name, std::initializer_list<const GLchar *> &attributes);
    GLuint loadShader(std::string file, GLenum type);
    const std::string EMPTY_ATTRIBUTE = "EMPTY";
    void storeUniforms(std::initializer_list<Uniform> &uniforms);
    ShaderProgram bind();
    ShaderProgram unbind();
    void cleanup();
protected:
    void bindAttributes(std::initializer_list<const GLchar *> &attributes);
private:
    GLuint program;
    GLuint vertex;
    GLuint fragment;
    GLchar log[512];
    GLint status;
};

#endif