#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

class LoseScreen {
public:
    LoseScreen() {
        buttonTexture.loadFromFile("C:/Users/arthu/source/repos/Shoot/Shoot/images/lose.png");
        lose.setSize(sf::Vector2f(330, 330));
        lose.setPosition(60, 90);
        lose.setTexture(&buttonTexture);

    }

    sf::RectangleShape getLose() {
        std::cout << "\n" << "Lose gotted!!!" << "\n";
        return lose;
    }


    void draw(sf::RenderWindow& window) {
        window.draw(lose);

    }

private:
    sf::Texture buttonTexture;
    sf::RectangleShape lose;
};


