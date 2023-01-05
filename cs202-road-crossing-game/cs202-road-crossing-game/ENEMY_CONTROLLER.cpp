
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
        ///std::cout << "Line: " << l << "\n";
        if (!canSpawn[l] || maxEnemyonLine[l] <= 0)
            continue;
        for (int i = 0; i < MAX_ENEMY_TYPE; i++) {
            //std::cout << i << " \n";
            int isSpawn = rand() % 100;
            if (isSpawn > 75) {
                continue;
            }
            int type = rand() % 100 + 1,
                dir = (rand() % 2 == 1) ? 1 : -1,
                s = 0;
           // std::cout << type << "\n";
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
        //std::cout << "laser out\n";;
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
    file << finalBoss << "\n";
    int size = redLightOn.size();
    file << size << " ";
    for (int i = 0; i < size; i++) {
        file << redLightOn[i] << " ";
    }
    size = canSpawn.size();
    file << "\n"
         << size << " ";
    for (int i = 0; i < size; i++) {
       file << canSpawn[i] << " ";
    }
    size = monsters.size();
    file << "\n"
         << size << " ";
    size = obstacles.size();
    file << "\n"
         << size << " ";
    size = lights.size();
    file << "\n"
         << size << " ";
    size = laserQueue.size();
    file << "\n"
         << size << " ";
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
        if (laserQueue[i])
            laserQueue[i]->saveGame(fileName);
        else {
            file.open(fileName, std::ios::app);
            file << "\n-1";
            file.close();
        }
    }
}

void ENEMY_CONTROLLER::loadGame(std::ifstream& file, LEVEL* newLevel)
{
    file >> finalBoss;
    //std::cout << "final boss: " << finalBoss << "\n";
    int size, tmp, size2, size3, size1;
    file >> size;
    for (int i = 0; i < size; i++) {
        file >> tmp;
        redLightOn.push_back(tmp == 1);
    }

    this->clearAll();
    // std::cout << "2";

    newLevel->transferEnemyBase(base);
    //std::cout << "trasfer base done\n";
    // std::cout << "2";
    newLevel->transferSpawnLine(spawnLine);
    //std::cout << "trasfer spawn line done\n";
    // std::cout << "2";
    newLevel->transferSpawnTimer(spawnTimer);
    //std::cout << "transfer spawntimer done\n";
    // std::cout << "2";
    newLevel->transferMaxEnemyOnLine(maxEnemyonLine);
    //std::cout << "transfer done\n";

    file >> size;
    for (int i = 0; i < size; i++) {
        file >> tmp;
        canSpawn.push_back(tmp == 1);
    }
    file >> size >> size1 >> size2 >> size3;
    int type = 0, rowID = 0, dir = 0;
    float pos;

    for (int i = 0; i < size; i++) {
        file >> type >> pos >> dir >> rowID;
       // std::cout << type << " " << pos << " " << dir << " " << rowID << "--\n";
        ENEMY_BASE* newEnemy = new ENEMY_BASE(base[type]->getSpeed(), base[type]->getRate(),
            base[type]->getTexture(), base[type]->getHp(), rowID, sf::Vector2f(pos, spawnLine[rowID]));
        if (type == BIGMONSTER) {
            monsters.push_back(new BIG_MONSTER(dir, newEnemy));
        } else {
            monsters.push_back(new SMALL_MONSTER(dir, newEnemy));
        }
    }
    //std::cout << "enemies done\n";
    for (int i = 0; i < size1; i++) {
        file >> type >> pos >> dir >> rowID;
        ENEMY_BASE* newEnemy = new ENEMY_BASE(base[type]->getSpeed(), base[type]->getRate(),
            base[type]->getTexture(), base[type]->getHp(), rowID, sf::Vector2f(pos, spawnLine[rowID]));
       // std::cout << type << " " << pos << " " << dir << " " << rowID
               //   << " new Enemy done\n";
        if (type == UFOENEMY) {
           // std::cout << "new UFO done\n";
            obstacles.push_back(new UFO(dir, newEnemy));
        } else {
            float y, droneLeftPosX, droneRightPosX, laserLeftSizeX;
            int prevFrame;
            bool isStarting, toDelete;
            int curImgX[3], curImgY[3];
            float totalTime[3];
            file >> y >> droneLeftPosX >> droneRightPosX >> laserLeftSizeX >> prevFrame >> tmp;
            isStarting = (tmp == 1);
            file >> tmp;
            toDelete = (tmp == 1);
            file >> curImgX[0] >> curImgY[0] >> totalTime[0] >> curImgX[1] >> curImgY[1] >> totalTime[1] >> curImgX[2] >> curImgY[2] >> totalTime[2];  
            obstacles.push_back(new LASER(y, droneLeftPosX, droneRightPosX, laserLeftSizeX, prevFrame, isStarting, toDelete, newEnemy, curImgX, curImgY, totalTime));
           // std::cout << "new Laser done\n";
        }
    }
    //std::cout << "obstacles done\n";

    for (int i = 0; i < size2; i++) {
        float posX, posY, totalTime;
        bool isRed, isBeginning;
        int curImgX, curImgY;
        file >> posX >> posY >> tmp;
        isRed = (tmp == 1);
        file >> tmp;
        isBeginning = (tmp == 1);
        file >> curImgX >> curImgY >> totalTime;
        lights.push_back(new TRAFFICLIGHT(posX, posY, isRed, isBeginning, curImgX, curImgY, totalTime));
    }
   // std::cout << "lights done\n";
    laserQueue.resize(size3);
    for (int i = 0; i < size3; i++) {
        file >> type;
        if (type == -1) {
            laserQueue[i] = nullptr;
            continue;
        }
        file >> pos >> dir >> rowID;
       // std::cout << i << " " << type << "laser 1 done\n";
        ENEMY_BASE* newEnemy = new ENEMY_BASE(base[type]->getSpeed(), base[type]->getRate(),
            base[type]->getTexture(), base[type]->getHp(), rowID, sf::Vector2f(pos, spawnLine[rowID]));
                                   std::cout << "laser 2 done\n";
        float droneLeftPosX, droneRightPosX, laserLeftSizeX, y;
        int prevFrame;
        bool isStarting, toDelete;
        int curImgX[3], curImgY[3];
       // std::cout << "laser 3 done\n";
        float totalTime[3];
        file >> y >> droneLeftPosX >> droneRightPosX >> laserLeftSizeX >> prevFrame >> tmp;
        isStarting = (tmp == 1);
        file >> tmp;
        toDelete = (tmp == 1);
       // std::cout << "laser 4 done\n";
        file >> curImgX[0] >> curImgY[0] >> totalTime[0] >> curImgX[1] >> curImgY[1] >> totalTime[1] >> curImgX[2] >> curImgY[2] >> totalTime[2];
       // std::cout << "laser 5 done\n";
        laserQueue[i] = new LASER(y, droneLeftPosX, droneRightPosX, laserLeftSizeX, prevFrame, isStarting, toDelete, newEnemy, curImgX, curImgY, totalTime);
        //std::cout << "laser 6 done\n";
    }
    //std::cout << "laser q done\n";
    canSpawn.assign(canSpawn.size(), true);
}
