#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

float OBSTACLE::getSpeed(){
	return speed;
}

void OBSTACLE::addSpeed(float speedAdd){
	speed += speedAdd;
}

void OBSTACLE::setSpeed(float speed){
	this->speed = speed;
}

sf::Sprite OBSTACLE::getSprite() {
	return sprite;
}

int OBSTACLE::getHP(){
	return HP;
}

void OBSTACLE::recievedDmg(int dmg){
	HP = std::max(0, HP - dmg);
}
int OBSTACLE::getDir() {
	return dir;
}