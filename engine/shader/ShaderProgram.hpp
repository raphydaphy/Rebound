#ifndef LEARNCPP_SHADERPROGRAM_H
#define LEARNCPP_SHADERPROGRAM_H

#include <GL/gl3w.h>
#include <iostream>
#include <string>
#include <initializer_list>
#include <fstream>
#include <sstream>
#include <vector>
#include "../gl/Uniform.hpp"

class ShaderProgram
{
public:
    ShaderProgram(std::string name, std::initializer_list<const GLchar *> attributes);
    GLuint loadShader(std::string file, GLenum type);
    const std::string EMPTY_ATTRIBUTE = "EMPTY";

    template <typename T>
    void storeUniforms(T *value)
    {
        Uniform *v = value;
        v->store(program);
    }

    template <typename First, typename... Rest>
    void storeUniforms(First *firstValue, Rest*... rest)
    {
        storeUniforms(firstValue);
        storeUniforms(rest...);

        glValidateProgram(program);
    }

    ShaderProgram bind();
    ShaderProgram unbind();
    void cleanup();
protected:
    void bindAttributes(std::initializer_list<const GLchar *> attributes);
private:
    GLuint program;
    GLuint vertex;
    GLuint fragment;
    GLchar log[512];
    GLint status;
};

#endif