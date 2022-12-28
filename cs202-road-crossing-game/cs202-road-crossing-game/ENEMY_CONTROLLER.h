#pragma once
#include "ENEMY_BASE.h"
#include "LEVEL_MANAGER.h"
#include "MONSTER.h"
#include "LASER.h"
#include "OBSTACLE.h"
#include "TRAFFICLIGHT.h"
#include "main.h"

class LASER;

class ENEMY_CONTROLLER {
private:
    ENEMY_BASE* base[MAX_ENEMY_TYPE];

    std::vector<MONSTER*> monsters;
    std::vector<OBSTACLE*> obstacles;
    std::vector<TRAFFICLIGHT*> lights;
    std::vector<bool> redLightOn;
    std::vector<bool> canSpawn;
    std::vector<int> spawnLine;
    std::vector<int> maxEnemyonLine;
    std::vector<LASER*> laserQueue;

    float spawnTimer;
    float curSpawnTimer;

public:
    ENEMY_CONTROLLER() {};
    ~ENEMY_CONTROLLER();

    void initNewLevel(LEVEL* newLevel);
    void initLight();

    MONSTER* isShoot(sf::FloatRect obj);
    bool isCollidewPlayer(sf::FloatRect obj);
    bool isLineEmpty(int rowID);

    void destroyEnemy(sf::Vector2u boundSize);
    void destroyMonsters(sf::Vector2u boundSize);
    void destroyObstacles(sf::Vector2u boundSize);

    void render(sf::RenderTarget& target);
    void renderEnemy(sf::RenderTarget& target);
    void renderLight(sf::RenderTarget& target);
    void update(float deltaTime);
    void updateEnemy(float deltaTime);
    void updateLight(float deltaTime);

    void spawn(float deltaTime);
    void initSpawn();
    void clearAll();
    void deallocate();
};
