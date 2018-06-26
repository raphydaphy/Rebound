#include "VertexArray.hpp"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
    bind();
    indices = VertexBuffer(GL_ELEMENT_ARRAY_BUFFER);
    unbind();
}

VertexArray VertexArray::bind(const std::initializer_list<GLuint> &attributes)
{
    this->bind();

    for (GLuint attribute : attributes)
    {
        glEnableVertexAttribArray(attribute);
    }

    return *this;
}

VertexArray VertexArray::bind()
{
    glBindVertexArray(id);
    return *this;
}

VertexArray VertexArray::unbind(const std::initializer_list<GLuint> &attributes)
{
    this->unbind();

    for (GLuint attribute : attributes)
    {
        glDisableVertexAttribArray(attribute);
    }

    return *this;
}

VertexArray VertexArray::unbind()
{
    glBindVertexArray(0);
    return *this;
}

VertexArray VertexArray::storeIndices(const GLuint indices[], int length)
{
    this->indices.bind().store(indices, length);
    this->indicesLength = length;
    return *this;
}

VertexArray VertexArray::createAttribute(GLuint index, const void *data, int length, int dimensions)
{
    VertexBuffer vbo = VertexBuffer(GL_ARRAY_BUFFER).bind().store(data, length);
    glVertexAttribPointer(index, dimensions, GL_FLOAT, GL_FALSE, 0, nullptr);
    buffers.push_back(vbo);
    return *this;
}

int VertexArray::getIndicesLength()
{
    return this->indicesLength;
}

void VertexArray::del()
{
    bind();

    for (VertexBuffer buffer : buffers)
    {
        buffer.del();
    }

    unbind();
    glDeleteVertexArrays(1, &id);
}