#ifndef LEARNCPP_VERTEXARRAY_H
#define LEARNCPP_VERTEXARRAY_H

#include <GL/gl3w.h>
#include <initializer_list>
#include <vector>
#include "VertexBuffer.h"

class VertexArray
{
public:
    VertexArray();
    VertexArray bind(const std::initializer_list<GLuint> &attributes);
    VertexArray bind();
    VertexArray unbind(const std::initializer_list<GLuint> &attributes);
    VertexArray unbind();
    VertexArray storeIndices(const GLint indices[], int length);
    VertexArray createAttribute(GLuint index, const void *data, int length, int dimensions);
    int getIndicesLength();
    void del();
    VertexBuffer indices;
private:
    GLuint id;
    std::vector<VertexBuffer> buffers;
    int indicesLength;
};

#endif