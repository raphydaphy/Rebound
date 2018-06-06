#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include "../core/loader.hpp"
#include "../core/pico.hpp"

class Texture
{
public:
    explicit Texture(std::string path);
    Texture bind();
    Texture unbind();
private:
    GLuint id;

    GLsizei width;
    GLsizei height;
};

#endif