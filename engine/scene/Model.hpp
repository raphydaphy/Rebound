#ifndef MODEL_H
#define MODEL_H

#include "../core/loader.hpp"
#include "../gl/VertexArray.hpp"
#include <string>

class StaticModel
{
public:
    StaticModel bind();
    StaticModel unbind();
    void del();
protected:
    VertexArray vao;
};

class TexturedStaticModel : public StaticModel
{
public:
    explicit TexturedStaticModel(std::string path);
    explicit TexturedStaticModel(TexturedModelData data);
    int getVerticesLength();
protected:
    int vertices;
};

class IndexedStaticModel : public StaticModel
{
public:
  explicit IndexedStaticModel(IndexedModelData data);
  int getIndicesLength();
protected:
    int indices;
};

#endif