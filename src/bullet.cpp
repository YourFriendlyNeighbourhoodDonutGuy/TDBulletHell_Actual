//
// Created by jamie on 15/07/25.
//

#include "../Headers/bullet.hpp"
#include "enemy.hpp"
#include<cmath>
#include <iostream>

//constructor for the bullet class
bullet::bullet(float x, float y, float width, float height, int damage,  sf::Color color){
    this-> state = bulletState::isIdle;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->damage = damage;
    this->color = color;
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition({x,y});
    shape.setOrigin({width/2,height/2});
    shape.setFillColor(color);
}

//moves the bullet the agnle the player has rotated
void bullet::move(const float VEL) {
    float dy = sin(rotateAngle.asRadians()) * VEL;
    float dx = cos(rotateAngle.asRadians()) * VEL;
    shape.move({dx,dy});

}

//checks boundary collisions and changes state to isCollided
void bullet::collide(const sf::RenderWindow &window) {
    if (shape.getPosition().x >= window.getSize().x || shape.getPosition().y >= window.getSize().y || shape.getPosition().x <= 0 || shape.getPosition().y <= 0) {
        this->state = bulletState::isCollided;
    }
}

void bullet::enemyCollision(const sf::RenderWindow &window, enemy &Enemy) {
    sf::FloatRect bulletBounds = this -> shape.getGlobalBounds();
    sf::FloatRect enemyBounds = Enemy.getBounds();
    int enemyHealth = Enemy.getHealth();

    std::optional <sf::FloatRect> bulletIntersection = bulletBounds.findIntersection(enemyBounds);

    if (bulletIntersection.has_value() && enemyHealth > 0 && bullet::state == bulletState::isFired) {
        enemyHealth -= this->damage;
        this->state = bulletState::isCollided;
    }
    if (enemyHealth <=0 ) {
        Enemy.setState(enemyState::isDead);
    }

    Enemy.setHealth(enemyHealth);


}


void bullet::setState(bulletState state) {
    this->state = state;
}

void bullet::setAngle(sf::Angle rotateAngle) {
    this->rotateAngle = rotateAngle;
}

bulletState bullet::getState() {
    return this->state;
}








