#pragma once
enum pauseMenuBtn;

#define TIME_POSITION sf::Vector2f(SCREEN_WIDTH / 2, 50)

class GUI {
private:
    sf::RenderWindow* window;
    // Player
    SPACESHIP* player;

    // Textures
    std::map<std::string, sf::Texture*> textures;
    sf::Texture worldBackgroundTex;
    sf::Sprite worldBackground;
    // std::vector<Bullet*> bullets;

    // GUI
    sf::Font font, font2;
    sf::Text levelText;
    sf::Text pauseText;
    sf::Text loseText;
    sf::Text winText;
    sf::Text totalTimeText;
    OPTIONS *pauseMenu, *loseMenu, *winMenu, *ingameGUI;

    // PlayerGUI
    sf::Texture bulletBarTexture;
    sf::Sprite bulletBar;
    ANIMATION bulletBarControl;
    sf::Sprite loseTitle, winTitle;
    float pauseMenuDisplacement, winLoseDisplacement, ingameGUIDisplacement;

    Textbox textBox;

    // Private functions
    void initTextures();
    void initGUI();

public:
    void initBG();
    GUI();
    GUI(sf::RenderWindow* window, SPACESHIP* player);
    ~GUI();

    void resetGUI();

    float getDisplacement();
    sf::Vector2u getBGSize();
    sf::Sprite getSprite();

    // Functions
    void updateBulletBar(int bullet);
    void updateLevel(int level);
    void updateTime(float totalTime);
    void update(int level, int bullet, float totalTime);

    void renderBG();
    void renderBulletBar();
    void render();

    // Game pause
    void renderGamePause();
    void updateGamePause();

    void initPauseMenu();
    int updatePauseMenu(sf::Event e, GAME* gm);
    void renderPauseMenu();
    void closePauseMenu();

    // Lose menu
    void initLose();
    int updateLoseMenu(sf::Event e, GAME* gm);
    void renderLose();
    void closeLose();

    // Win menu
    void initWin();
    int updateWinMenu(sf::Event e, GAME* gm);
    void renderWin();
    void closeWin();

    // Ingame GUI
    int updateIngameGUI(sf::Event e, GAME* gm);
    int updateIngameGUIAnim(GAME* gm);
    void renderIngameGUI();

    // SaveLoad Game
    void initSaveLoadGame(bool saveGame);
    std::string getSaveLoadText();
    bool updateTextBox(sf::Event event);
    void renderTextBox(sf::RenderTarget& target);
    void setTextBoxWarning(bool state);
    void setTextBoxString(std::string s);

    void setWorldBackground(sf::Texture* bg);

    void saveGame(std::string fileName);
};
