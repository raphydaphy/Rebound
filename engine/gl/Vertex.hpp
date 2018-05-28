#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

#define VERTEX_NO_INDEX (-1)

class Vertex
{
public:
    Vertex(int index, glm::vec3 position);

    glm::vec3 getPosition();
    int getIndex();
    int getTexCoordIndex();
    int getNormalIndex();

    void setTexCoordIndex(int texCoordIndex);
    void setNormalIndex(int normalIndex);

private:
    glm::vec3 position;
    int index;
    int texCoordIndex = VERTEX_NO_INDEX;
    int normalIndex = VERTEX_NO_INDEX;
};

#endif