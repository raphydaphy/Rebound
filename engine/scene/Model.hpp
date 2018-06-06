#ifndef MODEL_H
#define MODEL_H

#include "../core/loader.hpp"
#include "../gl/VertexArray.hpp"
#include <string>

class StaticModel
{
public:
    explicit StaticModel(std::string path);
    explicit StaticModel(ModelData data);
    int getVerticesLength();
    StaticModel bind();
    StaticModel unbind();
    void del();
private:
    int vertices;
    VertexArray vao;
};

#endif