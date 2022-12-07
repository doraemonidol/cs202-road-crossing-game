#pragma once
#include "SFML/Graphics.hpp"

enum Scene;
enum Alignment;

class BUTTON;

class OPTIONS {
public:
    OPTIONS();
    OPTIONS(std::vector<std::string> but, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[], int index);
    ~OPTIONS();

    void init();
    void addButton(std::string t, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[], int index);
    void draw(sf::RenderWindow* window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int update(sf::RenderWindow* window, sf::Event e);
    void unpdateButtonDisplacement(sf::Vector2f pos);
    void movePos(sf::Vector2f pos);
    void alignButtons(int type);
    void tidyButtons(float padding);

private:
    int selectedItemIndex = 0;
    sf::Font font;
    std::vector<BUTTON*> button;
    sf::Vector2f pos;
};