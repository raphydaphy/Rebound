#include "loader.hpp"

glm::vec3 parseLine(const std::string in)
{
    std::string split[4];
    int i = 0;
    std::stringstream stream(in);

    while (stream.good() && i < 4)
    {
        stream >> split[i];
        i++;
    }

    if (i == 4) // vec3
    {
        return glm::vec3(::atof(split[1].c_str()), ::atof(split[2].c_str()), ::atof(split[3].c_str())); // NOLINT
    } else if (i == 3) // vec2
    {
        return glm::vec3(::atof(split[1].c_str()), ::atof(split[2].c_str()), 0); // NOLINT
    }
}

namespace core
{
    void loadOBJ(std::string path)
    {
        path = "../" + path;
        std::ifstream src(path);

        if (!src)
        {
            std::cout << "Unable to locate model at " << path << std::endl;
            exit(1);
        }

        std::string line;

        std::vector<Vertex> vertices;
        std::vector<glm::vec2> textures;
        std::vector<glm::vec3> normals;
        std::vector<int> indices;

        while (std::getline(src, line))
        {
            if (line.find("v ") != std::string::npos)
            {
                vertices.emplace_back((int) vertices.size(), parseLine(line));
            } else if (line.find("vt ") != std::string::npos)
            {
                textures.emplace_back(glm::vec2(parseLine(line)));
            } else if (line.find("vn ") != std::string::npos)
            {
                normals.emplace_back(parseLine(line));
            } else if (line.find("f "))
            {
                break;
            }
        }
    }
}