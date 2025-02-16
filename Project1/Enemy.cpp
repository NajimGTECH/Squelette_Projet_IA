#include "Enemy.hpp"
#include <cmath>

Enemy::Enemy(Player& p, sf::Vector2f pos, float radiusDetect) : Entity(pos, sf::Color::Red), player(p), detectionRadius(radiusDetect) {
    detectionRadius = 200.0f;
    currentState = PATROL;
}

bool Enemy::detectPlayer(sf::Vector2f playerPos)
{
    // Calcul de la distance entre l'ennemi et le joueur
    float distance = std::sqrt(std::pow(player.getpos().x - position.x, 2) + std::pow(player.getpos().y - position.y, 2));

    // Affichage de la distance et du rayon de d�tection pour le d�bogage
    std::cout << "Distance to player: " << distance << " | Detection Radius: " << detectionRadius << std::endl;

    return (distance < detectionRadius);  // Si la distance est inf�rieure au rayon de d�tection, retour vrai
}



void Enemy::patrol()
{
    static int currentWaypoint = 0;
    static sf::Vector2f waypoints[4] = { sf::Vector2f(100, 300), sf::Vector2f(500, 100), sf::Vector2f(100, 300), sf::Vector2f(500, 300) };
    sf::Vector2f target = waypoints[currentWaypoint];
    sf::Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.0f) {
        currentWaypoint = (currentWaypoint + 1) % 4;
    }
    else {
        direction /= distance;
        position += direction * 1.0f;
    }
    shape.setPosition(position);
}

void Enemy::chase(sf::Vector2f playerPos)
{
    sf::Vector2f direction = playerPos - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > 0) {
        direction /= distance;
        position += direction * 0.2f;
    }

    shape.setPosition(position);
}



void Enemy::search(sf::Vector2f lastPlayerPos, float deltaTime) {
    static float searchTimer = 0.0f;
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
        searchTimer = 0.0f;
    }

    shape.setPosition(position);
}

void Enemy::update(float deltaTime, Grid& grid) {
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
        search(lastPlayerPos, deltaTime);
        break;
    }
}
