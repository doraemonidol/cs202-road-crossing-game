#pragma once

class BIG_MONSTER : public MONSTER {
public:
	BIG_MONSTER();
	BIG_MONSTER(int dir, int pos, int height);
	void render(sf::RenderTarget &target);
	void update();
	const sf::Vector2f &getPos() const;
};
