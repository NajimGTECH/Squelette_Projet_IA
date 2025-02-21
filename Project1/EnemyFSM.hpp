#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;
using namespace sf;


class EnemyFSM : public Enemy {
public:
    Player& player;
    static constexpr float SPEED = 100.0f;
    float detectionRadius;
    Vector2f position;
    Vector2f lastPlayerPos;
    enum State { PATROL, CHASE, SEARCH };
    State currentState;
    float searchTimer = 0.0f;
    Vector2f searchDirection;



    EnemyFSM(Player& p ,sf::Vector2f pos, float radius, int hp);

    bool detectPlayer(sf::Vector2f playerPos);
    void patrol();
    void chase(sf::Vector2f playerPos);
    void search(sf::Vector2f lastPlayerPos, float deltaTime);
    void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;
};

#endif // ENEMY_HPP