#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "EnemyFSM.hpp"
//#include "Enemy.hpp"
#include "BTEnemy.h"
#include "Grid.hpp"
#include "Window.h"

#include <vector>
#include <ctime>


int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(window::WINDOW_WIDTH, window::WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    std::vector<Entity*> players;
    Player player(200, 400, 10);
    player.shape.setOrigin(player.shape.getSize() / 2.f);
    players.push_back(new Player(200, 400, 10));

    std::vector<Entity*> enemies;
    enemies.push_back(new EnemyFSM(player, sf::Vector2f(100, 100), 50.0f, 100));
    enemies.push_back(new EnemyFSM(player, sf::Vector2f(700, 100), 50.0f, 100));

    Grid grid;
    grid.loadFromFile("map.txt");

    //*BEHAVIOR TREE ENEMY*\\ 
    std::vector<std::shared_ptr<BTEnemy>> btenemies;
    auto btEnemy = std::make_shared<BTEnemy>(200, 200);
    btEnemy->initBTree(grid);
    btEnemy->raycast.attachedEntity = btEnemy;
    btenemies.push_back(btEnemy);
    auto btEnemy2 = std::make_shared<BTEnemy>(1000, 550);
    btEnemy2->initBTree(grid);
    btEnemy2->raycast.attachedEntity = btEnemy2;
    btenemies.push_back(btEnemy2);

    sf::Clock clock;

    while (window.isOpen()) {
        window.clear();

        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid, enemies);
        for (auto& enemy : enemies) {
            //enemy->update(deltaTime, grid);
        }
        for (auto& btenemy : btenemies) {
            btenemy->update(deltaTime, grid, player);
        }


        grid.draw(window);

        for (auto& btenemy : btenemies) {
            auto rayIntersections = btenemy->raycast.renderRay(grid);
            sf::VertexArray fov_Vizualisation(sf::TrianglesFan, rayIntersections.size() + 1);
            std::cout << "Intersections count: " << rayIntersections.size() << std::endl;
            fov_Vizualisation[0].position = btenemy->shape.getPosition();

            for (size_t i = 1; i < rayIntersections.size() + 1; i++)
            {
                fov_Vizualisation[i].position = rayIntersections[i - 1];
            }
            window.draw(fov_Vizualisation);
        }

        window.draw(player.shape);

        for (const auto& btenemy : btenemies)
        {
            window.draw(btenemy->radius);
            window.draw(btenemy->radiusVision);
            window.draw(btenemy->shape);
        }

        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
                window.draw(enemy->shape);
            }
        }
        window.display();
    }
    return 0;
}
