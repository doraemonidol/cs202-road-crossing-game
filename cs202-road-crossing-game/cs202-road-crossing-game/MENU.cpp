#include "MENU.h"
#include "UTILS.h"
#include "main.h"

MENU::MENU() { }

MENU::MENU(float width, float height)
{
    if (!font.loadFromFile("Fonts/upheavtt.ttf")) {
        // handle error
    }

    sf::Color color[] = { sf::Color::White, sf::Color(248, 208, 146), sf::Color(248, 208, 146) };
    menu[0] = new BUTTON("Play", "PressStart2P-Regular.ttf", 21, sf::Vector2f(155.f, 40.f), "pointer.png", color);
    menu[0]->setPosition(sf::Vector2f(323, 286));
    menu[1] = new BUTTON("Options", "PressStart2P-Regular.ttf", 21, sf::Vector2f(205.f, 40.f), "pointer.png", color);
    menu[1]->setPosition(sf::Vector2f(333-40, 332));
    menu[2] = new BUTTON("Exit", "PressStart2P-Regular.ttf", 21, sf::Vector2f(155.f, 40.f), "pointer.png", color);
    menu[2]->setPosition(sf::Vector2f(323, 378));

    selectedItemIndex = 0;
    if (!this->worldBackgroundTex.loadFromFile("Textures/Menu-BG.png")) {
    //if (!this->worldBackgroundTex.loadFromFile("Textures/menu-bg-sample.png")) {
        std::cout << "ERROR::MENU::COULD NOT LOAD BACKGROUND TEXTURE"
                  << "\n";
    }
    if (!this->titleTex.loadFromFile("Textures/title.png")) {
        std::cout << "ERROR::MENU::COULD NOT LOAD TITLE TEXTURE"
                  << "\n";
    }
}

MENU::~MENU()
{
}

void MENU::init()
{
    this->worldBackground.setTexture(this->worldBackgroundTex);
    this->title.setTexture(this->titleTex);
    this->title.setPosition(170, 85);
    menu[selectedItemIndex]->onHover();

}

void MENU::draw(sf::RenderWindow* window)
{
    window->draw(this->worldBackground);
    window->draw(this->title);
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
            this->menu[i]->drawTo(window);
    }
}

void MENU::MoveUp()
{
    if (selectedItemIndex - 1 >= 0) {
        menu[selectedItemIndex]->onDefault();
        selectedItemIndex--;
        menu[selectedItemIndex]->onHover();
    }
}

void MENU::MoveDown()
{
    if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS) {
        menu[selectedItemIndex]->onDefault();
        selectedItemIndex++;
        menu[selectedItemIndex]->onHover();
    }
}

int MENU::update(sf::RenderWindow* window, sf::Event e) {
    int ret;
    if (e.type == sf::Event::KeyPressed) {
        switch (e.key.code) {
        case sf::Keyboard::Up:
            MoveUp();
            break;
        case sf::Keyboard::Down:
            MoveDown();
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++) {
        int state = this->menu[i]->update(window, e);
        switch (state) {
        case ACTIVE:
            return i;
        case HOVER:
            if (i != selectedItemIndex) {
                menu[selectedItemIndex]->onDefault();
                selectedItemIndex = i;
            }
            break;
        default:
            break;
        }
    }
}