#ifndef REBOUND_MARCHINGCUBESGENERATOR_H
#define REBOUND_MARCHINGCUBESGENERATOR_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <memory>
#include "Terrain.hpp"

namespace marching
{
    void generateMesh(std::vector<std::vector<std::vector<TerrainVoxel>>> voxels, unsigned int width, unsigned int height, unsigned int depth, int worldY,
                      std::vector<glm::vec3> *vertices, std::vector<glm::vec3> *normals, std::vector<glm::vec3> *colors);
    void setSurface(float surface);
}

#endif