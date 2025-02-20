#include "PatrolAction.h"


int randLimitGOAP(int min, int max) {
    return min + rand() % (max - min + 1);
}


bool PatrolAction::CanExecute(const State& state)
{
	return !state.getHunting() && !state.getSearching() && !state.getShouldFlee();
}

void PatrolAction::Execute(State& state)
{
	cout << "L'ennemi patrouille";
    enemyGoap->shape.setFillColor(Color::Green);
    static int currentWaypoint = 0;
    sf::Vector2f waypoints[4] = {
        sf::Vector2f(randLimitGOAP(0, 1440), randLimitGOAP(0, 840)),
        sf::Vector2f(randLimitGOAP(0, 1440), randLimitGOAP(0, 840)),
        sf::Vector2f(randLimitGOAP(0, 1440), randLimitGOAP(0, 840)),
        sf::Vector2f(randLimitGOAP(0, 1440), randLimitGOAP(0, 840))
    };
    Vector2f position = enemyGoap->shape.getPosition();
    Vector2f target = waypoints[currentWaypoint];
    Vector2f direction = target - position;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.0f) {
        currentWaypoint = (currentWaypoint + 1) % 4;
    }
    else {
        direction /= distance;
        position += direction * 3.0f;
    }
    enemyGoap->shape.setPosition(position);
}
