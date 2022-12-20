#include "OBSTACLE.h"
#include "UFO.h"
#include "LASER.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

SMALL_MONSTER::SMALL_MONSTER(){
	if(!this->texture.loadFromFile("Textures/obstacle-3.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(-100, 100);
	speed = 2.0;
	dir = 0;
	height = 100;
	HP = 25;
}

SMALL_MONSTER::SMALL_MONSTER(int dir, int pos, int height){
	if(!this->texture.loadFromFile("Textures/obstacle-3.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(pos, height);
	speed = 2.0;
	this->dir = dir;
	this->height = height;
	HP = 25;
}

void SMALL_MONSTER::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void SMALL_MONSTER::update(){
	this->sprite.move(speed * dir, 0);
}

const sf::Vector2f &SMALL_MONSTER::getPos() const{
	return this->sprite.getPosition();
}