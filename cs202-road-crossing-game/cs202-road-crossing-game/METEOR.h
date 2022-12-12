#pragma once

enum btnFunc;
class METEOR : public OBSTACLE {
public:
	METEOR();
	METEOR(int dir, int pos, int height);
	void render(sf::RenderTarget &target);
	void update();
	const sf::Vector2f &getPos() const;
};
