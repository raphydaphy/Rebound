#ifndef LEARNCPP_VERTEXBUFFER_H
#define LEARNCPP_VERTEXBUFFER_H

#include <glad/glad.h>
#include <vector>

class VertexBuffer
{
public:
    explicit VertexBuffer(GLenum type);
    VertexBuffer bind();
    VertexBuffer unbind();
    VertexBuffer store(const void *data, int size);
    void del();
private:
    GLuint id;
    GLenum type;
};

#endif