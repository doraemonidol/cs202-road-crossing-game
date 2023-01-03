
#include "main.h"

ENEMY_CONTROLLER::~ENEMY_CONTROLLER()
{
    this->deallocate();
}

void ENEMY_CONTROLLER::initFinalLevel(LEVEL* newLevel)
{
    initNewLevel(newLevel);
    boss.reset();
    gameDone = false;
    //std::cout << "finallll";
    finalBoss = true;
    bossDeath = false;
}

void ENEMY_CONTROLLER::initNewLevel(LEVEL* newLevel)
{
    //std::cout << "no not yet";
    finalBoss = false;
    gameDone = false;
    bossDeath = false;
    //std::cout << "2";
    this->clearAll();
    //std::cout << "2";

    newLevel->transferEnemyBase(base);
    //std::cout << "2";
    newLevel->transferSpawnLine(spawnLine);
    //std::cout << "2";
    newLevel->transferSpawnTimer(spawnTimer);
    //std::cout << "2";
    newLevel->transferMaxEnemyOnLine(maxEnemyonLine);
    //std::cout << "2";
    //std::cout << "Assign Spawn Line: " << spawnLine.size() << "\n";

    laserQueue.resize(spawnLine.size(), nullptr);
    //std::cout << "2";
    redLightOn.resize(spawnLine.size(), false);
    //std::cout << "2";
    canSpawn.resize(spawnLine.size(), true);
    //std::cout << "2";

    curSpawnTimer = spawnTimer;

    initLight();
    initSpawn();
    //std::cout << "2";
}

void ENEMY_CONTROLLER::initLight()
{
    for (int i = 0; i < spawnLine.size(); i++) {
        lights.push_back(new TRAFFICLIGHT(spawnLine[i] + 25));
    }
}

bool ENEMY_CONTROLLER::isShoot(sf::FloatRect obj, int dmg)
{
    if (finalBoss && boss.isShoot(obj)) {
        boss.receiveDmg(dmg);
        return true;
    }

    for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->isCollide(obj)) {
            monsters[i]->recievedDmg(dmg);
            return true;
        }
    }
    return false;
}

bool ENEMY_CONTROLLER::isCollidewPlayer(sf::FloatRect obj)
{
    if (gameDone)
        return false;

    if (finalBoss && boss.isCollide(obj))
        return true;

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
    if (!gameDone) {
        renderEnemy(target);
        renderLight(target);
        if (finalBoss)
            renderBoss(target);
    }
}

void ENEMY_CONTROLLER::renderBoss(sf::RenderTarget& target)
{
    //std::cout << "rendering boss\n";
    boss.render(target);
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

void ENEMY_CONTROLLER::update(float deltaTime, sf::Vector2f playerPos, std::vector<BULLET*>& bullets, GAME* game)
{
    if (!gameDone) {
        if (finalBoss) {
            gameDone = updateBoss(deltaTime, playerPos);
            if (boss.getHp() <= 0 && !bossDeath) {
                clearAll();
                bossDeath = true;
                game->stopMusic();
                game->playSound("Sound/BlowingSFX.wav");
                return;
            }
        }
        // std::cout << "Updating Enemy\n";
        updateEnemy(deltaTime, bullets);
        // std::cout << "Updating Light\n";
        updateLight(deltaTime);
    }
}

bool ENEMY_CONTROLLER::updateBoss(float deltaTime, sf::Vector2f playerPos)
{
    return boss.update(deltaTime, playerPos);
}

void ENEMY_CONTROLLER::updateEnemy(float deltaTime, std::vector<BULLET *>  &bullets)
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
        if (obstacles[i]->isUFO()) {
            int isShoot = rand() % 500;
            if(!isShoot){
                //std::cout << "shooting\n";
                sf::Vector2f pos = obstacles[i]->getPos();
                bullets.push_back(new BULLET(pos, true));
            }
        }
    }
}

void ENEMY_CONTROLLER::updateLight(float deltaTime)
{
    //std::cout << "Lights Size: " << lights.size() << "\n";
    // Update lights
    for (int i = 0; i < lights.size(); i++) {
        //std::cout << i << " ";
        lights[i]->updateAnim(deltaTime);
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
            int isSpawn = rand() % 100;
            if (isSpawn > 75) {
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
                 obstacles.push_back(new UFO(dir, newEnemy));
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
    for (int i = 0; i < laserQueue.size(); i++) {
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

void ENEMY_CONTROLLER::initSpawn()
{
    for (int l = 0; l < spawnLine.size(); l++) {
        if (!canSpawn[l] || maxEnemyonLine[l] <= 0)
            continue;
        // std::cout << "Line: " << l << "\n";
        for (int i = 0; i < MAX_ENEMY_TYPE; i++) {
            // std::cout << i << " \n";
            int isSpawn = rand() % 100;
            if (isSpawn > 75) {
                continue;
            }
            int type = rand() % 100 + 1,
                dir = (rand() % 2 == 1) ? 1 : -1,
                s = 0;

            if (type >= base[i]->getRate())
                continue;
            maxEnemyonLine[l]--;
            int pos = (dir == 1) ? (rand() % SCREEN_WIDTH) : (SCREEN_WIDTH + 160 + rand() % 100);
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
                 obstacles.push_back(new UFO(dir, newEnemy));
                break;
            case LASERENEMY:
                laserQueue[l] = new LASER(newEnemy);
                canSpawn[l] = false;
                break;
            }
        }
        // std::cout << "done spawning \n";
    }
    for (int i = 0; i < spawnLine.size(); i++) {
        // std::cout << i << ": ";
        if (!isLineEmpty(i) || laserQueue[i] == nullptr)
            continue;
        // std::cout << "laser out\n";
        obstacles.push_back(laserQueue[i]);
        laserQueue[i] = nullptr;
    }
}

void ENEMY_CONTROLLER::clearAll()
{
    //std::cout << "3";
    deallocate();
    //std::cout << "3";
    monsters.clear();
    //std::cout << "3";
    obstacles.clear();
   //std::cout << "3";
    lights.clear();
   //std::cout << "3";
    laserQueue.clear();
   // std::cout << "3";
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

void ENEMY_CONTROLLER::saveGame(std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::app);
    int size = redLightOn.size();
    file.write((char*)&size, sizeof(size));
    for (int i = 0; i < size; i++) {
        file.write((char*)&redLightOn[i], sizeof(bool));
    }
    size = canSpawn.size();
    file.write((char*)&size, sizeof(size));
    for (int i = 0; i < size; i++) {
        file.write((char*)&canSpawn[i], sizeof(bool));
    }
    size = spawnLine.size();
    file.write((char*)&spawnLine, sizeof(int));
    for (int i = 0; i < size; i++) {
        file.write((char*)&spawnLine[i], sizeof(bool));
    }
    size = maxEnemyonLine.size();
    file.write((char*)&spawnLine, sizeof(int));
    for (int i = 0; i < size; i++) {
        file.write((char*)&maxEnemyonLine[i], sizeof(bool));
    }
    file.close();
    for (int i = 0; i < monsters.size(); i++) {
        monsters[i]->saveGame(fileName);
    }
    for (int i = 0; i < obstacles.size(); i++) {
        obstacles[i]->saveGame(fileName);
    }
    for (int i = 0; i < lights.size(); i++) {
        lights[i]->saveGame(fileName);
    }
    for (int i = 0; i < laserQueue.size(); i++) {
        laserQueue[i]->saveGame(fileName);
    }
}