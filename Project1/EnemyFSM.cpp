#include "EnemyFSM.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>


sf::Clock timetest;
int randLimit(int min, int max) {
    return min + rand() % (max - min + 1);
}

Enemy::Enemy(Player& p, sf::Vector2f pos, float radiusDetect, int hp) : Entity(pos, sf::Color::Red, hp), player(p), detectionRadius(radiusDetect) {
    detectionRadius = 200.0f;
    currentState = PATROL;
}

bool Enemy::detectPlayer(sf::Vector2f playerPos)
{
    float distance = std::sqrt(std::pow(player.getpos().x - position.x, 2) + std::pow(player.getpos().y - position.y, 2));

    //std::cout << "Distance to player: " << distance << " | Detection Radius: " << detectionRadius << std::endl;

    return (distance < detectionRadius);
}



void Enemy::patrol()
{
    shape.setFillColor(sf::Color::Green);
    std::srand(static_cast<unsigned int>(std::time(0)));
    static int currentWaypoint = 0;
    sf::Vector2f waypoints[4] = {
        sf::Vector2f(randLimit(0, 1480), randLimit(0, 880)),
        sf::Vector2f(randLimit(0, 1480), randLimit(0, 880)),
        sf::Vector2f(randLimit(0, 1480), randLimit(0, 880)),
        sf::Vector2f(randLimit(0, 1480), randLimit(0, 880))
    };
    sf::Vector2f target = waypoints[currentWaypoint];
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.0f) {
        currentWaypoint = (currentWaypoint + 1) % 4;
    }
    else {
        direction /= distance;
        position += direction * 2.5f;
    }
    shape.setPosition(position);
}

void Enemy::chase(sf::Vector2f playerPos)
{
    shape.setFillColor(sf::Color::Red);
    sf::Vector2f direction = playerPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 0.5f;
    }
    shape.setPosition(position);
}



void Enemy::search(sf::Vector2f lastPlayerPos, float deltaTime) {
    shape.setFillColor(sf::Color::Yellow);
    float searchTimer = 0.0f;
    static sf::Vector2f searchDirection;

    if (searchTimer == 0.0f) {
        searchDirection = sf::Vector2f(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1);
        searchDirection /= std::sqrt(searchDirection.x * searchDirection.x + searchDirection.y * searchDirection.y);
    }

    searchTimer += deltaTime;
    if (searchTimer < 10.0f) {
        position += searchDirection * 5.f * deltaTime;
    }
    else {
        searchTimer = 0.0f;
        currentState = PATROL;
    }

    float distance = std::sqrt((lastPlayerPos.x - position.x) * (lastPlayerPos.x - position.x) + (lastPlayerPos.y - position.y) * (lastPlayerPos.y - position.y));
    if (distance < detectionRadius) {
        timetest.restart();
        searchTimer = 0.0f;
        currentState = CHASE;
    }

    if (timetest.getElapsedTime().asMilliseconds() > 5000)
    {
        timetest.restart();
        searchTimer = 0.0f;
        currentState = PATROL;
    }
    shape.setPosition(position);
}


void Enemy::update(float deltaTime, Grid& grid, std::vector<Entity*> players) {
    switch (currentState) {
    case PATROL:
        patrol();
        if (detectPlayer(player.getpos())) currentState = CHASE;
        break;

    case CHASE:
        chase(player.getpos());
        if (!detectPlayer(player.getpos())) {
            lastPlayerPos = player.getpos();
            currentState = SEARCH;
        }
        break;

    case SEARCH:
        search(player.getpos(), deltaTime);
        break;
    }
}



