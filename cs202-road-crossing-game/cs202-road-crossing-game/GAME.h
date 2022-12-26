#pragma once
#include "SPACESHIP.h"
#include "BULLET.h"
#include "MENU.h"
#include "SCREEN_MANAGER.h"  
#include "SoundEffect.hpp"
#include "SoundManager.hpp"
#include "ENEMY_CONTROLLER.h"

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
#define FPS 60.f
enum Scene;
enum btnFunc;
enum pauseMenuBtn;

class GUI;
class SCENE_MANAGER;

class GAME {
private:
    //Window
    sf::RenderWindow* window;
    sf::View view;

    //Game state
    bool isPause, isDead;

    //Textures
    std::map<std::string, sf::Texture*> textures;
    //std::vector<Bullet*> bullets;

    //Systems
    unsigned level, scene;
    float deltaTime = 0.0f;
    
    sf::Clock clock;
    SCENE_MANAGER sceneManager;
    ENEMY_CONTROLLER enemyController;
    LEVEL_MANAGER levelManager;

    //Player
    SPACESHIP* player;
    std::vector<BULLET*>  bullets;
    sf::Time bulletLoadTime;
    sf::Clock bulletClock;
    int remainBullets;
    GUI* gui;

    //Scene
    MENU menu;

    //Sound
    SoundManager* soundController;
    std::map<std::string, std::string> music = { { "TITLE", "Sound/Title Theme.wav" },
        { "LOSE", "Sound/lose.wav" },
        { "WIN", "Sound/win.wav" },
        { "INGAME", "Sound/background-music-3.wav" },
        { "PRESS_SFX", "Sound/btn-confirm.wav " }, 
        { "SWITCH_SFX", "Sound/btn-switch.wav " } };

    //Private functions
    void initWindow();
    void initView();
    void initTextures();
    void initSystems();
    void initGUI();
    void initMenu();
    void initEnemy();
    void initPlayer();

public:
    GAME();
    GAME(const int a);
    ~GAME();

    GAME& operator=(GAME other);

    //Functions
    void run();

    void updatePollEvents();
    void updateInput();
    void updateWorld();
    void updateView();
    void updateBullets();
    void updateEnemies();
    void update();

    void renderWorld();
    void renderBullets();
    void renderEnemies();
    void render();

    void saveGame();
    void loadGame();
    void resetGame();

    void checkCollision();
    void playerShoot();
    void removeBullet();
    void loadBullet();
    void setSPACESHIP(SPACESHIP player);
    void setGUI(GUI gui);
    void setClocK(sf::Clock clock);
    void setDeltaTime(float deltaTime);
    void setLevel(unsigned level);
    void setScene(unsigned scene);
    void setWindow(sf::RenderWindow window);
    void setView(sf::View view);
    void setIsPause(bool isPause);

    void playMusic(std::string file);
    void playSound(std::string file);
};
