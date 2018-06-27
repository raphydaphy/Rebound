#ifndef REBOUND_LOADER_H
#define REBOUND_LOADER_H

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
    ModelData(std::vector<glm::vec3> verticesArray, std::vector<glm::vec3> normalsArray);
    std::vector<glm::vec3> verticesArray;
    std::vector<glm::vec3> normalsArray;
};

struct TexturedModelData : public ModelData
{
    TexturedModelData(std::vector<glm::vec3> verticesArray, std::vector<glm::vec3> normalsArray, std::vector<glm::vec2> texturesArray);
    std::vector<glm::vec2> texturesArray;
};

struct ColoredModelData : public ModelData
{
    ColoredModelData(std::vector<glm::vec3> verticesArray, std::vector<glm::vec3> normalsArray, std::vector<glm::vec3> colorsArray);
    std::vector<glm::vec3> colorsArray;
};

namespace core
{
    TexturedModelData loadOBJ(std::string spath);
    void loadPNG(std::vector<unsigned char> &buffer, std::string sfilename);
    void setResourceDirectory(std::string dir);
    std::string getResourceDirectory();
}

#endif