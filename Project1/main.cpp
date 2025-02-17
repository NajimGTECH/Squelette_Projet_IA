#include <SFML/Graphics.hpp>

#include "Player.hpp"
#include "Enemy.hpp"
#include "BTEnemy.h"
#include "Grid.hpp"

#include <vector>


const int WINDOW_WIDTH = 1480;
const int WINDOW_HEIGHT = 880;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Jeu SFML - IA Ennemis");
    window.setFramerateLimit(60);

    Player player(200, 400);

    std::vector<Enemy> enemies = { Enemy(100, 100), Enemy(700, 100) };

    std::vector<BTEnemy> btenemies;
    btenemies.push_back(BTEnemy(200, 200));

    Grid grid;
    grid.loadFromFile("map.txt");

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.update(deltaTime, grid);
        for (auto& enemy : enemies) {
            enemy.update(deltaTime, grid);
        }
        for (auto& btenemy : btenemies) {
            btenemy.update(deltaTime, grid, player);
        }

        window.clear();
        grid.draw(window);
        window.draw(player.shape);

        for (const auto& enemy : enemies)
            window.draw(enemy.shape);

        for (const auto& btenemy : btenemies)
            window.draw(btenemy.shape);

        window.display();
    }
    return 0;
}

