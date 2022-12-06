#pragma once
#include "main.h"
#include <cstdlib>
#include <ctime>
class MONSTER {
protected:
	sf::Sprite sprite;
	sf::Texture texture;
	int speedX = 100;
	int dir;
public:
	MONSTER() {

	}
	MONSTER(int dir, int pos, int height) {

	}
	virtual void render(sf::RenderTarget& target) = 0;
	virtual void update() = 0;
	virtual const sf::Vector2f& getPos() const = 0;
	int getDir() {
		return dir;
	}
	float getPosition() {
		return this->sprite.getPosition().x;
	}
};
