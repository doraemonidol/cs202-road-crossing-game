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

OBSTACLE::OBSTACLE(int dir, ENEMY_BASE* base)
    : ENEMY_BASE(*base)
{
    this->dir = dir;
    if (this->texture != nullptr)
        this->sprite.setTexture(*this->texture);
    this->sprite.setPosition(this->pos);
}

int OBSTACLE::getDir()
{
    return dir;
}

int OBSTACLE::getRowID()
{
    return rowID;
}

const sf::Vector2f& OBSTACLE::getPos()
{
    return (this->sprite.getPosition());
}

float OBSTACLE::getSpeed()
{
    return speed;
}

void OBSTACLE::addSpeed(float speedAdd)
{
    speed += speedAdd;
}

void OBSTACLE::setSpeed(float speed)
{
    this->speed = speed;
}