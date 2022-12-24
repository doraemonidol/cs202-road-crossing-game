#include "ENEMY_BASE.h"
#include "OBSTACLE.h"
#include "UFO.h"
#include "LASER.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

//SMALL_MONSTER::SMALL_MONSTER(){
//	if(!this->texture.loadFromFile("Textures/obstacle-3.png")){
//		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
//	}
//	this->sprite.setTexture(this->texture);
//	this->sprite.scale(1.3f, 1.3f);
//	this->sprite.setPosition(-100, 100);
//	speed = 2.0;
//	dir = 0;
//	height = 100;
//	HP = 25;
//}

//SMALL_MONSTER::SMALL_MONSTER(int dir, int pos, int height, int rowID)
//{
//	if(!this->texture.loadFromFile("Textures/obstacle-3.png")){
//		std::cout << "ERROR::MOSNTER::INITTEXTURE::Could not load texture file.\n";
//	}
//	this->sprite.setTexture(this->texture);
//	this->sprite.scale(1.3f, 1.3f);
//        this->sprite.setPosition(pos, rowID);
//	speed = 2.0;
//	this->dir = dir;
//	this->rowID = rowID;
//	HP = 25;
//}

SMALL_MONSTER::SMALL_MONSTER(int dir, ENEMY_BASE* base)
    : MONSTER(dir, base)
{
}

void SMALL_MONSTER::render(sf::RenderTarget &target){
	target.draw(this->sprite);
}

void SMALL_MONSTER::update(){
	this->sprite.move(this->speed * dir, 0);
}