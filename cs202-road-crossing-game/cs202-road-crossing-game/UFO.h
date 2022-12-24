#pragma once

class UFO : public OBSTACLE {
public:
    UFO(int dir, ENEMY_BASE* base);
    ~UFO() {}

	void render(sf::RenderTarget& target);
    bool update(float deltaTime);

    bool isCollide(sf::FloatRect obj);
    bool canDelete(sf::Vector2u windowSize);
    bool isOutOfBound(sf::Vector2u windowSize);
};
