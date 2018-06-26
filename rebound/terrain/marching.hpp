#ifndef MARCHINGCUBESGENERATOR_H
#define MARCHINGCUBESGENERATOR_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>

namespace marching
{
    void generateMesh(std::vector<float> voxels, unsigned int width, unsigned int height, unsigned int depth,
                      std::vector<glm::vec3> *vertices, std::vector<glm::vec3> *normals, std::vector<unsigned int> *indices);
    void setSurface(float surface);
}

#endif