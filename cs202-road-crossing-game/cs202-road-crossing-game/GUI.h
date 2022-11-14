#pragma once
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

    sf::Text gameOverText;

    //PlayerGUI
    sf::Sprite playerHp[4];

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

    //Functions
    void updateHealth(int health);
    void updateLevel(int level);
    void update(int level);
    void renderGameOver();
    void render();
};
