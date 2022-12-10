#include "OPTIONS.h"
#include "MENU.h"
#include "UTILS.h"
#include "main.h"

MENU::MENU() { }

MENU::MENU(float width, float height)
{
    if (!font.loadFromFile("Fonts/upheavtt.ttf")) {
        // handle error
    }
    if (!this->worldBackgroundTex.loadFromFile("Textures/Menu-BG.png")) {
    //if (!this->worldBackgroundTex.loadFromFile("Textures/menu-bg-sample.png")) {
        std::cout << "ERROR::MENU::COULD NOT LOAD BACKGROUND TEXTURE"
                  << "\n";
    }
    if (!this->titleTex.loadFromFile("Textures/title.png")) {
        std::cout << "ERROR::MENU::COULD NOT LOAD TITLE TEXTURE"
                  << "\n";
    }
    playBtn = new OPTIONS;
    settingBtn = new OPTIONS;
    mainMenu = new OPTIONS;
}

MENU::~MENU()
{
}

void MENU::init()
{
    this->worldBackground.setTexture(this->worldBackgroundTex);
    this->title.setTexture(this->titleTex);
    this->title.setPosition(170, 85);
    sf::Color color[] = { sf::Color::White, sf::Color(248, 208, 146), sf::Color(248, 208, 146) };
    mainMenu->addButton("Play", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 1);
    playBtn->addButton("New Game", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 2);
    playBtn->addButton("Load Game", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 3);
    playBtn->addButton("Back", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 4);

    mainMenu->addButton("Setting", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 5);
    settingBtn->addButton("Sound: ON", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 6);
    settingBtn->addButton("Theme", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 7);
    settingBtn->addButton("Back", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 8);

    mainMenu->addButton("Exit", "PressStart2P-Regular.ttf", 21, "pointer.png", color, 9);
    this->mainMenu->tidyButtons(10);
    this->mainMenu->movePos(sf::Vector2f(0, 80));
    this->mainMenu->init();
    this->playBtn->tidyButtons(10);
    this->playBtn->movePos(sf::Vector2f(0, 80));
    this->playBtn->init();
    this->settingBtn->tidyButtons(10);
    this->settingBtn->movePos(sf::Vector2f(0, 80));
    this->settingBtn->init();
    curState = mainMenu;
}

void MENU::draw(sf::RenderWindow* window)
{
    window->draw(this->worldBackground);
    window->draw(this->title);
    curState->draw(window);
}

int MENU::update(sf::RenderWindow* window, sf::Event e) {
    int pressed = curState->update(window, e);
    switch (pressed) {
    case 1:
        curState = playBtn;
        break;
    case 2:
        return NEWGAME;
    case 3:
        return LOADGAME;
    case 4:
        std::cout << "back ";
        curState = mainMenu;
        break;
    case 5:
        curState = settingBtn;
        break;
    case 6:
        return TOGGLESOUND;
    case 7:
        return TOGGLETHEME;
    case 8:
        curState = mainMenu;
        break;
    case 9:
        return EXIT;
    }
    return -1;
}