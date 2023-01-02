#pragma once

class MONSTER : public ENEMY_BASE{
protected:
    sf::Sprite sprite;
    int dir;

public:
	//MONSTER(){}
    MONSTER(int dir, ENEMY_BASE* base);
    virtual ~MONSTER() {}

	virtual void render(sf::RenderTarget& target) = 0;
	virtual void update() = 0;

    bool isCollide(sf::FloatRect obj);
    bool canDelete(sf::Vector2u windowSize);
    bool isOutOfBound(sf::Vector2u windowSize);
    bool isDead();

    int getDir();
    int getRowID();
    const sf::Vector2f& getPos();
    float getSpeed();
	void addSpeed(float speedAdd); //speed += speedAdd
	void setSpeed(float speed); //set speed to

	void recievedDmg(int dmg);
};
