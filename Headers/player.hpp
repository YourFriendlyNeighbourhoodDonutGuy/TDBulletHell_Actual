//
// Created by jamie on 15/07/25.
//

#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <SFML/Graphics.hpp>

#include "bullet.hpp"

class player {
private:
    float x = 0;
    float y = 0;
    float width = 0;
    float height = 0;
    int capacity = 0;
    std::vector<bullet> Bullets;
    sf::Angle rotateAngle;
    sf::Color color;
    sf::RectangleShape shape;
public:
    player(float x, float y ,float width, float height, sf::Color color, int capacity);
    //handles drawing the player to the screen
    void draw(sf::RenderWindow &window);

    // handles player movement
    void move(sf::Angle rotateAngle);

    void bulletHandler(const std::optional<sf::Event>& event);

    
};
#endif //PLAYER_HPP
