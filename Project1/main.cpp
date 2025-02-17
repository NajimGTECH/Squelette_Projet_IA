#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "EnemyFSM.hpp"
#include "Grid.hpp"
#include <vector>



const int WINDOW_WIDTH = 1480;
const int WINDOW_HEIGHT = 880;

int main() {
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

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Time dt = clock.restart();
        float deltaTime = dt.asSeconds();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        enemies[0]->update(deltaTime, grid, players);

        player.update(deltaTime, grid, enemies);

        window.clear();
        grid.draw(window);
        window.draw(player.shape);
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
            window.draw(enemy->shape);
            }
        }
        window.display();
    }
    return 0;
}
