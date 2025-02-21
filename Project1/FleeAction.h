#pragma once

#include "Action.h"
//#include "State.h"
#include <SFML/Graphics.hpp>
#include "EnemyGOAP.h"
#include "Player.hpp"

class FleeAction : public Action {
private:
	Player* player;
public:
	bool CanExecute(const State& state) override;
	void Execute(EnemyGOAP& enemy, Player& player) override;
};
