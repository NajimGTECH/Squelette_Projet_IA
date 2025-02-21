#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

#include "Grid.hpp"
#include "Pathfinding.h"

class Entity {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    int health;
    Pathfinding pathfinding;

    float fov = 60.0f; //fov
    float orientation = 90.0f; //orientation

    float deltatime; //test

    //virtual void update(float deltaTime, Grid& grid) = 0;

    Entity(float x, float y, sf::Color color, int hp);
    virtual void update(float deltaTime, Grid& grid, std::vector<Entity*> neededEntities) = 0;
    bool isAlive() const;
    void takeDamage(int damage);
};


#endif // ENTITY_HPP