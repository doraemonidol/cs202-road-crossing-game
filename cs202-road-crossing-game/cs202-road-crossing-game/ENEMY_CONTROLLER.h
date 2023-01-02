#pragma once

class ENEMY_CONTROLLER {
private:
    ENEMY_BASE* base[MAX_ENEMY_TYPE];

    BOSS boss;
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
    bool gameDone = false, finalBoss = false, bossDeath = false;

public:
    ENEMY_CONTROLLER() = default;
    ~ENEMY_CONTROLLER();

    void initFinalLevel(LEVEL* newLevel);
    void initNewLevel(LEVEL* newLevel);
    void initLight();

    bool isShoot(sf::FloatRect obj, int dmg);
    bool isCollidewPlayer(sf::FloatRect obj);
    bool isLineEmpty(int rowID);

    void destroyEnemy(sf::Vector2u boundSize);
    void destroyMonsters(sf::Vector2u boundSize);
    void destroyObstacles(sf::Vector2u boundSize);

    void render(sf::RenderTarget& target);
    void renderBoss(sf::RenderTarget& target);
    void renderEnemy(sf::RenderTarget& target);
    void renderLight(sf::RenderTarget& target);
    void update(float deltaTime, sf::Vector2f, std::vector<BULLET *> &bullets, GAME* game);
    bool updateBoss(float deltaTime, sf::Vector2f);
    void updateEnemy(float deltaTime, std::vector<BULLET *> &bullets);
    void updateLight(float deltaTime);

    void spawn(float deltaTime);
    void initSpawn();
    void clearAll();
    void deallocate();
};
