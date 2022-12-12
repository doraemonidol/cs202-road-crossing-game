#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

UFO::UFO(){
	if(!this->texture.loadFromFile("Textures/obstacle-4.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(-100, 100);
	speed = 3.0;
	dir = 0;
	HP = 50;
}

UFO::UFO(int dir, int pos, int height){
	if(!this->texture.loadFromFile("Textures/obstacle-4.png")){
		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
	}
	this->sprite.setTexture(this->texture);
	this->sprite.scale(1.3f, 1.3f);
	this->sprite.setPosition(pos, height);
	speed = 3.0;
	this->dir = dir;
	HP = 50;
}

void UFO::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void UFO::update(){
	this->sprite.move(speed * dir, 0);
}

const sf::Vector2f &UFO::getPos() const{
	return this->sprite.getPosition();
}