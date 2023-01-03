

#include "main.h"


ENEMY_BASE::ENEMY_BASE(float speed, int rate,
                       sf::Texture* texture, int hp, int rowID,
                       sf::Vector2f pos)
{
    this->speed = speed;
    this->rate = rate;
    this->texture = texture;
    this->hp = hp;
    this->rowID = rowID;
    this->pos = pos;
}

ENEMY_BASE::ENEMY_BASE(float speed, int rate,
    sf::Texture* texture, int hp)
{
    this->speed = speed;
    this->rate = rate;
    this->texture = texture;
    this->hp = hp;
}

ENEMY_BASE::ENEMY_BASE(ENEMY_BASE* base)
{
    speed = base->speed;
    rate = base->rate;
    texture = base->texture;
    hp = base->hp;
    rowID = base->rowID;
    pos = base->pos;
}

ENEMY_BASE::ENEMY_BASE(int rowID, int rate, sf::Vector2f pos)
{
    this->rowID = rowID;
    this->rate = rate;
    this->pos = pos;
}

ENEMY_BASE::~ENEMY_BASE()
{
   // std::cout << "delete base\n";
    //delete texture;
}

float ENEMY_BASE::getSpeed()
{
    return speed;
}

int ENEMY_BASE::getRate()
{
    return rate;
}

sf::Texture* ENEMY_BASE::getTexture()
{
    return texture;
}

int ENEMY_BASE::getHp()
{
    return hp;
}

int ENEMY_BASE::getRowID()
{
    return rowID;
}

sf::Vector2f ENEMY_BASE::getPos()
{
    return pos;
}

void ENEMY_BASE::saveGame(std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::app);
    file.write((char*)&speed, sizeof(speed));
    file.write((char*)&rate, sizeof(rate));
    file.write((char*)hp, sizeof(hp));
    file.write((char*)rowID, sizeof(rowID));
    file.write((char*)&pos, sizeof(pos));
    file.close();
}
