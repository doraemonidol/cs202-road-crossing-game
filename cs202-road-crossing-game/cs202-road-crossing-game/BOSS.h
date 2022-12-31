#pragma once
#include "main.h"
#include "ANIMATION.h"
#include "BULLET.h"

#define BOSS_TEXTURE_IDLE "Textures/boss-idle.png"
#define BOSS_TEXTURE_SHOOT1 "Textures/boss-shoot-1.png"
#define BOSS_TEXTURE_SHOOT2 "Textures/boss-shoot-2.png"
#define BOSS_TEXTURE_DIE "Textures/boss-die.png"
#define BOSS_NORMAL_SPEED 0.8
#define BOSS_SHOOTING_SPEED 0.5

enum bossState {
    IDLE,
    SHOOT_4,
    SHOOTLASER,
    bossStateCnt
};

class BOSS {
    float speed, whiteDuration;
    sf::Texture texture[bossStateCnt], dieTexture;
    int hp;
    sf::Vector2f pos;
    sf::Vector2f des;

    sf::Vector2f shooter[4];
    std::vector<bool> shooted;
    std::vector<BULLET*> bullets;

    sf::Sprite sprite, dieSprite;
    sf::RectangleShape rec[4];
    sf::RectangleShape laserCollider;
    sf::RectangleShape bossCollider;
    sf::RectangleShape dieOverlay;
    ANIMATION anim[bossStateCnt], dieAnim;
    int curState, deadDir;
    bool isPlaying;

public:
    BOSS();
    ~BOSS();

    void initAnimation();
    void initSprite();
    void initVariables();

    void receiveDmg(int dmg);
    bool updead(float);
    void updateBullets();
    void updateShooterPos();
    void updateLaserPos();
    void updateBossCollider();

    bool update(float, sf::Vector2f);
    void renderDead(sf::RenderTarget& target);
    void renderBullets(sf::RenderTarget& target);
    void render(sf::RenderTarget &target);

    void move(sf::Vector2f);
    void shootRatata(sf::Vector2f);
    void removeBullet();
    void shootLaser(float);

    bool isCollide(sf::FloatRect obj);
    bool isShoot(sf::FloatRect obj);
    bool isDead();
    bool stopShowMonster();

    void reset();

    int getHp();
};
