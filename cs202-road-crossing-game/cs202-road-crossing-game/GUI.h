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

    //GUI
    sf::Font font;
    sf::Text levelText;
    sf::Text pauseText;
    sf::Text loseText;
    sf::Text winText;
    OPTIONS* pauseMenu, *loseMenu, *winMenu;

    //PlayerGUI
    sf::Sprite playerHp[4];
    sf::Sprite loseTitle, winTitle;
    float pauseMenuDisplacement, winLoseDisplacement;

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
    void update(int level);
    void render();

    // Game pause
    void renderGamePause();
    void updateGamePause();

    void initPauseMenu();
    int updatePauseMenu(sf::Event e);
    void renderPauseMenu();
    void closePauseMenu();

    // Lose menu
    void initLose();
    int updateLoseMenu(sf::Event e);
    void renderLose();
    void closeLose();

    // Win menu
    void initWin();
    int updateWinMenu(sf::Event e);
    void renderWin();
    void closeWin();
};
