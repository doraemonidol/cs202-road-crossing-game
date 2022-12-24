#include "ENEMY_BASE.h"
#include "main.h"
#include "OBSTACLE.h"
#include "GAME.h"
#include "LASER.h"

LASER::LASER(ENEMY_BASE* base)
    : OBSTACLE(0, base)
{
    this->initTexture();
    isStarting = true;
    toDelete = false;
}

LASER::~LASER()
{
}

void LASER::initTexture()
{
    //std::cout << "initializing texture for laser\n";
    if (!this->laserTexture.loadFromFile(LASER_BEAM_TEXTURE)) {
        std::cout << "ERROR::LASER::INITTEXTURE::Could not load texture file.\n";
    }
    //std::cout << "passed\n";
    laserAnim.initAnim(&this->laserTexture, sf::Vector2u { LASER_IMG_CNT, 1 }, NORMAL_SWITCH_TIME);
   // std::cout << "passed\n";
    this->laser.setTexture(this->laserTexture);
    this->laser.setOrigin(this->laser.getGlobalBounds().width / (2 * LASER_IMG_CNT), 0);
    this->laser.setPosition(SCREEN_WIDTH / 2, this->pos.y);

    //std::cout << "initializing texture for laser\n";
    if (!this->droneLeftTexture.loadFromFile(LEFT_DRONE_TEXTURE)) {
        std::cout << "ERROR::LASER::INITTEXTURE::Could not load texture file.\n";
    }
    droneLeftAnim.initAnim(&this->droneLeftTexture, sf::Vector2u { IMG_CNT, 1 }, NORMAL_SWITCH_TIME);
   // std::cout << "passed\n";
    this->droneLeft.setTexture(this->droneLeftTexture);
    this->droneLeft.setPosition(LEFT_DRONE_STARTING_POSITION, this->pos.y);

    //std::cout << "initializing texture for laser\n";
    if (!this->droneRightTexture.loadFromFile(RIGHT_DRONE_TEXTURE)) {
        std::cout << "ERROR::LASER::INITTEXTURE::Could not load texture file.\n";
    }
    droneRightAnim.initAnim(&this->droneRightTexture, sf::Vector2u { IMG_CNT, 1 }, NORMAL_SWITCH_TIME);
    //std::cout << "passed\n";
    this->droneRight.setTexture(this->droneRightTexture);
    this->droneRight.setPosition(RIGHT_DRONE_STARTING_POSITION, this->pos.y);

    laserLeft.setSize(sf::Vector2f(0, this->laser.getGlobalBounds().height));
    laserLeft.setFillColor(sf::Color::Transparent);
    //laserLeft.setOutlineColor(sf::Color::White);
    //laserLeft.setOutlineThickness(2);
    laserLeft.setOrigin(0.f, -5.f);
    laserLeft.setPosition(LEFT_DRONE_POSITION, this->pos.y);

    laserRight.setSize(laserLeft.getSize());
    laserRight.setFillColor(sf::Color::Transparent);
    //laserRight.setOutlineColor(sf::Color::Blue);
    //laserRight.setOutlineThickness(2);
    laserRight.setOrigin(laserRight.getSize().x, -5.f);
    laserRight.setPosition(RIGHT_LASER_ORIGIN, this->pos.y);

    this->droneRight.setTextureRect(droneRightAnim.uvRect);
    this->droneLeft.setTextureRect(droneLeftAnim.uvRect);
    //std::cout << "laser texture done\n";
}

