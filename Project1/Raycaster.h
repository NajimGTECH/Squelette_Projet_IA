#include <SFML/Graphics.hpp>
#include "Grid.hpp"
#include "Window.h"
#include "Entity.hpp"
#include <cmath>

class Raycaster {
public:
    Raycaster() {};
    std::shared_ptr<Entity> attachedEntity;
    std::vector<sf::Vector2f> intersections;

    void renderRay(Grid& grid);
    float degToRad(float degree);
};