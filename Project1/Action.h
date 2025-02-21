#pragma once

#include "State.h"

class EnemyGOAP;
class Player;

class Action {
public:
	virtual bool CanExecute(const State& state) = 0;
	virtual void Execute(EnemyGOAP& enemy,Player& player) = 0;
	virtual ~Action() {}
};