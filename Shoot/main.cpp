#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <stdio.h>
#include <sstream>
#include <windows.h>
#include <iostream>

#include "MainMenu.h"
#include "LoseScreen.h"
#include "WinScreen.h"

//макросы
#define PI 3.14159265 //действительно
#define CIRCLE_IN_NUM 5 //для
#define CIRCLE_OUT_NUM 9 //векторов
#define CIRCLE_RADIUS 10 //радиус круга
#define CIRCLE_CENTER_RADIUS 40 // радиус централого круга(окружности)
#define RAY_LENGTH 130 //длина моего штыка
#define CENTER_X 170 //кордината
#define CENTER_Y 125 //кордината
#define SPEED 0.00005 //Эну тут ясно

using namespace std;

sf::CircleShape center_circle(CIRCLE_CENTER_RADIUS); //окружность сфмл библ.

vector<sf::CircleShape> circles_in(CIRCLE_IN_NUM + CIRCLE_OUT_NUM,
    sf::CircleShape(CIRCLE_RADIUS)); //вектора штыков 

vector<sf::CircleShape> circles_out(CIRCLE_OUT_NUM, sf::CircleShape(CIRCLE_RADIUS)); //вне и внутри

vector<sf::RectangleShape> rays(CIRCLE_IN_NUM + CIRCLE_OUT_NUM, 
    sf::RectangleShape(sf::Vector2f(RAY_LENGTH, 1))); //сами палочки от штіков


int counter = 0; //число кружочков что попал и
    
sf::Text level_text; //уровень кружка

int level = 1; //тоже уровень кружка

double angles[CIRCLE_OUT_NUM + CIRCLE_OUT_NUM] = { 0,1.25,2.5,3.75,5,
PI / 2,PI / 2,PI / 2,PI / 2,PI / 2,PI / 2,PI / 2,PI / 2,PI / 2 };
//Массив углов для определения положения окружностей.
// Значения в массиве(дабл) используются для распределения штіков вокруг кружка.






struct coordinate { // стурктура для кординатніх точек
    double x;
    double y;
} address[CIRCLE_IN_NUM + CIRCLE_OUT_NUM]; //сходу создаем массив кординат

string convert_string(int num) {
    stringstream p;
    p << num;
    return p.str();
} //конверт в стринг числа

void display(sf::RenderWindow& window) {
    window.clear(sf::Color::White);
    //рисуем круги и линии вокруг центра
    for (int i = 0; i < 5 + counter; i++) {
        window.draw(circles_in[i]);
        window.draw(rays[i]);
    }
    //рисуем кружочки снизу
    for (int i = counter; i < 9; i++) {
        window.draw(circles_out[i]);
    }
    //рисуем черній кружок
    window.draw(center_circle);

    //відображення
    window.draw(level_text);
    window.display();
}

void resetGame() {
    counter = 0; // ресет штіков итд
    level = 1; // Reset the level

    // ресет углов 
    angles[0] = 0;
    angles[1] = 1.25;
    angles[2] = 2.5;
    angles[3] = 3.75;
    angles[4] = 5;

    for (int i = 5; i <= CIRCLE_OUT_NUM + CIRCLE_OUT_NUM; i++) {
        angles[i] = PI / 2;
    }

    // Reset the positions of the circles
    for (int i = 0; i < CIRCLE_OUT_NUM; i++) {
        circles_out[i].setPosition(195 - 25 * i, 360);
    }
}

bool lose() {
    //check the collision of the circle and the circles around the center 
    //проверка на то, что штіки соприкасаются
    for (int i = 0; i < CIRCLE_IN_NUM + counter; i++) {
        for (int j = i + 1; j < CIRCLE_IN_NUM + counter; j++) {
            if (sqrt(pow(address[i].x - address[j].x, 2) + pow(address[i].y - address[j].y, 2)) <= 2 * CIRCLE_RADIUS) {
                return true;
            }
        }
    }
    return false;
}





