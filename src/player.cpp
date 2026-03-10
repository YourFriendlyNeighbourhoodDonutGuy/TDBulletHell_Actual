//
// Created by jamie on 15/07/25.
//
#include <iostream>
#include "player.hpp"
#include "bullet.hpp"
player::player(float x, float y, float width, float height, int health, sf::Color color, int capacity) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->health = health;
    this->color = color;
    this->capacity = capacity;
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(color);
    shape.setPosition({x,y});
    shape.setOrigin({width/2,height/2});

}

void player::draw(sf::RenderWindow &window) {
    if (this->health > 0) {
        window.draw(shape);
        for (bullet& b : Bullets) {
            if (b.getState() == bulletState::isFired) {
                b.move(3);
                b.collide(window);
                window.draw(b.shape);
            }
        }
    }


}

void player::move(sf::Angle rotateAngle) {
    // changes rotation angle depending on the rotation angle which should be in radians
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape.rotate(rotateAngle);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape.rotate(-rotateAngle);
    }
}

void player::bulletHandler(const std::optional<sf::Event>& event) {
    // if there are no bullets, then create bullets but don't draw them now
    if (Bullets.size() < capacity && sf::Keyboard::isKeyPressed( sf::Keyboard::Key::R)){
        for (int i = 0; i < Bullets.size() - capacity; i++) {
            bullet bullet{this->shape.getPosition().x, this->shape.getPosition().y, 10,10, 10, sf::Color::Yellow};
            Bullets.push_back(bullet);
            std::cout << this->shape.getPosition().x << std::endl;
        }
    }
    if (event->is<sf::Event::KeyPressed>()) {
        if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::F) {
            for (bullet& b : Bullets) {
                if (b.getState() == bulletState::isIdle && b.getState() != bulletState::isCollided) {
                    b.setState(bulletState::isFired);
                    b.setAngle(shape.getRotation());
                    break;
                }
            }
        }
    }
    Bullets.erase(
        // an expression to remove bullets from a vector starting from the beginning to the end of the vector.
         std::remove_if(Bullets.begin(), Bullets.end(), [this](bullet& b) {
             if (b.getState() == bulletState::isCollided) {
                 std::cout << Bullets.size() << std::endl;
                 return true; // Remove this task
             }
             return false; // Keep it
         }),
         Bullets.end());
}




sf::Vector2f player::getPosition() {
    return shape.getPosition();
}

sf::Vector2f player::getSize() {
    return shape.getSize();
}

int player::getHealth() {
    return health;
}

void player::setHealth(int health) {
    this->health = health;
}

sf::FloatRect player::getBounds() {
    return this->shape.getGlobalBounds();
}

std::vector<bullet>& player::getBullets() {
    return Bullets;
}

void player::setBullets(std::vector<bullet> bullets) {
    Bullets = bullets;
}


