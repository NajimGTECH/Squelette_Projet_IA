#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include <SFML/Graphics.hpp>  

using namespace std;
using namespace sf;

class Enemy : public Entity {
public:
    static constexpr float SPEED = 100.0f;


    Enemy(sf::Vector2f pos, int hp) : Entity(pos, Color::Red, hp) {
    }
    virtual void update(float deltaTime, Grid& grid, std::vector<Entity*> players) = 0;
};
