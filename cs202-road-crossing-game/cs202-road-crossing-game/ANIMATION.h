#pragma once
class ANIMATION {

public:
    ANIMATION();
    ANIMATION(sf::Texture* texture, sf::Vector2u imgCnt, float switchTime);
    ~ANIMATION();

    void Update(int row, float deltaTime, bool faceRight);
    void initAnim(sf::Texture* texture, sf::Vector2u imgCnt, float switchTime);
    sf::IntRect uvRect;

private:
    sf::Vector2u imgCnt;
    sf::Vector2u curImg;

    float totalTime;
    float switchTime;
};
