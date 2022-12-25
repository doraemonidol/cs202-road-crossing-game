#include "LEVEL_MANAGER.h"

LEVEL_MANAGER::LEVEL_MANAGER()
{
    sf::Texture* texture;
    ENEMY_BASE* enemies[MAX_ENEMY_TYPE];
    std::vector<int> spawnLine;
    std::vector<int> maxEnemyonLine;
    
    /**
    LEVEL 0
    **/
    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/0/monster-1-4x.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::SMALLMONSTER::Could not load texture file.\n";
    }
    enemies[SMALLMONSTER] = new ENEMY_BASE(1.f, 100, texture, 25);

    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/0/monster-2-4x.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::BIGMONSTER::Could not load texture file.\n";
    }
    enemies[BIGMONSTER] = new ENEMY_BASE(1.f, 0, texture, 25);

    enemies[LASERENEMY] = new ENEMY_BASE(1.f, 0, nullptr, 25);

    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/0/ufo-4x.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::UFO::Could not load texture file.\n";
    }
    enemies[UFOENEMY] = new ENEMY_BASE(1.f, 0, texture, 25);

    spawnLine.clear();
    spawnLine.assign({ 450, 300, 150, 0, -150 });

    maxEnemyonLine.clear();
    maxEnemyonLine.assign({ 5, 5, 5, 5, 5 });

    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/0/background.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::BACKGROUND::Could not load texture file.\n";
    }
    level[0] = new LEVEL(enemies, spawnLine, texture, 5.f, maxEnemyonLine);

    /**
    LEVEL 1
    **/
    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/1/monster-1-4x.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::SMALLMONSTER::Could not load texture file.\n";
    }
    enemies[SMALLMONSTER] = new ENEMY_BASE(1.f, 25, texture, 25);

    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/1/monster-2-4x.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::BIGMONSTER::Could not load texture file.\n";
    }
    enemies[BIGMONSTER] = new ENEMY_BASE(1.f, 50, texture, 25);

    enemies[LASERENEMY] = new ENEMY_BASE(1.f, 15, nullptr, 25);

    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/1/ufo-4x.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::UFO::Could not load texture file.\n";
    }
    enemies[UFOENEMY] = new ENEMY_BASE(1.f, 0, texture, 25);

    spawnLine.clear();
    spawnLine.assign({ 450, 300, 150, 0, -150 });

    maxEnemyonLine.clear();
    maxEnemyonLine.assign({ 5, 5, 5, 5, 5 });

    texture = new sf::Texture();
    if (!texture->loadFromFile("Textures/level/1/background.png")) {
        std::cout << "ERROR::LEVEL_MANAGER::LEVEL0::BACKGROUND::Could not load texture file.\n";
    }
    level[1] = new LEVEL(enemies, spawnLine, texture, 3.f, maxEnemyonLine);
}

LEVEL_MANAGER::~LEVEL_MANAGER()
{
    for (int i = 0; i < MAX_LEVEL; i++)
        if (level[i])
            delete level[i];
}

LEVEL* LEVEL_MANAGER::getLevel(int lv)
{
    return level[lv];
}

LEVEL::LEVEL(ENEMY_BASE* enemies[MAX_ENEMY_TYPE], std::vector<int> spawnLine, 
    sf::Texture* bgTexture, float spawnTimer, std::vector<int> maxEnemyonLine)
{
    for (int i = 0; i < MAX_ENEMY_TYPE; i++)
        this->enemies[i] = new ENEMY_BASE(enemies[i]);

    for (int i = 0; i < spawnLine.size(); i++)
        this->spawnLine.push_back(spawnLine[i]);

    for (int i = 0; i < maxEnemyonLine.size(); i++)
        this->maxEnemyonLine.push_back(maxEnemyonLine[i]);

    backgroundTexture = bgTexture;
    this->spawnTimer = spawnTimer;
}

LEVEL::~LEVEL()
{
    for (int i = 0; i < MAX_ENEMY_TYPE; i++) {
        delete enemies[i]->getTexture();
        delete enemies[i];
    }
    delete backgroundTexture;
}

ENEMY_BASE* LEVEL::getEnemyBase(int id)
{
    return enemies[id];
}

std::vector<int> LEVEL::getSpawnLine()
{
    return spawnLine;
}

sf::Texture* LEVEL::getBackgroundTexture()
{
    return backgroundTexture;
}

void LEVEL::transferEnemyBase(ENEMY_BASE* newBase[])
{
    for (int i = 0; i < MAX_ENEMY_TYPE; i++)
        newBase[i] = this->enemies[i];
}

void LEVEL::transferSpawnLine(std::vector<int> &newSpawnLine)
{
    newSpawnLine.clear();
    for (int i = 0; i < this->spawnLine.size(); i++)
        newSpawnLine.push_back(spawnLine[i]);
}

void LEVEL::transferBackgroundTexture(sf::Texture*& newbgTexture)
{
    newbgTexture = backgroundTexture;
}

void LEVEL::transferSpawnTimer(float& newSpawnTimer)
{
    newSpawnTimer = this->spawnTimer;
}

void LEVEL::transferMaxEnemyOnLine(std::vector<int>& newMaxEnemyonLine)
{
    newMaxEnemyonLine.clear();
    for (int i = 0; i < this->maxEnemyonLine.size(); i++)
        newMaxEnemyonLine.push_back(this->maxEnemyonLine[i]);
}