bool LASER::update(float deltaTime)
{
    // START FRAMES

    if (isStarting) {
        this->droneLeft.move((float)speed, 0);
        this->droneRight.move((float)-speed, 0);/*
        std::cout << this->droneLeft.getPosition().x << " " << speed
                  << "\n";*/
        if (this->droneLeft.getPosition().x >= LEFT_DRONE_POSITION) {
            isStarting = false;
        }
        return false;
    }

    // END FRAMES

    if (prevFrame == IMG_CNT - 1) {
        this->droneLeft.move((float)-speed, 0);
        this->droneRight.move((float)speed, 0);
        if (this->droneLeft.getPosition().x <= LEFT_DRONE_STARTING_POSITION) {
            toDelete = true;
            //std::cout << "laser done";
            return true;
        }

        laserLeft.setSize(sf::Vector2f(0.f, 0.f));
        laserRight.setSize(sf::Vector2f(0.f, 0.f));
        laserLeft.setPosition(sf::Vector2f(-100, this->pos.y));
        laserRight.setPosition(sf::Vector2f(SCREEN_WIDTH + 100, this->pos.y));
        return false;
    }
    //std::cout << deltaTime << "\n";
    this->droneLeftAnim.Update(0, deltaTime, true);
    this->droneLeft.setTextureRect(droneLeftAnim.uvRect);
    this->droneRightAnim.Update(0, deltaTime, true);
    this->droneRight.setTextureRect(droneRightAnim.uvRect);

    int curFrame = this->droneLeftAnim.getCurImgCnt().x;
    /*std::cout << "Updating: " << curFrame << " " << prevFrame
              << "\n";*/

    if (curFrame == 0) {
        laserLeft.setSize(sf::Vector2f(droneLeft.getGlobalBounds().width, droneLeft.getGlobalBounds().height - 10));
        laserRight.setSize(sf::Vector2f(droneRight.getGlobalBounds().width, droneRight.getGlobalBounds().height - 10));
        laserRight.setOrigin(laserRight.getSize().x, -5.f);
        laserRight.setPosition(RIGHT_LASER_ORIGIN, this->pos.y);
    }

    if (curFrame == FRAME_BEGIN_LASER) {
        this->laserAnim.setCurImg(sf::Vector2u(0, 0));
    }

    if (curFrame >= FRAME_BEGIN_LASER) {
        //std::cout << "Laser\n";
        this->laserAnim.Update(0, deltaTime, true);
        this->laser.setTextureRect(laserAnim.uvRect);
    }

    if (curFrame != prevFrame) {
        if (curFrame == FRAME_BEGIN_SWITCH) {
            //system("pause");
            this->laserAnim.setSwitchTime(FAST_SWITCH_TIME);
            this->droneLeftAnim.setSwitchTime(FAST_SWITCH_TIME);
            this->droneRightAnim.setSwitchTime(FAST_SWITCH_TIME);
        }

        if (curFrame >= FRAME_BEGIN_LASER) {
            laserLeft.setSize(sf::Vector2f(this->laserLeft.getSize().x + inc[curFrame - FRAME_BEGIN_LASER] * 2, droneLeft.getGlobalBounds().height - 10));
            laserRight.setSize(laserLeft.getSize());
            laserRight.setOrigin(laserRight.getSize().x, -5.f);
            laserRight.setPosition(RIGHT_LASER_ORIGIN, this->pos.y);
        }

        if (curFrame == FRAME_END_SWITCH || curFrame == 0) {
            //system("pause");
            this->laserAnim.setSwitchTime(NORMAL_SWITCH_TIME);
            this->droneLeftAnim.setSwitchTime(NORMAL_SWITCH_TIME);
            this->droneRightAnim.setSwitchTime(NORMAL_SWITCH_TIME);
        }

        prevFrame = curFrame;
    }

    if (curFrame == 0) {
        //std::cout << NORMAL_SWITCH_TIME << "\n";
        this->laserAnim.setSwitchTime(NORMAL_SWITCH_TIME);
        this->droneLeftAnim.setSwitchTime(NORMAL_SWITCH_TIME);
        this->droneRightAnim.setSwitchTime(NORMAL_SWITCH_TIME);
    }
    return false;
}

void LASER::render(sf::RenderTarget& target)
{
    target.draw(this->laserLeft);
    target.draw(this->laserRight);
    if (isStarting || prevFrame == IMG_CNT - 1) {
        target.draw(this->droneLeft);
        target.draw(this->droneRight);
        return;
    }
    int curFrame = this->droneLeftAnim.getCurImgCnt().x;
    // std::cout << curFrame << std::endl;
    target.draw(this->droneLeft);
    target.draw(this->droneRight);
    if (curFrame >= FRAME_BEGIN_LASER && curFrame < IMG_CNT - 1) {
        target.draw(this->laser);
    }
}

bool LASER::isCollide(sf::FloatRect obj)
{
    if (droneLeft.getGlobalBounds().intersects(obj)) {
        // std::cout << "droneleft\n";
        return true;
    }
    if (droneRight.getGlobalBounds().intersects(obj)) {
        //  std::cout << "drone Right\n";
        return true;
    }
    if (laserLeft.getGlobalBounds().intersects(obj)) {
        // std::cout << "laser Left\n";
        return true;
    }
    if (laserRight.getGlobalBounds().intersects(obj)) {
        // std::cout << "laser Right\n";
        return true;
    }
    return false;
}

bool LASER::canDelete(sf::Vector2u windowSize)
{
    return toDelete;
}

bool LASER::isOutOfBound(sf::Vector2u windowSize)
{
    return false;
}

const sf::Vector2f& LASER::getPos() const
{
    return this->sprite.getPosition();
}