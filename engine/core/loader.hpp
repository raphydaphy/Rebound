#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../gl/Vertex.hpp"
#include <glm/glm.hpp>

namespace core
{
    void loadOBJ(std::string path);
}

#endif