#include "main.h"
#include "ANIMATION.h"

ANIMATION::ANIMATION(sf::Texture* texture, sf::Vector2u imgCnt, float switchTime)
{
    this->imgCnt = imgCnt;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    curImg.x = 0;

    uvRect.width = texture->getSize().x / float(imgCnt.x);
    uvRect.height = texture->getSize().y / float(imgCnt.y);
}

ANIMATION::~ANIMATION()
{
}

void ANIMATION::Update(int row, float deltaTime, bool faceRight)
{
    curImg.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        curImg.x = (curImg.x + 1) % imgCnt.x;
    }

    uvRect.top = curImg.y * uvRect.height;
    if (faceRight) {
        uvRect.left = curImg.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    } else {
        uvRect.left = (curImg.x + 1) * uvRect.width;
        uvRect.width = -abs(uvRect.width);
    }
}
