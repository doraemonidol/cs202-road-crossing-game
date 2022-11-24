#pragma once
#include "SPACESHIP.h"
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;

class GUI;

class GAME {
private:
    //Window
    sf::RenderWindow* window;
    sf::View view;

    //Textures
    std::map<std::string, sf::Texture*> textures;
    //std::vector<Bullet*> bullets;

    //Systems
    unsigned level;
    float deltaTime = 0.0f;
    sf::Clock clock;

    //Player
    SPACESHIP* player;
    GUI* gui;

    //Enemies
    float spawnTimer;
    float spawnTimerMax;
    std::vector<SPACESHIP*> spaceship;
    std::vector<OBSTACLE*> obstacle;

    //Private functions
    void initWindow();
    void initView();
    void initTextures();
    void initSystems();
    void initGUI();

    void initPlayer();
    void initEnemies();

public:
    GAME();
    virtual ~GAME();

    //Functions
    void run();

    void updatePollEvents();
    void updateInput();
    void updateWorld();
    void updateView();
    //void updateBullets();
    //void updateEnemies();
    //void updateCombat();
    void update();

    void renderWorld();
    void render();
};
