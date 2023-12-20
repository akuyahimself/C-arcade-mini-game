#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <sstream>
#include <iostream>

class WinScreen {


public:
    WinScreen() {
        imageTexture.loadFromFile("C:/Users/arthu/source/repos/Shoot/Shoot/images/win.png");
        win.setSize(sf::Vector2f(280, 330));
        win.setPosition(50, 10);
        win.setTexture(&imageTexture);

    }

    sf::RectangleShape getWin() {
        std::cout << "\n" << "Win gotted!!!" << "\n";
        return win;
    }


    void draw(sf::RenderWindow& window) {
        window.draw(win);

    }
private:
    sf::Texture imageTexture;
    sf::RectangleShape win;
};
