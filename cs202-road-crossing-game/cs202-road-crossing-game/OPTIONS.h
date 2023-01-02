#pragma once

const std::string PRESS_SFX = "Sound/btn-confirm.wav";
const std::string SWITCH_SFX = "Sound/btn-switch.wav";

enum Scene;
enum Alignment;

class GAME;

class OPTIONS {
public:
    OPTIONS();
    OPTIONS(std::vector<std::string> but, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[], int index);
    ~OPTIONS();

    void init();
    void addButton(std::string t, std::string fon, int charSize, std::string activeTexture, sf::Color textColor[], int index);
    void addButton(BUTTON* button);
    
    void draw(sf::RenderWindow* window);
    void MoveUp();
    void MoveDown();
    int GetPressedItem() { return selectedItemIndex; }
    int update(sf::RenderWindow* window, sf::Event e, GAME* gm);
    int updateAnim(GAME* gm);
    void unpdateButtonDisplacement(sf::Vector2f pos);
    void movePos(sf::Vector2f pos);
    void movePos2(sf::Vector2f pos);
    void alignButtons(int type);
    void tidyButtons(float padding);
    void changeText(int index);

    // Sound
    SoundManager* soundController = nullptr;
    void pressSFX(GAME* gm);
    void switchSFX(GAME* gm);
    void attachSoundController(SoundManager* sm);

private:
    int selectedItemIndex = 0;
    sf::Font font;
    std::vector<BUTTON*> button;
    sf::Vector2f pos;
};