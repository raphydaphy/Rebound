#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(const std::string &name, std::initializer_list<const GLchar *> attributes) : ShaderProgram(name, name, attributes)
{ }

ShaderProgram::ShaderProgram(const std::string &vertex, const std::string &fragment, std::initializer_list<const GLchar *> attributes)
{
    this->vertex = loadShader(vertex, GL_VERTEX_SHADER);
    this->fragment = loadShader(fragment, GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program, this->vertex);
    glAttachShader(program, this->fragment);

    bindAttributes(attributes);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        glGetProgramInfoLog(program, 512, nullptr, log);

        std::cout << "Failed to link shader program ( " << vertex << " / " << fragment << " )" << std::endl << log << std::endl;

        cleanup();
        exit(1);
    }
}

GLuint ShaderProgram::loadShader(std::string file, GLenum type)
{
    GLuint id = glCreateShader(type);
    const GLchar *source = file.c_str();

    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE)
    {
        glGetShaderInfoLog(id, 512, nullptr, log);

        std::cout << "Failed to compile shader " << file << std::endl << log << std::endl;

        glDeleteShader(id);

        exit(1);
    }

    return id;
}

void ShaderProgram::bindAttributes(std::initializer_list<const GLchar *> attributes)
{
    GLuint id = 0;
    for (const GLchar *attribute : attributes)
    {
        if (attribute != SHADER_EMPTY_ATTRIBUTE)
        {
            glBindAttribLocation(program, id, attribute);
        }

        id++;
    }
}

ShaderProgram ShaderProgram::bind()
{
    glUseProgram(program);
    return *this;
}

ShaderProgram ShaderProgram::unbind()
{
    glUseProgram(0);
    return *this;
}

void ShaderProgram::cleanup()
{
    unbind();

    glDetachShader(program, vertex);
    glDetachShader(program, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    glDeleteProgram(program);
}