#include "loader.hpp"

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

Vertex::Vertex(int index, glm::vec3 position)
{
    this->index = index;
    this->position = position;
}

Model::Model(std::vector<float> verticesArray, std::vector<float> texturesArray, std::vector<float> normalsArray,
             std::vector<int> indicesArray)
{
    this->verticesArray = verticesArray;
    this->texturesArray = texturesArray;
    this->normalsArray = normalsArray;
    this->indicesArray = indicesArray;
}


namespace core
{
    Model loadOBJ(std::string path)
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
            std::vector<std::string> words = split(line, ' ');
            if (words[0] == "v")
            {
                vertices.emplace_back((int) vertices.size(), glm::vec3(atof(words[1].c_str()), atof(words[2].c_str()), atof(words[3].c_str()))); // NOLINT
            } else if (words[0] == "vt")
            {
                textures.emplace_back(glm::vec2(atof(words[1].c_str()), atof(words[2].c_str()))); // NOLINT
            } else if (words[0] == "vn")
            {
                normals.emplace_back(glm::vec3(atof(words[1].c_str()), atof(words[2].c_str()), atof(words[3].c_str()))); // NOLINT
            } else if (words[0] == "f")
            {
                for (int v = 1; v <= 3; v++)
                {
                    std::vector<std::string> vertex = split(words[v], '/');

                    int index = atoi(vertex[0].c_str()) - 1; // NOLINT
                    int texCoordIndex = atoi(vertex[1].c_str()) - 1; // NOLINT
                    int normalIndex = atoi(vertex[2].c_str()) - 1; // NOLINT

                    Vertex vert = vertices[index];

                    if (vert.texCoordIndex == VERTEX_NO_INDEX || vert.normalIndex == VERTEX_NO_INDEX)
                    {
                        vert.texCoordIndex = texCoordIndex;
                        vert.normalIndex = normalIndex;

                        indices.push_back(index);
                    }
                    else
                    {
                        std::cout << "tried to process an already processed vertex" << std::endl;
                    }

                }
            }
        }

        std::vector<float> verticesArray;
        std::vector<float> texturesArray;
        std::vector<float> normalsArray;

        for (int i = 0; i < vertices.size(); i++)
        {
            Vertex vertex = vertices[i];
            glm::vec2 texture = textures[vertex.texCoordIndex];
            glm::vec3 normal = normals[vertex.normalIndex];

            verticesArray[i * 3] = vertex.position.x;
            verticesArray[i * 3 + 1] = vertex.position.y;
            verticesArray[i * 3 + 2] = vertex.position.z;

            texturesArray[i * 2] = texture.x;
            texturesArray[i * 2 + 1] = texture.y;

            normalsArray[i * 3] = normal.x;
            normalsArray[i * 3 + 1] = normal.y;
            normalsArray[i * 3 + 2] = normal.z;

        }

        Model m(verticesArray, texturesArray, normalsArray, indices);
        return m;
    }
}