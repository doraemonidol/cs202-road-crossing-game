#pragma once
#include "SFML/Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 3
enum Scene;

class BUTTON;

class MENU {
public:
    MENU();
    MENU(float width, float height);
    ~MENU();

    void init();
    void draw(sf::RenderWindow* window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int update(sf::RenderWindow* window, sf::Event e);

private:
    int selectedItemIndex = 0;
    sf::Font font;
    BUTTON* menu[MAX_NUMBER_OF_ITEMS];
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Texture titleTex;
    sf::Sprite title;
};
