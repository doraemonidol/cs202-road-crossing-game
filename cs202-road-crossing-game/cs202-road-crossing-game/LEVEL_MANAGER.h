#pragma once

enum monsterType;

class LEVEL {
    // Enemy Info
    ENEMY_BASE* enemies[MAX_ENEMY_TYPE];
    float spawnTimer;

    // Map
    std::vector<int> spawnLine;
    sf::Texture* backgroundTexture;
    std::vector<int> maxEnemyonLine;

public:
    LEVEL(ENEMY_BASE* enemies[MAX_ENEMY_TYPE], std::vector<int> spawnLine, sf::Texture* bgTexture,
        float spawnTimer, std::vector<int> maxEnemyonLine);
    ~LEVEL();
    
    ENEMY_BASE* getEnemyBase(int id);
    std::vector<int> getSpawnLine();
    sf::Texture* getBackgroundTexture();
    void transferEnemyBase(ENEMY_BASE* newBase[]);
    void transferSpawnLine(std::vector<int> &newSpawnLine);
    void transferBackgroundTexture(sf::Texture*& newbgTexture);
    void transferSpawnTimer(float& newSpawnTimer);
    void transferMaxEnemyOnLine(std::vector<int> &newMaxEnemyonLine);
};

class LEVEL_MANAGER {
    LEVEL* level[MAX_LEVEL];

public:
    LEVEL_MANAGER();
    ~LEVEL_MANAGER();
    LEVEL* getLevel(int lv);
};
