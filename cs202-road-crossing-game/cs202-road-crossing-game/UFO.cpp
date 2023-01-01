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

UFO::UFO(int dir, ENEMY_BASE* base)
    : OBSTACLE::OBSTACLE(dir, base)
{
}

void UFO::render(sf::RenderTarget& target)
{
    target.draw(this->sprite);
}

bool UFO::update(float deltaTime)
{
    this->sprite.move(speed * dir, 0);
    return false;
}

bool UFO::isCollide(sf::FloatRect obj)
{
    return this->sprite.getGlobalBounds().intersects(obj);
}

bool UFO::canDelete(sf::Vector2u windowSize)
{
    return this->isOutOfBound(windowSize);
}

bool UFO::isOutOfBound(sf::Vector2u windowSize)
{
    return (this->dir == 1 && this->getPos().x > windowSize.x + DESTROY_ZONE) || (this->dir == -1 && this->getPos().x < 0 - DESTROY_ZONE);
}

bool UFO::isUFO()
{
    return true;
}