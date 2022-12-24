#include "ENEMY_BASE.h"
#include "OBSTACLE.h"
#include "UFO.h"
#include "LASER.h"
#include "ENEMY_BASE.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "SPACESHIP.h"
#include "GAME.h"

MONSTER::MONSTER(int dir, ENEMY_BASE* base)
    : ENEMY_BASE(*base)
{
    this->dir = dir;
    this->sprite.setTexture(*this->texture);
    this->sprite.setPosition(this->pos);
}

int MONSTER::getDir()
{
    return dir;
}

int MONSTER::getRowID()
{
    return rowID;
}

const sf::Vector2f& MONSTER::getPos()
{
    return (this->sprite.getPosition());
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

void MONSTER::recievedDmg(int dmg){
	hp = std::max(0, hp - dmg);
}

bool MONSTER::isCollide(sf::FloatRect obj)
{
        return sprite.getGlobalBounds().intersects(obj);
}

bool MONSTER::canDelete(sf::Vector2u windowSize)
{
        return this->isOutOfBound(windowSize) || this->isDead();
}

bool MONSTER::isOutOfBound(sf::Vector2u windowSize)
{
        return (this->dir == 1 && this->getPos().x > windowSize.x + DESTROY_ZONE) || (this->dir == -1 && this->getPos().x < 0 - DESTROY_ZONE);
}

bool MONSTER::isDead()
{
        return (this->hp == 0);
}
