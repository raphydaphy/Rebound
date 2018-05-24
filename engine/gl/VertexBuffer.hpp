#ifndef LEARNCPP_VERTEXBUFFER_H
#define LEARNCPP_VERTEXBUFFER_H

#include <GL/gl3w.h>
#include <vector>

class VertexBuffer
{
public:
    VertexBuffer();
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