#pragma once
#include "SPACESHIP.h"
#include "UTILS.h"
#include "OPTIONS.h"
enum pauseMenuBtn;

class GUI {
private:
    sf::RenderWindow* window;
    //Player
    SPACESHIP* player;

    //Textures
    std::map<std::string, sf::Texture*> textures;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    //std::vector<Bullet*> bullets;
    std::map<std::string, BUTTON*> buttons;

    //GUI
    sf::Font font;
    sf::Text levelText;
    sf::Text pauseText;
    sf::Text gameOverText;
    OPTIONS* pauseMenu;

    //PlayerGUI
    sf::Sprite playerHp[4];
    float pauseMenuDisplacement;

    //Private functions
    void initTextures();
    void initBG();
    void initGUI();

public:
    GUI();
    GUI(sf::RenderWindow* window, SPACESHIP* player);
    virtual ~GUI();

    float getDisplacement();
    sf::Vector2u getBGSize();
    sf::Sprite getSprite();

    //Functions
    void updateHealth(int health);
    void updateLevel(int level);
    void updateGamePause();
    int updatePauseMenu(sf::Event e);
    void update(int level);
    void renderGameOver();
    void renderGamePause();
    void renderPauseMenu();
    void initPauseMenu();
    void render();
    void closePauseMenu();
};
