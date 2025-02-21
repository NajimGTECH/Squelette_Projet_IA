#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>



class Player : public Entity {
public:
    static constexpr float SPEED = 200.0f;
    sf::Vector2f playerPos;

    Player(sf::Vector2f pos, int hp);
    sf::Vector2f getpos() { return shape.getPosition(); }
    float SPEED = 150.f;
    //void update(float deltaTime, Grid& grid) override;
    static constexpr int DAMAGE = 20;
    static constexpr float ATTACK_COOLDOWN = 0.5f;
    float attackTimer;

    void attack(std::vector<Entity*> enemies);
    void update(float deltaTime, Grid& grid, std::vector<Entity*> enemies) override;
};

#endif // PLAYER_HPP