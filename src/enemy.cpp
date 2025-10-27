#include <iostream>
#include "../Headers/enemy.hpp"

#include <random>

enemy::enemy(float x, float y ,float width, float height, sf::Color color, int capacity, int enemyCapacity){
    this-> x = x;
    this-> y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->capacity = capacity;
    this->enemyCapacity = enemyCapacity;
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    shape.setPosition({x,y});
}

void enemy::spawn(sf::RenderWindow &window) {

    if (Enemies.size() < enemyCapacity) {
        for (int i = 0; i < this->enemyCapacity; i++) {
            std::mt19937 posGen(std::random_device{}());
            std::uniform_real_distribution<float> posDistx(0, window.getSize().x);
            std::uniform_real_distribution<float> posDisty(0, window.getSize().y);

            float enemyPosX = posDistx(posGen);
            float enemyPosY = posDisty(posGen);

            if (enemyPosY > enemyPosX) {
                enemyPosX = 0.f;
            }
            if (enemyPosX > enemyPosY) {
                enemyPosY = 0.f;
            }

            enemy Enemy(enemyPosX, enemyPosY, this->width, this->height, this->color, this->capacity, this->enemyCapacity);
            Enemies.push_back(Enemy);
            std::cout << enemyPosX << "\n";
        }
    }

}void enemy::move(float playerPosX, float playerPosY) {
    //make the enemies move towards the player
    float dx = 0.1f;
    float dy = 0.1f;
        if (shape.getPosition().x < playerPosX) {
            dx += this->VEL;
        }
        if (shape.getPosition().x > playerPosX) {
            dx -= this->VEL;
        }


        if (shape.getPosition().y< playerPosY) {
            dy += this->VEL;

        }
        if (shape.getPosition().y > playerPosY) {
            dy -= this->VEL;
        }

        shape.move({dx,dy});

    //rotate enemies to face the player
    //use radians
}




void enemy::draw(sf::RenderWindow &window, float playerPosX, float playerPosY) {
    for (enemy& e: Enemies) {
        e.move(playerPosX, playerPosY);
        window.draw(e.shape);
    }

}

float enemy::getWidth() {
    return this->width;
}




