#pragma once
#include "main.h"

class BULLET {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int speed;
	int damage;
	int moveLength;
	bool isPlayerBullet;
public:
	BULLET();
	BULLET(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void update();
	void render(sf::RenderTarget& target);
	int getDamage();
	sf::Sprite getSprite();
	int getMoveLength();
};