
#include "main.h" 

// CONSTRUCTORS / DESTRUCTORS

GAME::GAME()
    : sceneManager()
{
    soundController = new SoundManager(music["TITLE"]);
    this->isPause = false;
    this->isDead = false;
    this->initWindow();
    this->initPlayer();
    this->initView();
    this->initTextures();
    this->initSystems();
    this->initGUI();
    this->initMenu();
    /*this->loadGame();*/
    this->sceneManager.attachView(&view);
}

GAME::GAME(const int a)
{
    this->isPause = false;
    this->isDead = false;

    this->initPlayer();

    this->initView();
    this->initWindow();
    this->initTextures();
    this->initSystems();
    this->initGUI();
    this->initMenu();
    /*this->loadGame();*/
}

GAME::~GAME()
{
    delete this->window;
    delete this->player;
    delete this->gui;
    delete this->soundController;
    // Delete textures
    for (auto& i : this->textures) {
        delete i.second;
    }
}

// OPERATORS

GAME& GAME::operator=(GAME other)
{
    std::swap(window, other.window);
    /*std::swap()*/
    return *this;
}

// PRIVATE FUNCTIONS

void GAME::initWindow()
{
    this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Crossing the Universe", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(144);
    this->window->setVerticalSyncEnabled(false);
}

