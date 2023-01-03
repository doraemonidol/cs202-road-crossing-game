#pragma once

class OBSTACLE : public ENEMY_BASE{
protected:
	sf::Sprite sprite;
	int dir;
public:
    OBSTACLE(int dir, ENEMY_BASE* base);
    virtual ~OBSTACLE() {}

	virtual void render(sf::RenderTarget& target) = 0;
    virtual bool update(float deltaTime) = 0;
	
    virtual bool isCollide(sf::FloatRect obj) = 0;
    virtual bool canDelete(sf::Vector2u windowSize) = 0;
    virtual bool isOutOfBound(sf::Vector2u windowSize) = 0;

    int getDir();
    int getRowID();
    const sf::Vector2f& getPos();
    float getSpeed();
    void addSpeed(float speedAdd); // speed += speedAdd
    void setSpeed(float speed); // set speed to

    virtual bool isUFO() = 0;
    virtual void saveGame(std::string fileName);
};