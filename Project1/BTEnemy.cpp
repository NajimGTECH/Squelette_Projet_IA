#include "BTEnemy.h"

BTEnemy::BTEnemy(float x, float y) : Entity(x, y, sf::Color::Cyan, 50)
{
	shape.setOrigin(shape.getSize() / 2.f);
	//Raycaster raycast = Raycaster(100, 100, 1.0f, 1.0f);
	//raycaster = raycast;
	fov_Vizualisation = sf::VertexArray(sf::TrianglesFan, 0);

	radius.setRadius(DETECTION_RADIUS);
	radius.setOutlineColor(sf::Color::Green);
	radius.setOutlineThickness(2);
	radius.setFillColor(sf::Color(0, 255, 0, 20));
	radius.setOrigin(DETECTION_RADIUS, DETECTION_RADIUS);
}

void BTEnemy::update(float deltaTime, Grid& grid, std::vector<Entity*> neededEntities)
{
	behavior->executeRoot();
}

void BTEnemy::update(float deltaTime, Grid& grid, Player& player)
{
	deltatime = deltaTime;
	sf::Vector2f playerPos = player.shape.getPosition();
	sf::Vector2f pos = shape.getPosition();

	radius.setPosition(shape.getPosition());
	//radiusVision.setPosition(shape.getPosition());

	raycast.renderRay(grid);

	fov_Vizualisation.clear();

	fov_Vizualisation.append(sf::Vertex(shape.getPosition(), sf::Color(255, 0, 0, 100)));

	for (size_t i = 1; i < raycast.intersections.size() + 1; i++)
	{
		fov_Vizualisation.append(sf::Vertex(raycast.intersections[i - 1], sf::Color(255, 0, 0, 100)));
	}

	float distance = std::hypot(playerPos.x - pos.x, playerPos.y - pos.y);
	auto blackboard = behavior->getBlackboard();
	velocity = { 0, 0 };

	if (distance <= DETECTION_RADIUS)
	{
		if (isPointInVision(playerPos, fov_Vizualisation))
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

bool BTEnemy::isPointInVision(const sf::Vector2f& point, const sf::VertexArray& vision)
{
	int intersectCount = 0;
	size_t vertexCount = vision.getVertexCount();

	for (size_t i = 0; i < vertexCount; ++i)
	{
		sf::Vector2f v1 = vision[i].position;
		sf::Vector2f v2 = vision[(i + 1) % vertexCount].position;

		if ((point.y > std::min(v1.y, v2.y)) && (point.y <= std::max(v1.y, v2.y)))
		{
			float intersectX = (point.y - v1.y) * (v2.x - v1.x) / (v2.y - v1.y) + v1.x;

			if (intersectX > point.x)
			{
				++intersectCount;
			}
		}
	}

	return (intersectCount % 2) != 0;
}
