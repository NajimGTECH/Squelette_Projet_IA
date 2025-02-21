#pragma once
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "Entity.hpp"
#include "Enemy.hpp"
#include "State.h"
#include "GOAPPlanner.h"


class EnemyGOAP : public Enemy {
private:
    State state;
    Goal currentGoal;
    GOAPPlanner planner;
public:
    Player& player;
    float detectionRadius;

    EnemyGOAP(Player& p, Vector2f pos, float radius, int hp);

    void setGoal(Goal goal);
    void updateState(State& state, EnemyGOAP& enemy);
    void PerformActions(State& state, EnemyGOAP& enemy);
    bool detectPlayer(sf::Vector2f playerPos);


    void update(float deltaTime, Grid& grid, std::vector<Entity*> players) override;

    int GetHealth() const { return state.getHealthstate(); }
    Vector2f getPos() const { return state.getPosState(); }
    State& getState() { return state; }
};