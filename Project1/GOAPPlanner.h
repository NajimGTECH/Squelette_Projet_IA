#pragma once


#include <vector>
#include <memory>

#include "Goal.h"
#include "Action.h"


class GOAPPlanner {
public:
	vector<unique_ptr<Action>> Plan(const State& initialState, Goal goal);
};