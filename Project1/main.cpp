#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "EnemyFSM.hpp"
#include "Enemy.hpp"
#include "BTEnemy.h"
#include "Grid.hpp"

#include <vector>
#include <ctime>

const int WINDOW_WIDTH = 1480;
const int WINDOW_HEIGHT = 880;


int main() {
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player({ 400, 400 }, 10);
    std::vector<Entity*> players;
    players.push_back(new Player({ 400,400 }, 10));
    std::vector<Entity*> enemies;
    enemies.push_back(new Enemy(player, { 100, 100 }, 50.0f, 100));
    enemies.push_back(new Enemy(player, { 700, 100 }, 50.0f, 100));

    Grid grid;
    grid.loadFromFile("map.txt");

    Player player(200, 400, 10);
    player.shape.setOrigin(player.shape.getSize() / 2.f);

    //*BEHAVIOR TREE ENEMY*\\ 
    std::vector<std::shared_ptr<BTEnemy>> btenemies;
    auto btEnemy = std::make_shared<BTEnemy>(200, 200);
    btEnemy->initBTree(grid);
    btenemies.push_back(btEnemy);
    auto btEnemy2 = std::make_shared<BTEnemy>(1000, 550);
    btEnemy2->initBTree(grid);
    btenemies.push_back(btEnemy2);

    sf::Clock clock;

    while (window.isOpen()) {
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

        window.clear();

        grid.draw(window);
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
