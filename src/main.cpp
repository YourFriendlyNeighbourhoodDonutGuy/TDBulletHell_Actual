#include <iostream>
#include <random>
#include <SFML/Graphics.hpp>
#include <vector>

#include "enemy.hpp"
#include "../Headers/player.hpp"

#include "../Headers/enemy.hpp"
// TIP To <b>Run</b> code, press <shortcut actionId="Run"/> or click the <icon src="AllIcons.Actions.Execute"/> icon in the gutter.



int main() {
    sf::RenderWindow window(sf::VideoMode({300,300}), "SFML window");
    const float playerPosX = window.getSize().x / 2;
    const float playerPosY = window.getSize().y / 2;

    //enemy variables
    enemy enemy(1.f,2.f,30.f,30.f,100,25 ,sf::Color::Red, 8, 5);

    player player{playerPosX, playerPosY, 30.0f, 30.0f, 100,sf::Color::White, 8};

    window.setFramerateLimit(60);
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent())
            {
            if (event->is<sf::Event::Closed>())
                window.close();
            player.bulletHandler(event);
            }

        window.clear();
        player.draw(window);
        player.move(sf::radians(0.1f));
        enemy.spawn(window);
        enemy.draw(window, player);
        window.display();
    }
}