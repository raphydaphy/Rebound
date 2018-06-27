#ifndef REBOUND_LIGHT_H
#define REBOUND_LIGHT_H

#include <glm/gtc/matrix_transform.hpp>

class Light
{
public:
    Light(glm::vec3 position, glm::vec3 color);
    Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation);
    void setPosition(glm::vec3 position);
    void setColor(glm::vec3 color);
    glm::vec3 getPosition();
    glm::vec3 getColor();
    glm::vec3 getAttenuation();
private:
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 attenuation;
};

#endif