void initializeGame() {
   

    sf::Time postpone = sf::seconds(2); //время для задержки
    sf::Font font;
    font.loadFromFile("OLDENGL.TTF"); //подгрузочка шрифта

    center_circle.setFillColor(sf::Color::Black); //цвет круга
    center_circle.setPosition(CENTER_X, CENTER_Y); //его позиция

    // Установка начальніх позиций линий в массиве
    for (int i = 0; i < CIRCLE_IN_NUM + CIRCLE_OUT_NUM; i++) {
        rays[i].setPosition(210, 165);
    }

    // Инициализация кругов внутри центральной окружности
    for (int i = 0; i < CIRCLE_OUT_NUM; i++) {
        circles_out[i].setFillColor(sf::Color::Black);
        circles_out[i].setPosition(195 - 25 * i, 360);
    }

    sf::RenderWindow windowGame(sf::VideoMode(400, 500), "Shoot"); //создаем окно игри

    while (windowGame.isOpen()) {
        sf::Event event; //ивент библиотечный

            // Обновление свойств линий и кругов внутри центральной окружности
        for (int i = 0; i < CIRCLE_IN_NUM + counter; i++) {
            rays[i].setFillColor(sf::Color::Black); // Установка цвета линии
            rays[i].setRotation(angles[i] * 180 / PI); // Установка поворота линии

        // Установка позиции и цвета кругов внутри КРУЖОЧКА
            circles_in[i].setPosition(130 * cos(angles[i]) + 202, 130 * sin(angles[i]) + 152);
            circles_in[i].setFillColor(sf::Color::Black);

        // Обновление координат штыков
            address[i].x = 130 * cos(angles[i]) + 200;
            address[i].y = 130 * sin(angles[i]) + 150;

        // Обновление угла для следующего кадра
            angles[i] += SPEED * level;
        }

        windowGame.clear(sf::Color::White);

        //чек на победу
        if (counter == CIRCLE_OUT_NUM) {
            windowGame.clear(sf::Color::White);
            WinScreen winScreen;

            winScreen.draw(windowGame);
            windowGame.display();
            sleep(postpone);
            counter = 0;
            level++;

            //обнова настроек при вине
            angles[0] = 0;
            angles[1] = 1.25;
            angles[2] = 2.5;
            angles[3] = 3.75;
            angles[4] = 5;

            for (int i = 5; i <= CIRCLE_OUT_NUM + CIRCLE_OUT_NUM; i++) {
                angles[i] = PI / 2;
            }
            for (int i = 0; i < CIRCLE_OUT_NUM; i++) {
                circles_out[i].setPosition(195 - 25 * i, 360);
            }
        }

        //чекна ивент закрытия окна
        while (windowGame.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                windowGame.close();
                break;
            case sf::Event::KeyPressed: //чек на нажатие кнопки вверх
                // Обработка события нажатия клавиши вверх
                if (event.key.code == sf::Keyboard::Up) {
                    int y = 360;

                    // Анимация летящих штыков
                    while (y >= 280) {
                        circles_out[counter].setPosition(195, y);
                        y -= 2;
                        display(windowGame); // Перерисовка окна
                    }

                    // Установка позиции и адреса нового круга внутри кружка
                    circles_in[CIRCLE_IN_NUM + counter].setPosition(195, 280);
                    address[CIRCLE_IN_NUM + counter].x = 195;
                    address[CIRCLE_IN_NUM + counter].y = 280;
                    counter++; // Увеличение счетчика кругов

                    int x = 1;

                    // Анимация распределения кругов снаружи кружка
                    while (x <= 25) {
                        for (int i = counter; i < CIRCLE_OUT_NUM; i++) {
                            circles_out[i].setPosition(195 - 25 * i + x * counter, 360);
                        }
                        x += 2;
                        display(windowGame); // Перерисовка окна
                    }
                }
                break; // Завершение обработки события нажатия клавиши 

            }
        }

        //настраиваем текст уровня
        level_text.setFont(font); //шрифт
        level_text.setPosition(CENTER_X + 30, CENTER_Y + 15);//позиция
        level_text.setCharacterSize(40);//Сайз
        level_text.setString(convert_string(level));//конвертим в стринг инкрементационный левел

        //check losing
        if (lose()) {
            LoseScreen loseScreen;

            windowGame.clear(sf::Color::White);
            loseScreen.draw(windowGame);
            windowGame.display(); // Отображаем изменения

            // Задержка перед сбросом
            sleep(postpone);

            resetGame();

        }

        display(windowGame);
    }
}

int main() {

    
    sf::RenderWindow window(sf::VideoMode(270, 410), "MainScreen"); //старт скрин
    MainMenu mainMenu;

    bool startGame = false;

    while (window.isOpen() && startGame == false) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } //базовый чек на закрытие окна

            if (!startGame && event.type == sf::Event::MouseButtonPressed
                && event.mouseButton.button == sf::Mouse::Left) { //чек нажатией клавишей на кнопку старт

                sf::Vector2f mousePosition(static_cast<float>(event.mouseButton.x), 
                    static_cast<float>(event.mouseButton.y));

                if (mainMenu.isStartButtonPressed(mousePosition)) {

                    // нажалась кнопка старта

                    startGame = true;
                    window.close();
                    break;
                }
            }
        }

        window.clear(sf::Color::White);

        if (!startGame) {
            mainMenu.draw(window);
        }
        else {
            initializeGame();
        }

        window.display();
    }

    return 0;
}