void GAME::initView() {
    this->view = sf::View();
    view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void GAME::initTextures()
{
}

void GAME::initSystems()
{
    this->level = 0;
    this->scene = MENUSCENE;
}

void GAME::initEnemy() {
    this->enemyController.initNewLevel(levelManager.getLevel(level));
}

void GAME::initPlayer()
{
    this->player = new SPACESHIP();
    this->remainBullets = 0;
    this->bulletLoadTime = 0;

}

template <class T>void swap(T* a, T* b) {
    T* c = a;
    a = b;
    b = c;
}

void GAME::initGUI() {
    this->gui = new GUI(this->window, this->player);
}

void GAME::initMenu() {
    menu = MENU(200, 200);
    menu.init();
}

//Functions
void GAME::run()
{
    sf::Image icon;
    icon.loadFromFile("Textures/logo.png"); // File/Image/Pixel
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    float totalTime = 0, prevTime = 0, curTime = 0;
    while (this->window->isOpen()) {
        //std::cout << "Game Update \n";
        soundController->update();
        curTime = clock.getElapsedTime().asSeconds();
        //std::cout << curTime << "\n";
        totalTime = curTime - prevTime;
        deltaTime += totalTime;
        if (deltaTime > 1.0 / FPS) {
            deltaTime = std::min(0.25, (double)deltaTime);
            if (!this->isPause) {
                this->totalTime += deltaTime;
                //std::cout << "doing";
            }
            //std::cout << deltaTime << " " << 1.0 / FPS << "\n";
            this->updatePollEvents();
            if (this->player->getHp() > 0)
                this->update();
            //std::cout << "Start Rendering\n";
            this->render();
            deltaTime -= 1 / FPS;
            /*this->saveGame();*/
        }
        prevTime = curTime;
    }
}

// UPDATE FUNCTIONS

void GAME::updatePollEvents()
{
    sf::Event e;
    while (this->window->pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed)
            this->window->close();
        switch (scene) {
        case LOADGAMESCENE: {
            bool didHitReturn = gui->updateTextBox(e);
            if (didHitReturn) {
                std::string fileName = gui->getSaveLoadText();
                std::ifstream infile(fileName);
                if (!infile.good()) {
                    std::cout << "Can not find game file!!" << std::endl;
                    gui->setTextBoxWarning(true);
                } else {
                    playMusic(music["INGAME"]);
                    this->loadGame(fileName);
                    scene = INGAME;
                    update();
                    gui->initPauseMenu();
                    scene = PAUSEGAME;
                    gui->setTextBoxWarning(false);
                }
                gui->setTextBoxString("");
            }
            break;
        }
        case SAVEGAMESCENE: {
            bool didHitReturn = gui->updateTextBox(e);
            if (didHitReturn) {
                std::string fileName = gui->getSaveLoadText();
                std::ifstream infile(fileName);
                this->saveGame(fileName);
                //scene = INGAME;
                //update();
                scene = PAUSEGAME;
                gui->setTextBoxWarning(false);
                gui->setTextBoxString("");
            }
                break;
        }
        case MENUSCENE: {
            int option = menu.update(this->window, e, this);
            switch (option) {
            case NEWGAME:
                playMusic(music["INGAME"]);
                totalTime = 0;
                scene = INGAME;
                this->resetGame();
                break;
            case EXIT:
                exit(0);
                break;
            case LOADGAME: {
                // playMusic(music["INGAME"]);
                //totalTime = 0;
                gui->initSaveLoadGame(true);
                scene = LOADGAMESCENE;
                update();
                break;
            }  
            case TOGGLESOUND:
                soundController->switchMute();
                menu.ToggleSound();
                break;
            case TOGGLETHEME:
                break;
            }
            break;
        }
        case INGAME:
            if (e.type == sf::Event::KeyPressed) {
                switch (e.key.code) {
                case sf::Keyboard::Escape:
                    if (this->isPause == false) {
                        this->gui->initPauseMenu();
                        this->isPause = true;
                        scene = PAUSEGAME;
                    } else {
                        this->isPause = false;
                        scene = INGAME;
                    }
                    break;
                case sf::Keyboard::M:
                    scene = MENUSCENE;
                    playMusic(music["TITLE"]);
                    break;
                case sf::Keyboard::S:
                    if (this->isPause) {

                    }
                    break;
                case sf::Keyboard::Space:
                    if (!this->isPause) {
                        if (remainBullets > 0) {
                            std::cout << remainBullets << std::endl;
                            remainBullets -= 1;
                            this->playerShoot();
                        }
                    }
                    break;
                case sf::Keyboard::R:
                    /*this->resetGame();
                    scene = MENUSCENE;*/
                    break;
                default:
                    break;
                }
            } else {
                gui->updateIngameGUI(e, this);
            }
            break;
        case PAUSEGAME: {
            int option = this->gui->updatePauseMenu(e, this);
            if (option != -1 && option != SAVEGAME)
                this->gui->closePauseMenu();
            switch (option) {
            case BACKTOGAME:
                this->isPause = false;
                scene = INGAME;
                break;
            case BACKTOMENU:
                this->isPause = false;
                view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f));
                this->window->setView(view);
                playMusic(music["TITLE"]);
                scene = MENUSCENE;
                break;
            case RESTART:
                this->resetGame();
                this->isPause = false;
                scene = INGAME;
                break;
            case LEADERBOARD:
                break;
            case SAVEGAME:
                scene = SAVEGAMESCENE;
                break;
            }
            break;
        }
        case WINSCENE: {
            int option = this->gui->updateWinMenu(e, this);
            if (option != -1)
                this->gui->closeWin();
            switch (option) {
            case 0:
                scene = INGAME;
                this->resetGame();
                break;
            case 1:
                view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f));
                this->window->setView(view);
                playMusic(music["TITLE"]);
                scene = MENUSCENE;
                break;
            }
            break;
        }
        case LOSESCENE: {
            int option = this->gui->updateLoseMenu(e, this);
            if (option != -1)
                this->gui->closeLose();
            switch (option) {
            case 0:
                scene = INGAME;
                this->resetGame();
                break;
            case 1:
                view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f));
                this->window->setView(view);
                playMusic(music["TITLE"]);
                scene = MENUSCENE;
                break;
            }
            break;
        }
        case INSTRUCTIONSCENE:
            if (e.type == sf::Event::KeyPressed) {
                this->isPause = false;
                scene = INGAME;
            }
            break;
        }
    }
}

