#ifndef MODEL_H
#define MODEL_H

#include "../core/loader.hpp"
#include "../gl/VertexArray.hpp"
#include <string>

class StaticModel
{
public:
    int getVerticesLength();
    StaticModel bind();
    StaticModel unbind();
    void del();
protected:
    int vertices{};
    VertexArray vao;
};

class TexturedStaticModel : public StaticModel
{
public:
    explicit TexturedStaticModel(std::string path);
    explicit TexturedStaticModel(TexturedModelData data);
};

class ColoredStaticModel : public StaticModel
{
public:
  explicit ColoredStaticModel(ColoredModelData data);
};

#endif