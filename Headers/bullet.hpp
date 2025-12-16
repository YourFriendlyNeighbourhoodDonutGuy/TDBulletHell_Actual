//
// Created by jamie on 15/07/25.
//

#ifndef BULLET_HPP
#define BULLET_HPP
#include <SFML/Graphics.hpp>

#include "enemy.hpp"

enum class bulletState {
    isCollided,
    isFired,
    isIdle
};

class bullet {
private:
        float x = 0;
        float y = 0;
        float width = 0;
        float height = 0;
        int damage = 0;
        sf::Angle rotateAngle;
        bulletState state;
        sf::Color color;
public:
    sf::RectangleShape shape;
    bullet(float x, float y, float width, float height,int damage,  sf::Color color);
    void move(float VEL);
    void collide(const sf::RenderWindow &window);
    void enemyCollision(const sf::RenderWindow &window, enemy &enemy);
    void setState(bulletState state);
    void setAngle(sf::Angle rotateAngle);
    bulletState getState();
};
#endif //BULLET_HPP
