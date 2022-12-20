#pragma once
#include "main.h"

class TRAFFICLIGHT{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	int height;
	bool isRed;
public:
	TRAFFICLIGHT(int pos, int height);
	void render(sf::RenderTarget &target);
	void update();
	sf::Sprite getSprite();
};

