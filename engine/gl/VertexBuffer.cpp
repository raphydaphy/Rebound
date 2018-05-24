#include "VertexBuffer.hpp"

VertexBuffer::VertexBuffer() = default;

VertexBuffer::VertexBuffer(GLenum type)
{
    glGenBuffers(1, &id);
    this->type = type;
}

VertexBuffer VertexBuffer::bind()
{
    glBindBuffer(type, id);
    return *this;
}

VertexBuffer VertexBuffer::unbind()
{
    glBindBuffer(type, 0);
    return *this;
}

VertexBuffer VertexBuffer::store(const void *data, int size)
{
    glBufferData(type, size, data, GL_STATIC_DRAW);
    return *this;
}

void VertexBuffer::del()
{
    glDeleteBuffers(1, &id);
}


