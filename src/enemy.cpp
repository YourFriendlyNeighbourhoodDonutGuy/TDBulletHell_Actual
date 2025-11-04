#include <iostream>
#include "../Headers/enemy.hpp"

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
            std::cout << enemyPosX << "\n";
        }
    }

}

void enemy::move(player &player) {
    //make the enemies move towards the player
    sf::Vector2f movement = {0.1f, 0.1f};
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




void enemy::draw(sf::RenderWindow &window, player &player) {
    for (enemy& e: Enemies) {
        window.draw(e.shape);
        e.move(player);
    }

}

void enemy::collision(player &player, sf::Vector2f movement) {
    int playerHealth = player.getHealth();

    // handle damage dealt when enemy has collided with player
    sf::FloatRect shapeBounds = shape.getGlobalBounds();
    sf::FloatRect playerBounds = player.getBounds();
    std::optional<sf::FloatRect> playerIntersection = shapeBounds.findIntersection(playerBounds);
    if (playerIntersection.has_value()) {
        playerHealth = playerHealth - this->damage;
        shape.move(-movement);
    }

    player.setHealth(playerHealth);


}


float enemy::getWidth() {
    return this->width;
}




