#include "Model.hpp"

StaticModel StaticModel::bind()
{
    vao.bind({0, 1, 2});
    return *this;
}

StaticModel StaticModel::unbind()
{
    vao.unbind({0, 1, 2});
    return *this;
}

void StaticModel::del()
{
    vao.del();
}

TexturedStaticModel::TexturedStaticModel(std::string path) : TexturedStaticModel( core::loadOBJ(path + ".obj")) { }

TexturedStaticModel::TexturedStaticModel(TexturedModelData data)
{
    vao = VertexArray().bind().createAttribute(0, &data.verticesArray[0], data.verticesArray.size() * sizeof(glm::vec3), 3)
            .createAttribute(1, &data.normalsArray[0], data.normalsArray.size() * sizeof(glm::vec3), 3)
            .createAttribute(2, &data.texturesArray[0], data.texturesArray.size() * sizeof(glm::vec2), 2).unbind();

    vertices = data.verticesArray.size();
}

int TexturedStaticModel::getVerticesLength()
{
    return vertices;
}

IndexedStaticModel::IndexedStaticModel(IndexedModelData data)
{
    vao = VertexArray().bind().storeIndices(&data.indicesArray[0], data.indicesArray.size() * sizeof(unsigned int))
            .createAttribute(0, &data.verticesArray[0], data.verticesArray.size() * sizeof(glm::vec3), 3)
            .createAttribute(1, &data.normalsArray[0], data.normalsArray.size() * sizeof(glm::vec3), 3).unbind();

    indices = data.indicesArray.size();
}

int IndexedStaticModel::getIndicesLength()
{
    return indices;
}
