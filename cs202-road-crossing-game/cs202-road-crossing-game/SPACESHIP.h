#pragma once 
#include "ANIMATION.h"

class SPACESHIP {
private:
    sf::Sprite sprite, blowupSprite;
    std::map<std::string, sf::Texture> textures;
    
    // Animation
    //sf::RectangleShape body;
    ANIMATION anim, blowup;
    unsigned int row;
    float speed;
    bool faceRight;
    sf::Vector2u imgCnt = { 1, 3 };
    float switchTime = 5;

    int hp;
    int hpMax;

    //Private functions
    void initVariables();
    void initTexture();
    void initSprite();

public:
    SPACESHIP();
    ~SPACESHIP();

    //Accessor
    const sf::Vector2f& getPos() const;
    const sf::FloatRect getBounds() const;
    const int& getHp() const;
    const int& getHpMax() const;
    const sf::Sprite getSprite();

    //Modifiers
    void setPosition(const sf::Vector2f pos);
    void setPosition(const float x, const float y);
    void setHp(const int hp);
    void loseHp(const int value);

    //Functions
    void move(const float dirX, const float dirY);
    void updateCollision(int worldBGTexY);
    void updateInput(float deltaTime);
    void update(int worldBGTexY, float deltaTime);
    void render(sf::RenderTarget& target);
    void initAfterLoad();
    bool upDead(float deltaTime);
    void renderDead(sf::RenderTarget& target);
};