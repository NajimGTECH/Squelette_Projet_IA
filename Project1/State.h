#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>


using namespace sf;
using namespace std;

class State {
public:
    bool isPatrolling = true; 
    bool isHunting = false;    
    bool isSearching = false;  
    bool shouldFlee = false;    
    int healthGOAP = 100;
    Vector2f positionGOAP;

    bool getPatrolling() const { return isPatrolling; }
    bool getHunting() const { return isHunting; }
    bool getSearching() const { return isSearching; }
    bool getShouldFlee() const { return shouldFlee; }

    int getHealthstate() const { return healthGOAP; }
    Vector2f getPosState() const { return positionGOAP; }


    void setPatrolling(bool p) { isPatrolling = p; }
    void setHunting(bool h) { isHunting = h; }
    void setSearching(bool s) { isSearching = s; }
    void setShouldFlee(bool f) { shouldFlee = f; }
};


