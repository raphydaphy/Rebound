#include "Vertex.hpp"

Vertex::Vertex(int index, glm::vec3 position)
{
    this->index = index;
    this->position = position;
}

glm::vec3 Vertex::getPosition()
{
    return position;
}

int Vertex::getIndex()
{
    return index;
}

int Vertex::getTexCoordIndex()
{
    return texCoordIndex;
}

int Vertex::getNormalIndex()
{
    return normalIndex;
}

void Vertex::setTexCoordIndex(int texCoordIndex)
{
    this->texCoordIndex = texCoordIndex;
}

void Vertex::setNormalIndex(int normalIndex)
{
    this->normalIndex = normalIndex;
}