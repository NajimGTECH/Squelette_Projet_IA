#include "EnemyGOAP.h"



EnemyGOAP::EnemyGOAP(Player& p, Vector2f pos, float radiusDetect, int hp) : Enemy(pos, hp), player(p), detectionRadius(radiusDetect) 
{
    currentGoal = Goal::PATROL;
    state.setPatrolling(false);
    state.setHunting(false);
    state.setShouldFlee(false);
	detectionRadius = 100.0f;
	state.healthGOAP = 100;
	state.positionGOAP = pos;
}

void EnemyGOAP::setGoal(Goal goal)
{
    currentGoal = goal;
}

void EnemyGOAP::updateState(State& state, EnemyGOAP& enemy)
{
    if (detectPlayer(player.getpos()))
    {
        if (enemy.state.getHealthstate() < enemy.state.getHealthstate() / 2)
        {
            enemy.state.setShouldFlee(true);
        }

        if (enemy.state.getShouldFlee()) {
            setGoal(Goal::FLEE);
            enemy.state.setPatrolling(false);
            enemy.state.setHunting(false);
            //cout << "test flee";
        }

        else {
            setGoal(Goal::HUNT);
            enemy.state.setHunting(true);
            enemy.state.setPatrolling(false);
            cout << "test hunt";
        }
    }
    else
    {
        enemy.state.setPatrolling(true);
        enemy.state.setHunting(false);
        setGoal(Goal::PATROL);
        //cout << "test patrol";
    }
    PerformActions(enemy.state, enemy);
}

void EnemyGOAP::PerformActions(State& state, EnemyGOAP& enemy)
{
    vector<unique_ptr<Action>> actions = planner.Plan(state, currentGoal);

    for (auto& action : actions) {
        if (action->CanExecute(state))
        {
            action->Execute(enemy, player);
        }
    }
}

bool EnemyGOAP::detectPlayer(sf::Vector2f playerPos)
{
    float distance = std::sqrt(std::pow(player.getpos().x - shape.getPosition().x, 2) + std::pow(player.getpos().y - shape.getPosition().y, 2));
    //std::cout << "Distance to player: " << distance << " | Detection Radius: " << detectionRadius << std::endl;
    return (distance < detectionRadius);
}


void EnemyGOAP::update(float deltaTime, Grid& grid, std::vector<Entity*> players)
{
}
