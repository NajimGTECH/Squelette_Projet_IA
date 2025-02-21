#pragma once

#include "Action.h"
#include "State.h"
#include <SFML/Graphics.hpp>
#include "EnemyGOAP.h"

class PatrolAction : public Action {
public:
	bool CanExecute(const State& state) override;
	void Execute(EnemyGOAP& enemy, Player& player) override;
};