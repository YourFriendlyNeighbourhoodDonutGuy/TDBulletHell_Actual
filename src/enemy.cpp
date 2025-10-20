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
            std::uniform_real_distribution<float> posDistx(0, window.getSize().x - this->width );
            std::uniform_real_distribution<float> posDisty(0, window.getSize().y - this->width);

            float enemyPosX = posDistx(posGen);
            float enemyPosY = posDisty(posGen);

            enemy Enemy(enemyPosX, enemyPosY, this->width, this->height, this->color, this->capacity, this->enemyCapacity);
            Enemies.push_back(Enemy);
            std::cout << enemyPosX << "\n";
        }
    }

}

void enemy::draw(sf::RenderWindow &window) {
    for (enemy& e: Enemies) {
        window.draw(e.shape);
    }

}

float enemy::getWidth() {
    return this->width;
}




