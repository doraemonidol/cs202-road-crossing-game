#pragma once

class UFO : public OBSTACLE {
public:
	UFO();
	UFO(int dir, int pos, int height);
	void render(sf::RenderTarget &target);
	void update();
	const sf::Vector2f &getPos() const;
};
