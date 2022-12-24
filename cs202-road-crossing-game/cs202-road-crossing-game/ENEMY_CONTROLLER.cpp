#include "ENEMY_CONTROLLER.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "OBSTACLE.h"
#include "LASER.h"
#include "UFO.h"

ENEMY_CONTROLLER::~ENEMY_CONTROLLER()
{
    this->deallocate();
}

void ENEMY_CONTROLLER::initNewLevel(LEVEL* newLevel)
{

    std::cout << "2";
    this->clearAll();
    std::cout << "2";

    newLevel->transferEnemyBase(base);
    std::cout << "2";
    newLevel->transferSpawnLine(spawnLine);
    std::cout << "2";
    newLevel->transferSpawnTimer(spawnTimer);
    std::cout << "2";
    newLevel->transferMaxEnemyOnLine(maxEnemyonLine);
    std::cout << "2";
    //std::cout << "Assign Spawn Line: " << spawnLine.size() << "\n";

    laserQueue.resize(spawnLine.size(), nullptr);
    std::cout << "2";
    redLightOn.resize(spawnLine.size(), false);
    std::cout << "2";
    canSpawn.resize(spawnLine.size(), true);
    std::cout << "2";

    initLight();
    std::cout << "2";
}

void ENEMY_CONTROLLER::initLight()
{
    for (int i = 0; i < spawnLine.size(); i++) {
        lights.push_back(new TRAFFICLIGHT(25, spawnLine[i] + 75));
    }
}

MONSTER* ENEMY_CONTROLLER::isShoot(sf::FloatRect obj)
{
    for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->isCollide(obj)) {
            return monsters[i];
        }
    }
}

bool ENEMY_CONTROLLER::isCollidewPlayer(sf::FloatRect obj)
{
    for (int i = 0; i < monsters.size(); i++)
        if (monsters[i]->isCollide(obj)) {
            //system("pause");
            return true;
        }
    for (int i = 0; i < obstacles.size(); i++)
        if (obstacles[i]->isCollide(obj)) {
            //std::cout << "obstacles\n";
            //system("pause");
            return true;
        }
    return false;
}

bool ENEMY_CONTROLLER::isLineEmpty(int rowID)
{
    for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->getRowID() == rowID) {
            //std::cout << "mont#" << i << "\n";
            return false;
        }
    }
    for (int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i]->getRowID() == rowID)
            return false;
    }
    return true;
}

void ENEMY_CONTROLLER::destroyEnemy(sf::Vector2u boundSize) {
    destroyMonsters(boundSize);
    destroyObstacles(boundSize);
}

void ENEMY_CONTROLLER::destroyMonsters(sf::Vector2u boundSize)
{
    int i = 0;
    while (i < monsters.size()) {
        if (monsters[i]->canDelete(boundSize)) {
            maxEnemyonLine[monsters[i]->getRowID()]++;
            delete monsters[i];
            monsters.erase(monsters.begin() + i);
        } else
            i++;
    }
}

void ENEMY_CONTROLLER::destroyObstacles(sf::Vector2u boundSize)
{
    int i = 0;
    while (i < obstacles.size()) {
        if (obstacles[i]->canDelete(boundSize)) {
            maxEnemyonLine[obstacles[i]->getRowID()]++;
            delete obstacles[i];
            obstacles.erase(obstacles.begin() + i);
        } else
            i++;
    }
}

void ENEMY_CONTROLLER::render(sf::RenderTarget& target)
{
    renderEnemy(target);
    renderLight(target);
}

void ENEMY_CONTROLLER::renderEnemy(sf::RenderTarget& target)
{
    for (int i = 0; i < monsters.size(); i++) {
        monsters[i]->render(target);
    }
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->render(target);
    }
}

void ENEMY_CONTROLLER::renderLight(sf::RenderTarget& target)
{
    // Render lights
    for (int i = 0; i < lights.size(); i++) {
        lights[i]->render(target);
    }
}

void ENEMY_CONTROLLER::update(float deltaTime) {
    //std::cout << "Updating Enemy\n";
    updateEnemy(deltaTime);
    //std::cout << "Updating Light\n";
    updateLight(deltaTime);
}

