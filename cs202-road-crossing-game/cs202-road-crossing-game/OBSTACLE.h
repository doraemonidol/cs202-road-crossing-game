#pragma once
#include "main.h"
#include <cstdlib>
#include <ctime>

class OBSTACLE{
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	float speed;
	int dir;
	int HP;
public:
	OBSTACLE(){};
	OBSTACLE(int dir, int pos, int height){};
	virtual void render(sf::RenderTarget& target) = 0;
    virtual void update(float deltaTime) = 0;
	virtual const sf::Vector2f& getPos() const = 0;
    virtual bool isCollide(sf::FloatRect obj) = 0;
    virtual bool canDelete() = 0;
	float getSpeed();
	void addSpeed(float speedAdd); //speed += speedAdd
	void setSpeed(float speed); //set speed to
	sf::Sprite getSprite();
	int getHP();
	void recievedDmg(int dmg);
	int getDir();
};