void GAME::updateInput()
{
}

void GAME::updateWorld()
{
    //remove 
}

void GAME::updateView() {
    //std::cout << "updating view\n";
    float y = player->getPos().y;
    if (y > SCREEN_HEIGHT / 2)
        y = SCREEN_HEIGHT / 2;
    int tmp = (SCREEN_HEIGHT - this->gui->getBGSize().y);
    if (y < SCREEN_HEIGHT / 2 + tmp)
        y = SCREEN_HEIGHT / 2.0f + tmp;

    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, y));
    this->window->setView(view);
}

void GAME::updateBullets()
{
    this->loadBullet();
    this->removeBullet();
    // Update and render bullet
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->update();
    }
}

void GAME::loadBullet() {
    if (remainBullets == MAX_BULLET) {
        return;
    }
    bulletLoadTime += deltaTime;
    //std::cout << bulletLoadTime << std::endl;
    if (bulletLoadTime >= BULLET_RELOAD_TIME) {
        remainBullets += 1;
        bulletLoadTime -= BULLET_RELOAD_TIME;
    }
}

void GAME::updateEnemies()
{
    this->enemyController.update(deltaTime, player->getPos(), bullets, this);
}

void GAME::update()
{
    switch (scene) {
    case INGAME:
        //std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
        // this->updateInput();
        //std::cout << "1 ";
        this->updateIngameGUI();
        this->enemyController.spawn(deltaTime);
        //std::cout << "2 ";
        this->updateEnemies();
        //std::cout << "3";
        this->updateBullets();
        //std::cout << "4 ";

        this->player->update(this->gui->getBGSize().y, deltaTime);
        //std::cout << "5 ";

        this->gui->update(this->level, this->remainBullets, totalTime);
        //std::cout << "6 ";

        this->updateWorld();
        //std::cout << "7 ";

        this->updateView();
        //std::cout << "8 ";
        this->checkCollision();
        //std::cout << "9 ";
        enemyController.destroyEnemy(this->window->getSize());
        break;
    case NEXTLEVEL: {
        bool opt = sceneManager.update(this->gui->getBGSize().y, deltaTime, scene);
        if (opt) {
            this->gui->resetGUI();
            if (level == MAX_LEVEL)
                scene = ENDGAME;
            else
                scene = WINSCENE;
        }
        break;
    }
    case ENDGAME:
        sceneManager.update(this->gui->getBGSize().y, deltaTime, scene);
        break;
    }
}

/**
  * RENDER FUNCTIONS
  */

void GAME::renderWorld()
{
    this->gui->renderBG();
}

void GAME::renderBullets()
{
    // Update and render bullet
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->render(*this->window);
    }
}

void GAME::renderEnemies()
{
    // Render monsters and obstacles
    enemyController.render(*this->window);
}

void GAME::render()
{
    this->window->clear();
    switch (scene) {
    case SAVEGAMESCENE: {
        this->renderWorld();

        // Render bullet, enemies
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);
        this->gui->render();
        this->gui->renderTextBox(*this->window);
        break;
    }
    case LOADGAMESCENE: {
        this->menu.drawTitle(this->window);
        this->gui->renderTextBox(*this->window);

        break;
    }
    case MENUSCENE:
        this->menu.draw(this->window);
        break;
    case INGAME:
        // Draw world
        this->renderWorld();
        // Render bullet, enemies, lights
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);
        this->gui->render();

        // Game over screen
        if (this->player->getHp() <= 0)
            this->gui->renderWin();
        break;
         
    case PAUSEGAME:
        this->renderWorld();

        // Render bullet, enemies
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);
        this->gui->render();

        this->gui->renderPauseMenu();
        break;

    case WINSCENE:
        this->gui->renderBG();
        this->gui->renderWin();
        break;

    case LOSESCENE:
        if (isDead) {
            isDead = !(this->player->upDead(deltaTime));
        }
        this->renderWorld();

        // Render bullet, enemies
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);
        this->player->renderDead(*this->window);
        this->gui->render();

        if (!isDead)
            this->gui->renderLose();
        break;

    case ENDGAME:
        //view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2));
        sceneManager.renderFinalScene(*this->window);
        break;
    case INSTRUCTIONSCENE:
        // Draw world
        this->renderWorld();
        // Render bullet, enemies, lights
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);
        this->gui->render();
        this->gui->renderInstruction(*this->window);
        break;
    default:
        this->gui->renderBG();
        this->sceneManager.render(*this->window, scene);
    }

    this->window->display();
}

