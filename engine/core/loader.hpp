#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <array>
#include <utility>
#include <glm/glm.hpp>

struct ModelData
{
    ModelData(std::vector<glm::vec3> verticesArray, std::vector<glm::vec2> texturesArray, std::vector<glm::vec3> normalsArray, std::vector<int> indicesArray);
    std::vector<glm::vec3> verticesArray;
    std::vector<glm::vec2> texturesArray;
    std::vector<glm::vec3> normalsArray;
    std::vector<int> indicesArray;
};

namespace core
{
    ModelData loadOBJ(std::string spath);
    void loadPNG(std::vector<unsigned char> &buffer, std::string sfilename);
    void setResourceDirectory(std::string dir);
    std::string getResourceDirectory();
}

#endif