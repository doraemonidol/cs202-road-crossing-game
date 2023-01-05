
#include "main.h"

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

void UFO::saveGame(std::string fileName)
{
    std::ofstream file;
    file.open(fileName, std::ios::app);
    file << "\n" << UFOENEMY << " ";
    file.close();
    OBSTACLE::saveGame(fileName);
}
