#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <array>
#include <glm/glm.hpp>

#define VERTEX_NO_INDEX (-1)

struct Vertex
{
    Vertex(int index, glm::vec3 position);
    glm::vec3 position;
    int index;
    int texCoordIndex = VERTEX_NO_INDEX;
    int normalIndex = VERTEX_NO_INDEX;
};

struct Model
{
    Model(std::vector<float> verticesArray, std::vector<float> texturesArray, std::vector<float> normalsArray, std::vector<int> indicesArray);
    std::vector<float> verticesArray;
    std::vector<float> texturesArray;
    std::vector<float> normalsArray;
    std::vector<int> indicesArray;
};

namespace core
{
    Model loadOBJ(std::string path);
}

#endif