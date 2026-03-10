#include <iostream>
#include "enemy.hpp"
#include "bullet.hpp"
#include "player.hpp"
#include <random>

enemy::enemy(float x, float y ,float width, float height, int health, int damage,sf::Color color, int capacity, int enemyCapacity){
    this-> x = x;
    this-> y = y;
    this->width = width;
    this->height = height;
    this->health = health;
    this->damage = damage;
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

            enemy Enemy(enemyPosX, enemyPosY, this->width, this->height, this->health,this->damage,this->color, this->capacity, this->enemyCapacity);
            Enemies.push_back(Enemy);
        }
    }

}

void enemy::move(player &player) {
    //make the enemies move towards the player
    sf::Vector2f movement = {0.1f, 0.1f};
    if (this->health > 0){
        if (shape.getPosition().x < player.getPosition().x) {
            movement.x += this->VEL;
        }
        if (shape.getPosition().x > player.getPosition().x) {
            movement.x -= this->VEL;
        }


        if (shape.getPosition().y< player.getPosition().y) {
            movement.y += this->VEL;

        }
        if (shape.getPosition().y > player.getPosition().y) {
            movement.y -= this->VEL;
        }

        shape.move(movement);

        collision(player, movement);

        //rotate enemies to face the player
        //use radians
    }
}



void enemy::draw(sf::RenderWindow &window, player &player) {
    for (enemy& e: Enemies) {
        std::vector<bullet> player_bullet = player.getBullets();
        if (e.state == enemyState::isAlive) {
            window.draw(e.shape);
            e.move(player);
            for (bullet& bull : player.getBullets()) {
                bull.enemyCollision(window, e);
            }
        }
        if (e.state == enemyState::isDead) {
            e.Remove();
        }
    }

}

void enemy::collision(player &player, sf::Vector2f movement) {
    int playerHealth = player.getHealth();
    // handle damage dealt when enemy has collided with player
    sf::FloatRect shapeBounds = this->shape.getGlobalBounds();
    sf::FloatRect playerBounds = player.getBounds();
    std::optional<sf::FloatRect> playerIntersection = shapeBounds.findIntersection(playerBounds);
    if (playerIntersection.has_value()) {
        if (playerHealth > 0) {
            playerHealth = playerHealth - this->damage;
        }
        shape.move(-movement);
    }

    player.setHealth(playerHealth);


}

void enemy::Remove() {
    Enemies.erase(
       // an expression to remove bullets from a vector starting from the beginning to the end of the vector.
        std::remove_if(Enemies.begin(), Enemies.end(), [this](enemy& e) {
            if (e.state == enemyState::isDead) {
                std::cout << "this happens";
                return true;
            }
            return false;
        }),
        Enemies.end());
}


float enemy::getWidth() {
    return this->width;
}

sf::FloatRect enemy::getBounds() {
    return shape.getGlobalBounds();
}

void enemy::setHealth(int health) {
    this->health = health;
}

int enemy::getHealth() {
    return this->health;
}

enemyState enemy::getState() {
    return this->state = state;
}

void enemy::setState(enemyState state) {
    this->state = state;
}







