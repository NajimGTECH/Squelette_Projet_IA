#include "GOAPPlanner.h"
#include "PatrolAction.h"
#include "HuntAction.h"
//#include "SearchAction.h"
#include "FleeAction.h"

vector<unique_ptr<Action>> GOAPPlanner::Plan(const State& initialState, Goal goal) {
	vector<unique_ptr<Action>> plan;
	if (goal == Goal::PATROL) {
		plan.push_back(make_unique<PatrolAction>());
	}
	else if (goal == Goal::HUNT)
	{
		plan.push_back(make_unique<HuntAction>());
	}
	else if (goal == Goal::FLEE)
	{
		plan.push_back(make_unique <FleeAction>());
	}
	return plan;
}