#pragma once

extern const int SCREEN_HEIGHT;
extern const int SCREEN_WIDTH;
#define FPS 60.f
#define BULLET_RELOAD_TIME 5.0f
#define MAX_BULLET 5
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
    float deltaTime = 0.0f, totalTime = 0.0f;
    
    sf::Clock clock;
    SCENE_MANAGER sceneManager;
    ENEMY_CONTROLLER enemyController;
    LEVEL_MANAGER levelManager;

    //Player
    SPACESHIP* player;
    std::vector<BULLET*>  bullets;
    float bulletLoadTime;
    int remainBullets;
    GUI* gui;

    //Scene
    MENU menu;
    Textbox *textbox;
    sf::Font font;
    
    //Sound
    SoundManager* soundController;
    std::map<std::string, std::string> music = { { "TITLE", "Sound/Title Theme.wav" },
        { "LOSE", "Sound/lose.wav" },
        { "WIN", "Sound/win.wav" },
        { "INGAME", "Sound/background-music-3.wav" },
        { "PRESS_SFX", "Sound/btn-confirm.wav " },
        { "SWITCH_SFX", "Sound/btn-switch.wav " },
        { "FINAL_BOSS", "Sound/boss-fight.wav" },
        { "FINAL_CUT", "Sound/final-cut.wav" },
        { "BOSS_BLOW_UP", "Sound/BlowingSFX.wav" } };

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

    void updateIngameGUI();
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

    void saveGame(std::string fileName);
    void loadGame(std::string fileName);
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

    float getDeltaTime();

    void playMusic(std::string file);
    void playSound(std::string file);
    void stopMusic();
};
