#include "Light.hpp"

Light::Light(glm::vec3 position, glm::vec3 color) : Light(position, color, glm::vec3(1, 0, 0)) { }

Light::Light(glm::vec3 position, glm::vec3 color, glm::vec3 attenuation)
{
    this->position = position;
    this->color = color;
    this->attenuation = attenuation;
}

void Light::setPosition(glm::vec3 position)
{
    this->position = position;
}

void Light::setColor(glm::vec3 color)
{
    this->color = color;
}

glm::vec3 Light::getPosition()
{
    return position;
}

glm::vec3 Light::getColor()
{
    return color;
}

glm::vec3 Light::getAttenuation()
{
    return attenuation;
}
