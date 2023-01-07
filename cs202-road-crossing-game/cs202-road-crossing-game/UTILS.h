#pragma once

enum btnState;
class BUTTON {
public:
    BUTTON() { }
    BUTTON(std::string t, int charSize, sf::Vector2f size, sf::Color bgColor, sf::Color textColor);
    BUTTON(std::string hoverT, std::string activeT, std::string defaultT);
    BUTTON(std::string t, std::string fon, int charSize, sf::Vector2f size, sf::Color bgColor[btnStateCnt], sf::Color textColor[btnStateCnt]);
    BUTTON(std::string t, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[btnStateCnt], int index);
    BUTTON(std::string, sf::Vector2u imgCnt, float switchTime, sf::Vector2f, int index);

    void setFont(std::string fon);
    void setBackColor(sf::Color color);
    void setTextColor(sf::Color color);
    void setPosition(sf::Vector2f pos);
    void movePosition(sf::Vector2f pos);
    void movePosition2(sf::Vector2f pos);
    void updateDisplacement(sf::Vector2f pos);
    void setTexture(std::string hoverT, std::string activeT, std::string defaultT);
    void drawTo(sf::RenderWindow* window);
    bool isMouseOver(sf::RenderWindow* window);
    void onDefault();
    void onClick();
    void onHover();
    int update(sf::RenderWindow* window, sf::Event e, float deltaTime);
    int updateAnim(float deltaTime);
    sf::FloatRect getSize();
    int getIndex();
    void changeText(std::string newText);
    std::string getText();
    void saveGame(std::string fileName);
private:
    sf::RectangleShape button;
    ANIMATION switchAnim;
    sf::Texture texture[btnStateCnt];
    sf::Color bgColor[btnStateCnt], textColor[btnStateCnt];
    sf::Sprite activeSprite;
    int type, index;
    sf::Font font;
    unsigned state;
    sf::Text text;
    sf::Vector2f pos;
    bool isPlayingAnim;
    int toReturn;
};

class UTILS {
};


class Textbox {
public:
    Textbox(sf::RenderWindow& windowToUse, sf::Font& fontToUse);
    void setDimensons(double newX, double newY, double newWidth, double newHeight);
    void draw();
    void setString(std::string newString);
    std::string getString();
    bool pollEvent(sf::Event event);
    void setFocus(bool newFocus);
    void setReturnEvent(void (*newFunctionToCall)());
    void setWarning(bool warning);
private:
    bool isFocused = true;
    double x;
    double y;
    double width;
    double height;
    bool isWarning = false;
    std::string string = "";
    sf::Font& font;
    sf::RenderWindow& window;
    sf::RectangleShape background;
    sf::Text text;
    sf::Text title;
    sf::Text warning;
    bool enterText(sf::Uint32 unicode);
};
