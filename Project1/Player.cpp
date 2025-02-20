#include "Player.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "EnemyFSM.hpp"

Player::Player(float x, float y, int hp) : Entity(x, y, sf::Color::Blue, hp), attackTimer(0.f) {}

void Player::update(float deltaTime, Grid& grid, std::vector<Entity*> enemies) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { SPEED = 250.f; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) { SPEED = 75.f; }
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && !sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { SPEED = 150.f; }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { movement.y -= SPEED * deltaTime; }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += SPEED * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) movement.x -= SPEED * deltaTime;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += SPEED * deltaTime;

    if (movement == sf::Vector2f{ 0.f, 0.f }) SPEED = 0.f; //i did this to make it so the enemy won't hear the player if they stand still

    sf::Vector2f newPosition = shape.getPosition() + movement;
    sf::Vector2f originOffset = shape.getOrigin();
    sf::Vector2f size = shape.getSize();

    float left = newPosition.x - originOffset.x;
    float top = newPosition.y - originOffset.y;
    float right = left + size.x;
    float bottom = top + size.y;

    sf::FloatRect newBounds(left, top, size.x, size.y);

    auto isWalkable = [&](float x, float y) {
        int gridX = static_cast<int>(x / CELL_SIZE);
        int gridY = static_cast<int>(y / CELL_SIZE);
        return gridX >= 0 && gridX < GRID_WIDTH && gridY >= 0 && gridY < GRID_HEIGHT && grid.getCell(gridX, gridY).walkable;
        };

    bool topLeft = isWalkable(left, top);
    bool topRight = isWalkable(right, top);
    bool bottomLeft = isWalkable(left, bottom);
    bool bottomRight = isWalkable(right, bottom);

    if (topLeft && topRight && bottomLeft && bottomRight) {
        shape.move(movement);
    }

    attackTimer += deltaTime;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && attackTimer >= ATTACK_COOLDOWN) {
        attack(enemies);
        attackTimer = 0.f;
    }
}

void Player::attack(std::vector<Entity*>enemies) {
	for (auto& enemy : enemies) {
        if (enemy = dynamic_cast<Entity*>(enemy)) {
            if (enemy->isAlive() && shape.getGlobalBounds().intersects(enemy->shape.getGlobalBounds())) {
                enemy->takeDamage(DAMAGE);
                std::cout << "Enemy HP: " << enemy->health << std::endl;
            }
        }
		
	}
    std::cout << "Player attacks" << std::endl;
}