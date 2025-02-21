#ifndef GRID_HPP
#define GRID_HPP

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <iostream>


const int GRID_WIDTH = 38;
const int GRID_HEIGHT = 30;
const int CELL_SIZE = 40;

struct Cell {
    bool walkable;
    sf::Vector2f position;
    sf::RectangleShape shape;
};

class Grid {
public:
    Grid();
    void loadFromFile(const std::string& filename);
    void draw(sf::RenderWindow& window);
    Cell& getCell(int x, int y);

    bool isWalkable(int x, int y) {
        return cells[y][x].walkable;
    }

    std::vector<std::vector<Cell>> cells;
};

#endif      