// LOAD & SAVE GAME

void GAME::saveGame(std::string fileName) {
    std::ofstream file;
    file.open(fileName, std::ios::out);
    if (!file) {
        std::cout << "Unable to open save game!" << std::endl;
        return;
    }
    file << view.getCenter().y << " " << isDead << " " << level << " " << deltaTime << " " << totalTime << "\n";
    sf::Vector2f pos = this->player->getPos();
    file << pos.x << " " << pos.y << "\n";
    file << bulletLoadTime << " " << remainBullets << "\n";
    int size = bullets.size();
    file << size << "\n";
    file.close();
    for (int i = 0; i < size; i++) {
        bullets[i]->saveGame(fileName);
    }
    //sceneManager.saveGame(fileName);
    enemyController.saveGame(fileName);
    //levelManager.saveGame(fileName);
    //gui->saveGame(fileName);
}

void GAME::loadGame(std::string fileName) {
    std::cout << "Loading...\n";
    std::ifstream file;
    file.open(fileName, std::ios::in);
    if (!file) {
        std::cout << "Unable to open save game!" << std::endl;
        return;
    }
    if (file.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Game file is empty, let's play new game!!" << std::endl;
        return;
    }

    float y, x;
    int tmp1, tmp2, size;
    file >> y >> tmp1 >> level >> deltaTime >> totalTime >> x >> y;
    gui->setWorldBackground(levelManager.getLevel(level)->getBackgroundTexture());
    isDead = (tmp1 == 1);
    isPause = true;
    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, y));
    this->window->setView(view);

    player->setPosition(sf::Vector2f(x, y));

    file >> bulletLoadTime >> remainBullets;
    file >> size;
    bullets.resize(size);
    for (int i = 0; i < size; i++) {
        file >> tmp1 >> x >> y;
        //std::cout << "\nbullets" << tmp1 << " " << x << " " << y;
        bullets[i] = new BULLET(sf::Vector2f(x, y), tmp1 == 1);
    }
   /* std::cout << bulletLoadTime << " " << remainBullets << " "
              << "bullets done\n";*/
    // sceneManager.saveGame(fileName);
    enemyController.loadGame(file, levelManager.getLevel(level));
    //std::cout << "enemies done\n";
    file.close();
    std::cout << "Open save game successfuly!" << std::endl;
}

void GAME::updateIngameGUI()
{
    int option = gui->updateIngameGUIAnim(this);
    switch (option) {
    case 0:
        soundController->switchMute();
        menu.ToggleSound();
        break;
    case 1:
        std::cout << "Instructions Scene\n";
        this->isPause = true;
        scene = INSTRUCTIONSCENE;
        break;
    case 2:
        if (this->isPause == false) {
            this->gui->initPauseMenu();
            this->isPause = true;
            scene = PAUSEGAME;
        } else {
            this->isPause = false;
            scene = INGAME;
        }
        break;
    }
}

// Reset game