void ENEMY_CONTROLLER::updateEnemy(float deltaTime)
{
    // Check red light. Theo row id
    for (int i = 0; i < monsters.size(); i++) {
        if (redLightOn[monsters[i]->getRowID()])
            continue;
        monsters[i]->update();
    }
    for (int i = 0; i < obstacles.size(); i++) {
        if (obstacles[i]->update(deltaTime)) {
            canSpawn[obstacles[i]->getRowID()] = true;
        }
    }
}

void ENEMY_CONTROLLER::updateLight(float deltaTime)
{
    //std::cout << "Lights Size: " << lights.size() << "\n";
    // Update lights
    for (int i = 0; i < lights.size(); i++) {
        //std::cout << i << " ";
        if (lights[i]->isRedLight()) {
            int isTurnGreen = rand() % 500;
            if (!isTurnGreen) {
                lights[i]->update();
                redLightOn[i] = false;
            }
        } else {
            int isTurnRed = rand() % 1500;
            if (!isTurnRed) {
                lights[i]->update();
                redLightOn[i] = true;
            }
        }
    }
}

void ENEMY_CONTROLLER::spawn(float deltaTime)
{
    curSpawnTimer += deltaTime;
    if (curSpawnTimer < spawnTimer)
        return;
    //std::cout << "Spawning " << spawnLine.size() << "\n ";
    for (int l = 0; l < spawnLine.size(); l++) {
        if (!canSpawn[l] || maxEnemyonLine[l] <= 0)
            continue;
        //std::cout << "Line: " << l << "\n";
        for (int i = 0; i < MAX_ENEMY_TYPE; i++) {
            //std::cout << i << " \n";
            int isSpawn = rand() % 2;
            if (isSpawn == 0) {
                continue;
            }
            int type = rand() % 100 + 1,
                dir = (rand() % 2 == 1) ? 1 : -1,
                s = 0;

            if (type >= base[i]->getRate())
                continue;
            maxEnemyonLine[l]--;
            int pos = (dir == 1) ? (-100 - rand() % 100) : (SCREEN_WIDTH + 160 + rand() % 100);
            ENEMY_BASE* newEnemy = new ENEMY_BASE(base[i]->getSpeed(), base[i]->getRate(),
                base[i]->getTexture(), base[i]->getHp(), l, sf::Vector2f(pos, spawnLine[l]));
            switch (i) {
            case BIGMONSTER:
                monsters.push_back(new BIG_MONSTER(dir, newEnemy));
                break;
            case SMALLMONSTER:
                monsters.push_back(new SMALL_MONSTER(dir, newEnemy));
                break;
            case UFOENEMY:
                // obstacles.push_back(new UFO(dir, newEnemy));
                break;
            case LASERENEMY:
                //std::cout << l << " in laser \n";
                //system("pause");
                laserQueue[l] = new LASER(newEnemy);
                //std::cout << "passed\n";
                canSpawn[l] = false;
                //std::cout << "passed\n";
                break;
            }
        }
        //std::cout << "done spawning \n";
    }
    for (int i = 0; i < spawnLine.size(); i++) {
        //std::cout << i << ": ";
        if (!isLineEmpty(i) || laserQueue[i] == nullptr)
            continue;
        //std::cout << "laser out\n";
        obstacles.push_back(laserQueue[i]);
        laserQueue[i] = nullptr;
    }
    curSpawnTimer -= spawnTimer;
    //std::cout << "Return Spawning\n";
}

void ENEMY_CONTROLLER::clearAll()
{
    std::cout << "3";
    deallocate();
    std::cout << "3";
    monsters.clear();
    std::cout << "3";
    obstacles.clear();
    std::cout << "3";
    lights.clear();
    std::cout << "3";
    laserQueue.clear();
    std::cout << "3";
}

void ENEMY_CONTROLLER::deallocate() {
    for (int i = 0; i < monsters.size(); i++)
        if (monsters[i])
            delete monsters[i];
    for (int i = 0; i < obstacles.size(); i++)
        if (obstacles[i])
            delete obstacles[i];
    for (int i = 0; i < lights.size(); i++)
        if (lights[i])
            delete lights[i];
    for (int i = 0; i < laserQueue.size(); i++)
        if (laserQueue[i])
            delete laserQueue[i];
}