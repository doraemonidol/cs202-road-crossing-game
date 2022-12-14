#include "OBSTACLE.h"
#include "UFO.h"
#include "LASER.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

BIG_MONSTER::BIG_MONSTER(){
	if(!this->texture.loadFromFile("Textures/obstacle-2.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(-100, 100);
	speed = 1.0;
	dir = 0;
	HP = 100;
}

BIG_MONSTER::BIG_MONSTER(int dir, int pos, int height){
	if(!this->texture.loadFromFile("Textures/obstacle-2.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(pos, height);
	speed = 1.0;
	this->dir = dir;
	HP = 100;
}

void BIG_MONSTER::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void BIG_MONSTER::update(){
	this->sprite.move(speed * dir, 0);
}

const sf::Vector2f &BIG_MONSTER::getPos() const{
	return this->sprite.getPosition();
}