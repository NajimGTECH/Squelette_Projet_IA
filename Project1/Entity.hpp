#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include <iostream>

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    int health;

    Entity(sf::Vector2f pos, sf::Color color, int hp);
    virtual void update(float deltaTime, Grid& grid, std::vector<Entity*> neededEntities) = 0;
    sf::RectangleShape getshape();
    bool isAlive() const;
    void takeDamage(int damage);

};


#endif // ENTITY_HPP