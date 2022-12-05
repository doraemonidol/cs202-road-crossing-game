#pragma once
#include "SFML/Graphics.hpp"
#include "OPTIONS.h"
/**
MAIN (1)
  |- PLAY (2)
  |  |- NEW GAME (3)
  |  |- LOAD GAME (4)
  |- SETTING (5)
  |  |- SOUND : ON (6)
  |  |- THEME (7)
  |  |  |- DEFAULT
  |- EXIT (8)
**/
enum Scene;

class BUTTON;

class MENU {
public:
    MENU();
    MENU(float width, float height);
    ~MENU();

    void init();
    void draw(sf::RenderWindow* window);
    int update(sf::RenderWindow* window, sf::Event e);

private:
    sf::Font font;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    sf::Texture titleTex;
    sf::Sprite title;
    OPTIONS *mainMenu, *playBtn, *settingBtn, *curState;
};