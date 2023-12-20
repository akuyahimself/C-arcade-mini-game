#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

class MainMenu {
public:
    MainMenu() {
        buttonTexture.loadFromFile("C:/Users/arthu/source/repos/Shoot/Shoot/images/start.png");
        startButton.setSize(sf::Vector2f(200, 200));
        startButton.setPosition(31, 180);
        startButton.setTexture(&buttonTexture);   

        logoTexture.loadFromFile("C:/Users/arthu/source/repos/Shoot/Shoot/images/logo.png");
        logoImage.setSize(sf::Vector2f(180, 150));
        logoImage.setPosition(50, 20);
        logoImage.setTexture(&logoTexture);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(startButton);
        window.draw(logoImage);

    }

    bool isStartButtonPressed(const sf::Vector2f& mousePosition) {
        return startButton.getGlobalBounds().contains(mousePosition);
    }

private:
    sf::Texture buttonTexture;
    sf::Texture logoTexture;
    sf::RectangleShape logoImage;
    sf::RectangleShape startButton;
};


