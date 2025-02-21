#include <SFML/Graphics.hpp>
#include <vector>

#include "Player.hpp"
#include "EnemyFSM.hpp"
//#include "Enemy.hpp"
#include "BTEnemy.h"
#include "Grid.hpp"
#include "Window.h"

#include <vector>
#include <ctime>
#include "State.h"

<<<<<<<<< Temporary merge branch 1

const int WINDOW_WIDTH = 1480;
const int WINDOW_HEIGHT = 880;
=========
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
>>>>>>>>> Temporary merge branch 2

const int WINDOW_HEIGHT = 600;
>>>>>>>>> Temporary merge branch 2

    std::vector<Entity*> players;
<<<<<<< HEAD
    Player player(200, 400, 10);
    player.shape.setOrigin(player.shape.getSize() / 2.f);
    players.push_back(new Player(200, 400, 10));

    srand(time(NULL));
    enemies.push_back(new EnemyFSM(player, { 100, 100 },50.0f, 100));
    enemies.push_back(new EnemyFSM(player ,{ 700, 100 },50.0f, 100));

    enemies.push_back(new EnemyGOAP(player, { 100, 100 }, 50.0f, 100));  // Exemple d'ennemi
    enemies.push_back(new EnemyGOAP(player, { 700, 100 }, 50.0f, 100));
    EnemyGOAP enemyGOAP(player, { 500,500 }, 50.0f, 10);
    window.setFramerateLimit(60);

    Player player(400, 400, 10);
    std::vector<Entity*> enemies;
	enemies.push_back(new Enemy(100, 100, 10));
	enemies.push_back(new Enemy(700, 100, 100));
=======
    players.push_back(new Player({ 400,400 }, 10));
    std::vector<Entity*> enemies;
    //enemies.push_back(new EnemyFSM(player, { 100, 100 },50.0f, 100));
    //enemies.push_back(new EnemyFSM(player ,{ 700, 100 },50.0f, 100));

    enemies.push_back(new EnemyGOAP(player, { 100, 100 }, 50.0f, 100));  // Exemple d'ennemi
    enemies.push_back(new EnemyGOAP(player, { 700, 100 }, 50.0f, 100));
    EnemyGOAP test(player, { 500,500 }, 50.0f, 10);
>>>>>>> parent of e309c11 (Finish)
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
        for (auto& enemy : enemies) {
            //enemy->update(deltaTime, grid);
        }
        for (auto& btenemy : btenemies) {
            btenemy->update(deltaTime, grid, player);
        }


<<<<<<< HEAD
        enemyGOAP.updateState(enemyGOAP.getState(), enemyGOAP);
=======
        player.update(deltaTime, grid, enemies);
        //test.flee(player.getpos());
        //test.hunt(player.getpos());
        //test.PerformActions(test.state);
        test.updateState(test.getState(), test);
>>>>>>> parent of e309c11 (Finish)
        window.clear();
        player.update(deltaTime, grid, enemies);
        for (auto& enemy : enemies) {
            //enemy->update(deltaTime, grid);
        }

        window.clear();
        grid.draw(window);

        for (const auto& btenemy : btenemies)
        {
            window.draw(btenemy->radius);
            //window.draw(btenemy->radiusVision);
            window.draw(btenemy->shape);
        }


        for (auto& btenemy : btenemies) {
            window.draw(btenemy->fov_Vizualisation);
        }

        window.draw(player.shape);
<<<<<<< HEAD
=======
        window.draw(test.shape);
>>>>>>> parent of e309c11 (Finish)
        for (const auto& enemy : enemies) {
            if (enemy->isAlive()) {
                window.draw(enemy->shape);
            }
        }
        window.display();
    }
    return 0;
}
