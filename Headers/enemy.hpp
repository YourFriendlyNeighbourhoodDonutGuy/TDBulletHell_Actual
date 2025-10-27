//
// Created by jamie on 14/08/2025.
//

#ifndef CLION_TEST_ENEMY_HPP
#define CLION_TEST_ENEMY_HPP
#include "player.hpp"

//inherits the base class player so a basic constructor, draw function and variables are made.
class enemy{
private:
    float x = 0;
    float y = 0;
    float VEL = 3;
    float width = 0;
    float height = 0;
    int capacity = 0;
    int enemyCapacity = 0;
    sf::Color color;
    sf::RectangleShape shape;
    std::vector<enemy>Enemies;
    std::vector<bullet>Bullets;
public:
    enemy(float x, float y, float width, float height, sf::Color color, int capacity, int enemyCapacity);
    //spawning the enemies into the screen
    void spawn(sf::RenderWindow &window);

    void move(float playerPosX, float playerPosY);

    //Draw function to be passed into the spawn function
    void draw(sf::RenderWindow &window, float playerPosX, float playerPosY);
    // be able to get the width of the enemy
    float getWidth();

};
#endif //CLION_TEST_ENEMY_HPP