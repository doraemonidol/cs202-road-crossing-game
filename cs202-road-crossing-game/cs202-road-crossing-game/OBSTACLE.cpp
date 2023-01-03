
#include "main.h"

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

void OBSTACLE::saveGame(std::string fileName) {
    this->ENEMY_BASE::saveGame(fileName);
    std::ofstream file;
    file.open(fileName, std::ios::app);
    file.write((char*)&sprite.getPosition().x, sizeof(sprite.getPosition().x));
    file.write((char*)&sprite.getPosition().y, sizeof(sprite.getPosition().y));
    file.write((char*)&dir, sizeof(dir));
    file.close();
}