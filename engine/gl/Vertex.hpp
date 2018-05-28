#ifndef VERTEX_H
#define VERTEX_H

#include "../../lib/glm/glm/gtc/matrix_transform.hpp"

#define VERTEX_NO_INDEX (-1)

class Vertex
{
public:
    Vertex(int index, glm::vec3 position);
private:
    glm::vec3 position;
    int texCoordIndex = VERTEX_NO_INDEX;
    int normalIndex = VERTEX_NO_INDEX;
};

#endif