void GAME::resetGame()
{
    totalTime = 0;
    bullets.clear();
    if (level == MAX_LEVEL - 1)
        playMusic(music["FINAL_BOSS"]);
    else playMusic(music["INGAME"]);
    // std::cout << "1";
    //  scene = MENUSCENE;
    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f));
    // std::cout << "1";
    this->window->setView(view);
    // std::cout << "1";
    this->gui->resetGUI();
    // std::cout << "1";
    delete this->player;
    // std::cout << "1";
    this->initPlayer();
    // std::cout << "1";
    gui->setWorldBackground(levelManager.getLevel(level)->getBackgroundTexture());
    if (level != MAX_LEVEL - 1)
        enemyController.initNewLevel(levelManager.getLevel(level));
    else enemyController.initFinalLevel(levelManager.getLevel(level));
    // std::cout << "1";

    // this->gui->initPauseMenu();
}

// COLLISION

void GAME::checkCollision()
{
    // return;
    if (enemyController.isCollidewPlayer(this->player->getCollider1()) || enemyController.isCollidewPlayer(this->player->getCollider2())) {
        scene = LOSESCENE;
        isDead = true;
        playMusic(music["LOSE"]);
        this->gui->initLose();

        //std::cout << "Lost case!" << std::endl;
    }

    int minHeight = -1 * (this->gui->getBGSize().y - SCREEN_HEIGHT);
    if (this->player->getPos().y == minHeight) {
        this->scene = NEXTLEVEL;
        this->sceneManager.resetNextLevel();
        // std::cout
        level++;

        if (level == MAX_LEVEL) {
            playMusic(music["FINAL_CUT"]);
        } else {
            playMusic(music["WIN"]);
            // this->initPlayer();
            view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f));
            this->window->setView(view);
            this->gui->initWin();

            // std::cout << "Win case!" << std::endl;
        }
    }

    // damge monsteres and obstacles
    for (int i = 0; i < bullets.size(); i++) {
        // enemies' bullets
        if(!bullets[i]->PlayerBullet()) {
            // check whether it hit player
            if(bullets[i]->getSprite().getGlobalBounds().intersects(player->getCollider1())) {
                scene = LOSESCENE;
                isDead = true;
                playMusic(music["LOSE"]);
                this->gui->initLose();

                std::cout << "Lost case!" << std::endl;
            }
            // skip checking collide with enemies
            continue;
        }
        if (enemyController.isShoot(bullets[i]->getSprite().getGlobalBounds(), bullets[i]->getDamage())) {
            bullets.erase(bullets.begin() + i);
            // std::cout << bullets.size() << "< < < < < <\n >>>>>>";
            i--;
            if (i < 0)
                break;
        }
    }
   // std::cout << "Finish Collision\n";
}

void GAME::playerShoot()
{
        // std::cout << "Shooting\n";
        sf::Vector2f pos = this->player->getPos();
        this->bullets.push_back(new BULLET(pos, false));
        // std::cout << "Done shooting\n";
}

void GAME::removeBullet()
{
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->getMoveLength() == 0) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
            i--;
        }
    }
}

// SETTERS

void GAME::setSPACESHIP(SPACESHIP player) {
    swap(this->player, &player);
}

void GAME::setGUI(GUI gui) {
    swap(this->gui, &gui);
}

void GAME::setClocK(sf::Clock clock) {
    this->clock = clock;
}

void GAME::setDeltaTime(float deltaTime) {
    this->deltaTime = deltaTime;
}

void GAME::setLevel(unsigned level) {
    this->level = level;
}

void GAME::setScene(unsigned scene) {
    this->scene = scene;
}

void setTextures(std::map<std::string, sf::Texture*> other) {
}

void GAME::setWindow(sf::RenderWindow window) {
    swap(this->window, &window);
}

void GAME::setView(sf::View view) {
    this->view = view;
}

void GAME::setIsPause(bool isPause) {
    this->isPause = isPause;
}

// MUSIC and SFX

void GAME::playMusic(std::string file)
{
    soundController->playSound(file);
}

void GAME::playSound(std::string file)
{
    soundController->playEffect(file);
}

float GAME::getDeltaTime()
{
    return deltaTime;
}

void GAME::stopMusic()
{
    soundController->clearQueue();
}
