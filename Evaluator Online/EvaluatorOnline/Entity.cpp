#include "Entity.h"


Entity::Entity()
{
    active=true;
    textActive=false;
    apasat=false;
}

void Entity::setTexture(sf::Texture texture)
{
    this->texture=texture;
}

void Entity::Activate()
{
    this->active=true;
}
void Entity::Deactivate()
{
    this->active=false;
}

bool Entity::IsActive()
{
    return this->active;
}

void Entity::setBoundsTexture(sf::Texture texture)
{
    this->bounds.setTexture(&texture);
}

sf::Texture Entity::getTexture()
{
    return this->texture;
}
