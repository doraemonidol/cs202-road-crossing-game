#pragma once
#include "SPACESHIP.h"
#include "MENU.h"
#include "SoundEffect.hpp"
#include "SoundManager.hpp"
extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
enum Scene;
enum btnFunc;
enum pauseMenuBtn;

class GUI;
class MONSTER;
class OBSTACLE;

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

    //Player
    SPACESHIP* player;
    GUI* gui;

    //Scene
    MENU menu;

    //Enemies
    float spawnTimer;
    float spawnTimerMax;
    sf::Time spawnTimeCheck;
    std::vector<MONSTER*> monsters;
    std::vector<OBSTACLE*> obstacles;

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
    void saveGame();
    void loadGame();
    void removeOutOfBoundEnemies();
    void resetGame();
    void checkCollision();
    //set
    void setSPACESHIP(SPACESHIP player);
    void setGUI(GUI gui);
    void setSpawnTimer(float spawnTimer);
    void setSpawnTimerMax(float spawnTimerMax);
    void setClocK(sf::Clock clock);
    void setDeltaTime(float deltaTime);
    void setLevel(unsigned level);
    void setScene(unsigned scene);
    void setTextures(std::map<std::string, sf::Texture*> other);
    void setWindow(sf::RenderWindow window);
    void setView(sf::View view);
    void setIsPause(bool isPause);

    void playMusic(std::string file);
    void playSound(std::string file);

    GAME& operator=(GAME other);
};
