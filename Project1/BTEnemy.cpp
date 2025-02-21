#include "BTEnemy.h"

BTEnemy::BTEnemy(float x, float y) : Entity(x, y, sf::Color::Cyan, 50)
{
	shape.setOrigin(shape.getSize() / 2.f);
	//Raycaster raycast = Raycaster(100, 100, 1.0f, 1.0f);
	//raycaster = raycast;

	radius.setRadius(DETECTION_RADIUS);
	radius.setOutlineColor(sf::Color::Green);
	radius.setOutlineThickness(2);
	radius.setFillColor(sf::Color(0, 255, 0, 20));
	radius.setOrigin(DETECTION_RADIUS, DETECTION_RADIUS);

	radiusVision.setRadius(VISION_RADIUS);
	radiusVision.setOutlineColor(sf::Color::Red);
	radiusVision.setOutlineThickness(2);
	radiusVision.setFillColor(sf::Color(255, 0, 0, 20));
	radiusVision.setOrigin(VISION_RADIUS, VISION_RADIUS);
}

void BTEnemy::update(float deltaTime, Grid& grid, std::vector<Entity*> neededEntities)
{
	behavior->executeRoot();
}

void BTEnemy::update(float deltaTime, Grid& grid, Player& player)
{
	sf::Vector2f playerPos = player.shape.getPosition();
	sf::Vector2f pos = shape.getPosition();

	radius.setPosition(shape.getPosition());
	radiusVision.setPosition(shape.getPosition());

	velocity = { 0, 0 };
	deltatime = deltaTime;

	float distance = std::hypot(playerPos.x - pos.x, playerPos.y - pos.y);
	auto blackboard = behavior->getBlackboard();

	if (distance <= DETECTION_RADIUS)
	{
		if (distance <= VISION_RADIUS)
		{
			blackboard->setValue("isPlayerDetected", true);
			blackboard->setValue("GoTo", playerPos);
		}
		else
		{
			if (player.SPEED >= 100.f)
			{
				blackboard->setValue("GoTo", playerPos);
				blackboard->setValue("isSearching", true);
			}
			else
			{
				if (blackboard->getValue<bool>("isOnSearchCooldown"))
				{
					blackboard->setValue("isSearching", true);
				}
				else
				{
					blackboard->setValue("isSearching", false);
				}
			}

			blackboard->setValue("isPlayerDetected", false);
		}
	}
	else
	{
		if (blackboard->getValue<bool>("isOnSearchCooldown"))
		{
			blackboard->setValue("isSearching", true);
		}
		
		blackboard->setValue("isPlayerDetected", false);
	}

	//execute tree
	behavior->executeRoot();
	shape.setPosition(pos + velocity * deltaTime * SPEED);
}

void BTEnemy::initBTree(Grid& grid)
{
	behavior = std::make_shared<BTree>(grid, shared_from_this());

	behavior->getBlackboard()->setValue("isPlayerDetected", false);

	behavior->getBlackboard()->setValue("isSearching", false);
	behavior->getBlackboard()->setValue("isOnSearchCooldown", false);


	behavior->getBlackboard()->setValue("GoTo", sf::Vector2f{ 0, 0 });

	auto plrFound = std::make_unique<SelectorNode>();
	auto plrNotFound = std::make_unique<SelectorNode>();

	auto plrChase = std::make_unique<SequenceNode>();
	auto plrSearch = std::make_unique<SequenceNode>();
	auto patrolling = std::make_unique<SequenceNode>();

	plrChase->addChild(std::make_unique<ConditionNode>("isPlayerDetected", true));
	plrChase->addChild(std::make_unique<ChaseNode>());

	plrSearch->addChild(std::make_unique<ConditionNode>("isSearching", true));
	plrSearch->addChild(std::make_unique<SearchNode>());

	patrolling->addChild(std::make_unique<PatrolNode>());


	plrFound->addChild(std::move(plrChase));
	plrFound->addChild(std::move(plrSearch));
	plrNotFound->addChild(std::move(patrolling));

	behavior->addChildToRoot(std::move(plrFound));
	behavior->addChildToRoot(std::move(plrNotFound));
}
