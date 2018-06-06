#include "loader.hpp"

ModelData::ModelData(std::vector<glm::vec3> verticesArray, std::vector<glm::vec2> texturesArray, std::vector<glm::vec3> normalsArray,
             std::vector<int> indicesArray)
{
    this->verticesArray = std::move(verticesArray);
    this->texturesArray = std::move(texturesArray);
    this->normalsArray = std::move(normalsArray);
    this->indicesArray = std::move(indicesArray);
}

namespace core
{
    ModelData loadOBJ(const char *path)
    {

        printf("Loading OBJ file %s...\n", path);

        std::vector<int> vertexIndices, uvIndices, normalIndices;
        std::vector<glm::vec3> temp_vertices;
        std::vector<glm::vec2> temp_uvs;
        std::vector<glm::vec3> temp_normals;


        FILE * file = fopen(path, "r");
        if(!file)
        {
            std::cout << "Unable to locate model_acacia_1 at " << path << std::endl;
            exit(1);
        }

        while( 1 )
        {

            char lineHeader[128];
            int res = fscanf(file, "%s", lineHeader);
            if (res == EOF)
            {
                break;
            }
            if ( strcmp( lineHeader, "v" ) == 0 )
            {
                glm::vec3 vertex;
                fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
                temp_vertices.push_back(vertex);
            }else if ( strcmp( lineHeader, "vt" ) == 0 )
            {
                glm::vec2 uv;
                fscanf(file, "%f %f\n", &uv.x, &uv.y );
                uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
                temp_uvs.push_back(uv);
            }else if ( strcmp( lineHeader, "vn" ) == 0 )
            {
                glm::vec3 normal;
                fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
                temp_normals.push_back(normal);
            } else if ( strcmp( lineHeader, "f" ) == 0 )
            {
                std::string vertex1, vertex2, vertex3;
                unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
                if (matches != 9){
                    printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                    fclose(file);
                    exit(1);
                }
                vertexIndices.push_back(vertexIndex[0]);
                vertexIndices.push_back(vertexIndex[1]);
                vertexIndices.push_back(vertexIndex[2]);
                uvIndices    .push_back(uvIndex[0]);
                uvIndices    .push_back(uvIndex[1]);
                uvIndices    .push_back(uvIndex[2]);
                normalIndices.push_back(normalIndex[0]);
                normalIndices.push_back(normalIndex[1]);
                normalIndices.push_back(normalIndex[2]);
            } else
            {
                // Probably a comment, eat up the rest of the line
                char stupidBuffer[1000];
                fgets(stupidBuffer, 1000, file);
            }

        }

        std::vector<glm::vec3> out_vertices;
        std::vector<glm::vec2> out_uvs;
        std::vector<glm::vec3> out_normals;

        // For each vertex of each triangle
        for( unsigned int i=0; i<vertexIndices.size(); i++ )
        {
            // Get the indices of its attributes
            int vertexIndex = vertexIndices[i];
            int uvIndex = uvIndices[i];
            int normalIndex = normalIndices[i];

            // Get the attributes thanks to the index
            glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
            glm::vec2 uv = temp_uvs[ uvIndex-1 ];
            glm::vec3 normal = temp_normals[ normalIndex-1 ];

            // Put the attributes in buffers
            out_vertices.push_back(vertex);
            out_uvs     .push_back(uv);
            out_normals .push_back(normal);
        }
        fclose(file);

        ModelData m(out_vertices, out_uvs, out_normals, vertexIndices);
        return m;
    }

    void loadPNG(std::vector<unsigned char> &buffer, const std::string &filename)
    {
        std::ifstream file(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

        //get filesize
        std::streamsize size = 0;
        if (file.seekg(0, std::ios::end).good()) size = file.tellg();
        if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

        //read contents of the file into the vector
        if (size > 0)
        {
            buffer.resize((size_t) size);
            file.read((char *) (&buffer[0]), size);
        } else buffer.clear();
    }
}