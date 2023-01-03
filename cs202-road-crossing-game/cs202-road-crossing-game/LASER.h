#pragma once

#define LASER_BEAM_TEXTURE "Textures/laser-beam-2x.png"
#define LEFT_DRONE_TEXTURE "Textures/drone-left-2x.png"
#define RIGHT_DRONE_TEXTURE "Textures/drone-right-2x.png"
#define NORMAL_SWITCH_TIME 0.1f
#define FAST_SWITCH_TIME 0.005f
#define FRAME_BEGIN_SWITCH 30
#define FRAME_END_SWITCH 42
#define IMG_CNT 48
#define LASER_IMG_CNT 24
#define LEFT_DRONE_POSITION -20
#define LEFT_DRONE_STARTING_POSITION -60
#define RIGHT_DRONE_POSITION (SCREEN_WIDTH - 40)
#define RIGHT_DRONE_STARTING_POSITION (RIGHT_DRONE_POSITION + 40)
#define FRAME_BEGIN_LASER 23
#define RIGHT_LASER_ORIGIN (RIGHT_DRONE_POSITION + 60)
#define MOVE_TIME 0.5f

enum btnFunc;

class LASER : public OBSTACLE {
    sf::Texture laserTexture, droneLeftTexture, droneRightTexture;
    sf::Sprite droneLeft, droneRight, laser;
    sf::RectangleShape laserLeft, laserRight;
    std::vector<float> inc = { 0, 2, 1, 1, 2, 7, 3, 8, 8, 9,
                               8, 8, 8, 8, 8, 8, 8, 8, 8, 16, 
                               16, 16, 16, 16, 16, 24, 24, 24, 24, 32};
    int prevFrame;
    ANIMATION laserAnim, droneLeftAnim, droneRightAnim;
    bool isStarting;
    bool toDelete;

public:
    LASER(ENEMY_BASE* base);
    ~LASER();
    void initTexture();

    bool update(float deltaTime);
    void render(sf::RenderTarget& target);

    bool isCollide(sf::FloatRect obj);
    bool canDelete(sf::Vector2u windowSize);
    bool isOutOfBound(sf::Vector2u windowSize);

    const sf::Vector2f& getPos() const;

    bool isUFO();
    void saveGame(std::string fileName);
};
