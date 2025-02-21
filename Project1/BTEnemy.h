#ifndef BTENEMY_HPP
#define BTENEMY_HPP

#include "Player.hpp"
#include "BehaviorTree.h"
#include "Raycaster.h"

#include <cmath>

class BTEnemy : public Entity, public std::enable_shared_from_this<BTEnemy> {
public:
    static constexpr float SPEED = 150.0f;
    static constexpr float DETECTION_RADIUS = 250.0f; //hear
    static constexpr float VISION_RADIUS = 100.0f; //see

    sf::CircleShape radius; //hear

    std::shared_ptr<BTree> behavior = nullptr;
    Raycaster raycast;
    sf::VertexArray fov_Vizualisation;

    BTEnemy(float x, float y);
    void update(float deltaTime, Grid& grid, std::vector<Entity*> neededEntities) override;
    void update(float deltaTime, Grid& grid, Player& player);

    void initBTree(Grid& grid);
    bool isPointInVision(const sf::Vector2f& point, const sf::VertexArray& vision);
};

#endif // BTENEMY_HPP
