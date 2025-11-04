//
// Created by jamie on 14/08/2025.
//

#ifndef CLION_TEST_ENEMY_HPP
#define CLION_TEST_ENEMY_HPP
#include "player.hpp"
#include "bullet.hpp"

//inherits the base class player so a basic constructor, draw function and variables are made.
class enemy{
private:
    float x = 0;
    float y = 0;
    float VEL = 1;
    float width = 0;
    float height = 0;
    int health = 0;
    int damage = 0;
    int capacity = 0;
    int enemyCapacity = 0;
    sf::Color color;
    sf::RectangleShape shape;
    std::vector<enemy>Enemies;
    std::vector<bullet>Bullets;
public:
    enemy(float x, float y, float width, float height, int health, int damage, sf::Color color, int capacity, int enemyCapacity);
    //spawning the enemies into the screen
    void spawn(sf::RenderWindow &window);

    void move(player &player);

    //Draw function to be passed into the spawn function
    void draw(sf::RenderWindow &window, player &player);
    // be able to get the width of the enemy
    float getWidth();
    //handle enemy death and damage when colliding with player
    void collision(player &player, sf::Vector2f movement);

};
#endif //CLION_TEST_ENEMY_HPP