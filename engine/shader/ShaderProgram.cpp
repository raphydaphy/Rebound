#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string name, std::initializer_list<const GLchar *> attributes)
{
    vertex = loadShader(name + ".vert", GL_VERTEX_SHADER);
    fragment = loadShader(name + ".frag", GL_FRAGMENT_SHADER);

    program = glCreateProgram();

    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    bindAttributes(attributes);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE)
    {
        glGetProgramInfoLog(program, 512, nullptr, log);

        std::cout << "Failed to link shader program " << name << std::endl << log << std::endl;

        cleanup();
        exit(1);
    }
}

GLuint ShaderProgram::loadShader(std::string file, GLenum type)
{
    std::ifstream src(file);

    if (!src)
    {
        std::cout << "Unable to locate shader at " << file << std::endl;
        exit(1);
    }

    GLuint id = glCreateShader(type);

    std::string shader;
    std::string line;

    while (std::getline(src, line))
    {
        shader += line + "\n";
    }

    const GLchar *source = shader.c_str();

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
        if (attribute != EMPTY_ATTRIBUTE)
        {
            std::cout << "Bound attribute " << attribute << " with id " << id << std::endl;
            glBindAttribLocation(program, id, attribute);
            std::cout << "got location " << glGetAttribLocation(program, attribute) << std::endl;
        }

        id++;
    }
}

void ShaderProgram::storeUniforms(std::initializer_list<Uniform> uniforms)
{
    for (Uniform uniform : uniforms)
    {
        uniform.store(program);
    }
    glValidateProgram(program);
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