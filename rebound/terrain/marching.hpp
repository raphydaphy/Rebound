#ifndef MARCHINGCUBESGENERATOR_H
#define MARCHINGCUBESGENERATOR_H

#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain.hpp"

namespace marching
{
    void generateMesh(std::vector<TerrainVoxel> voxels, int width, int height, int depth, int worldY,
                      std::vector<glm::vec3> *vertices, std::vector<glm::vec3> *normals, std::vector<glm::vec3> *colors,
                      std::map<glm::vec3, std::vector<glm::vec3>> *triangles);
    void setSurface(float surface);
}

#endif