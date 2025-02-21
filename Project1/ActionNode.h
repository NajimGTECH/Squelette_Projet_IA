#ifndef ACTION_NODE_H
#define ACTION_NODE_H

#include <SFML/System/Vector2.hpp>

#include "BTNode.h"
#include "Blackboard.h"

#include <iostream>
#include <string>
#include <random>

class ActionNode : public BTNode {
public:
    ActionNode();
    ActionNode(const std::string& actionName);
    NodeState execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity) override;
protected:
    std::shared_ptr<Blackboard> m_blackboard;
    std::string m_actionName;
};


class PatrolNode : public ActionNode {
public:
    int stopTime = 1;
    float speedMultiplicator = .5f;

    PatrolNode() : ActionNode("Patrolling") {}
    NodeState execute(Grid & grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity) override;
};

class ChaseNode : public ActionNode {
public:
    float speedMultiplicator = 1.25f;

    ChaseNode() : ActionNode("Chase") {}
    NodeState execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity) override;
};

class SearchNode : public ActionNode {
public:
    int stopTime = 3;
    float speedMultiplicator = 1.f;

    SearchNode() : ActionNode("Search") {}
    NodeState execute(Grid& grid, std::shared_ptr<Blackboard> blackboard, std::shared_ptr<Entity> entity) override;
};




#endif