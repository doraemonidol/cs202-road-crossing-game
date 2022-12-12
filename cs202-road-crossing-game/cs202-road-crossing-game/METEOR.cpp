#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

METEOR::METEOR() {
	if(!this->texture.loadFromFile("Textures/obstacle-1.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(-100, 100);
	dir = 0;
	HP = 75;
}

METEOR::METEOR(int dir, int pos, int height){
	if(!this->texture.loadFromFile("Textures/obstacle-1.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(pos, height);
	this->dir = dir;
	HP = 75;
}

void METEOR::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void METEOR::update() {
	this->sprite.move(3.0f * dir, 0);
}

const sf::Vector2f &METEOR::getPos() const{
	return this->sprite.getPosition();
}