#pragma once

class SMALL_MONSTER : public MONSTER {
public:
	//SMALL_MONSTER();
    //SMALL_MONSTER(int dir, int pos, int height, int rowID, );
    SMALL_MONSTER(int dir, ENEMY_BASE* base);
    ~SMALL_MONSTER() {};
	void render(sf::RenderTarget &target);
    void update();
};
