#pragma once
#include "SPACESHIP.h"
#include "MENU.h"
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
enum Scene;

class GUI;

class GAME {
private:
    //Window
    sf::RenderWindow* window;
    sf::View view;

    //Game state
    bool isPause;

    //Textures
    std::map<std::string, sf::Texture*> textures;
    //std::vector<Bullet*> bullets;

    //Systems
    unsigned level, scene;
    float deltaTime = 0.0f;
    sf::Clock clock;

    //Player
    SPACESHIP* player;
    GUI* gui;

    //Scene
    MENU menu;

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
    void initMenu();

    void initPlayer();
    void initEnemies();

public:
    GAME();
    GAME(const int a);
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
    void pauseGame();
    void renderWorld();
    void render();
    void renderGamePause();
    void saveGame();
    void loadGame();
    GAME& operator=(GAME other);
};
