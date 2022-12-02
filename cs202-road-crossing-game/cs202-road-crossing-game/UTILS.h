#pragma once

#include "main.h"
enum btnState;
class BUTTON {
public:
    BUTTON() { }
    BUTTON(std::string t, int charSize, sf::Vector2f size, sf::Color bgColor, sf::Color textColor);
    BUTTON(std::string hoverT, std::string activeT, std::string defaultT);
    BUTTON(std::string t, std::string fon, int charSize, sf::Vector2f size, sf::Color bgColor[btnStateCnt], sf::Color textColor[btnStateCnt]);
    BUTTON(std::string t, std::string fon, int charSize, sf::Vector2f size, std::string activeTexture, sf::Color textColor[btnStateCnt]);

    void setFont(std::string fon);
    void setBackColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPosition(sf::Vector2f pos);
    void setTexture(std::string hoverT, std::string activeT, std::string defaultT);
    void drawTo(sf::RenderWindow* window);
    bool isMouseOver(sf::RenderWindow* window);
    void onDefault();
    void onClick();
    void onHover();
    int update(sf::RenderWindow* window, sf::Event e);

private:
    sf::RectangleShape button;
    sf::Texture texture[btnStateCnt];
    sf::Color bgColor[btnStateCnt], textColor[btnStateCnt];
    sf::Sprite activeSprite;
    int type;
    sf::Font font;
    unsigned state;
    sf::Text text;
};

class UTILS {
};
