#include "main.h"

ANIMATION::ANIMATION()
{
}

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

bool ANIMATION::Update(int row, float deltaTime, bool faceRight)
{
    bool res = false;
    curImg.y = row;
    totalTime += deltaTime;
    //std::cout << totalTime << "\n";

    if (totalTime >= switchTime) {
        totalTime -= switchTime;
        if (curImg.x + 1 == imgCnt.x)
            res = true;
        curImg.x = (curImg.x + 1) % imgCnt.x;
    }

    uvRect.top = curImg.y * uvRect.height;
    if (faceRight) {
        uvRect.left = curImg.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    } else {
        uvRect.left = (curImg.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
    return res;
}

void ANIMATION::initAnim(sf::Texture* texture, sf::Vector2u imgCnt, float switchTime)
{
    this->imgCnt = imgCnt;
    this->switchTime = switchTime;
    totalTime = 0.0f;
    curImg.x = 0;

    uvRect.width = texture->getSize().x / float(imgCnt.x);
    uvRect.height = texture->getSize().y / float(imgCnt.y);
}

sf::Vector2u ANIMATION::getCurImgCnt()
{
    return curImg;
}

void ANIMATION::setSwitchTime(float switchTime)
{
    this->switchTime = switchTime;
}

void ANIMATION::setCurImg(sf::Vector2u newImg)
{
    curImg = newImg;
    uvRect.top = curImg.y * uvRect.height;
    uvRect.left = curImg.x * uvRect.width;
    uvRect.width = abs(uvRect.width);
}
