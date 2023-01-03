#pragma once

class ENEMY_BASE {
protected:
    float speed;
    int rate;
    sf::Texture* texture;
    int hp;
    int rowID;
    sf::Vector2f pos;

public:
    ENEMY_BASE() { }
    ENEMY_BASE( float speed,
        int rate,
        sf::Texture* texture,
        int hp,
        int rowID,
        sf::Vector2f pos);
    ENEMY_BASE(float speed,
        int rate,
        sf::Texture* texture,
        int hp);
    ENEMY_BASE(ENEMY_BASE* base);
    ENEMY_BASE(int rowID, int rate, sf::Vector2f pos);
    ~ENEMY_BASE();
    
    float getSpeed();
    int getRate();
    sf::Texture* getTexture();
    int getHp();
    int getRowID();
    sf::Vector2f getPos();
    virtual void saveGame(std::string fileName);
};
