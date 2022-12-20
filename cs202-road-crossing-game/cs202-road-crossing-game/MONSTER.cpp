#include "OBSTACLE.h"
#include "UFO.h"
#include "LASER.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

int MONSTER::getDir(){
	return dir;
}

int MONSTER::getHeight(){
	return height;
}

float MONSTER::getPosition(){
	return this->sprite.getPosition().x;
}

float MONSTER::getSpeed(){
	return speed;
}

void MONSTER::addSpeed(float speedAdd){
	speed += speedAdd;
}

void MONSTER::setSpeed(float speed){
	this->speed = speed;
}

sf::Sprite MONSTER::getSprite(){
	return sprite;
}

int MONSTER::getHP(){
	return HP;
}

void MONSTER::recievedDmg(int dmg){
	HP = std::max(0, HP - dmg);
}