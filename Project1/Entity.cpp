#include "Entity.hpp"

Entity::Entity(sf::Vector2f pos, sf::Color color, int health) {
    shape.setSize({ 35, 35 });
    shape.setPosition(pos);
    shape.setFillColor(color);
}

sf::RectangleShape Entity::getshape()
{
    return shape;
}
bool Entity::isAlive() const
{
    return health > 0;
}

void Entity::takeDamage(int damage) {
    health -= damage;
}