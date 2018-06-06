#include "Model.hpp"


StaticModel::StaticModel(std::string path) : StaticModel( core::loadOBJ(("../res/" + path + ".obj").c_str())) { }

StaticModel::StaticModel(ModelData data)
{
    vao = VertexArray().bind().createAttribute(0, &data.verticesArray[0], data.verticesArray.size() * sizeof(glm::vec3), 3)
            .createAttribute(1, &data.texturesArray[0], data.texturesArray.size() * sizeof(glm::vec2), 2)
            .createAttribute(2, &data.normalsArray[0], data.normalsArray.size() * sizeof(glm::vec3), 3).unbind();

    vertices = data.verticesArray.size();
}

int StaticModel::getVerticesLength()
{
    return vertices;
}


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