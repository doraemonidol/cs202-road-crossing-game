#include "main.h"
#include "ENEMY_CONTROLLER.h"
#include "GUI.h"
#include "GAME.h"       

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
    float totalTime = 0, prevTime = 0, curTime = 0;
    while (this->window->isOpen()) {
        //std::cout << "Game Update \n";
        soundController->update();
        curTime = clock.getElapsedTime().asSeconds();
        //std::cout << curTime << "\n";
        totalTime = curTime - prevTime;
        deltaTime += totalTime;
        if (deltaTime > 1.0 / FPS) {
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
        case MENUSCENE: {
            int option = menu.update(this->window, e, this);
            switch (option) {
            case NEWGAME:
                playMusic(music["INGAME"]);
                scene = INGAME;
                this->resetGame();
                break;
            case EXIT:
                exit(0);
                break;
            case LOADGAME:
                playMusic(music["INGAME"]);
                loadGame();
                scene = INGAME;
                break;
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
                        this->playerShoot();
                    }
                    break;
                case sf::Keyboard::R:
                    /*this->resetGame();
                    scene = MENUSCENE;*/
                    break;
                default:
                    break;
                }
            }
            break;
        case PAUSEGAME: {
            int option = this->gui->updatePauseMenu(e, this);
            if (option != -1)
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
                saveGame();
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
    this->removeBullet();
    // Update and render bullet
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i]->update();
    }
}

void GAME::updateEnemies()
{
    this->enemyController.update(deltaTime);
}

void GAME::update()
{
    switch (scene) {
    case INGAME:
        //std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
        // this->updateInput();
        //std::cout << "1 ";
        this->enemyController.spawn(deltaTime);
        //std::cout << "2 ";
        this->updateEnemies();
        //std::cout << "3";
        this->updateBullets();
        //std::cout << "4 ";

        this->player->update(this->gui->getBGSize().y, deltaTime);
        //std::cout << "5 ";

        this->gui->update(this->level);
        //std::cout << "6 ";

        this->updateWorld();
        //std::cout << "7 ";

        this->updateView();
        //std::cout << "8 ";
        this->checkCollision();
        //std::cout << "9 ";
        enemyController.destroyEnemy(this->window->getSize());
        break;
    case NEXTLEVEL:
        bool opt = sceneManager.update(this->gui->getBGSize().y, deltaTime, scene);
        if (opt) {
            this->gui->resetGUI();
            scene = WINSCENE;
        }
    }
}

// RENDER FUNCTIONS

void GAME::renderWorld()
{
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
    case MENUSCENE:
        this->menu.draw(this->window);
        break;
    case INGAME:
        // Draw world
        this->renderWorld();
        this->gui->render();

        // Render bullet, enemies, lights
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);

        // Game over screen
        if (this->player->getHp() <= 0)
            this->gui->renderWin();
        break;
         
    case PAUSEGAME:
        this->renderWorld();
        this->gui->render();

        // Render bullet, enemies
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);

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
        this->gui->render();

        // Render bullet, enemies
        this->renderBullets();
        this->renderEnemies();

        // Draw all the stuffs
        this->player->render(*this->window);
        this->player->renderDead(*this->window);

        if (!isDead)
            this->gui->renderLose();
        break;
    default:
        this->gui->renderBG();
        this->sceneManager.render(*this->window, scene);
    }

    this->window->display();
}

// LOAD & SAVE GAME

void GAME::saveGame() {
    std::ofstream file;
    file.open("Game.txt", std::ios::out);
    if (!file) {
        std::cout << "Unable to open save game!" << std::endl;
        return;
    }
    /*file.write((char*)window, sizeof(GAME));*/
    file.write((char*)&view, sizeof(sf::View));
    file.write((char*)&isPause, sizeof(bool));
    file.write((char*)&level, sizeof(unsigned));
    file.write((char*)&scene, sizeof(scene));
    file.write((char*)&clock, sizeof(sf::Clock));
    sf::Vector2f pos = this->player->getPos();
    file.write((char*)&pos, sizeof(sf::Vector2f));
    /*file.write((char*)gui, sizeof(GUI));*/
    file.close();
}

void GAME::loadGame() {
    std::ifstream file2;
    file2.open("Game.txt", std::ios::in);
    if (!file2) {
        std::cout << "Unable to open save game!" << std::endl;
        return;
    }
    std::cout << "Open save game successfuly!" << std::endl;
    if (file2.peek() == std::ifstream::traits_type::eof()) {
        std::cout << "Game file is empty, let's play new game!!" << std::endl;
        return;
    }
    file2.read((char*)&this->view, sizeof(sf::View));
    file2.read((char*)&this->isPause, sizeof(bool));
    file2.read((char*)&this->level, sizeof(unsigned));
    file2.read((char*)&this->scene, sizeof(unsigned));
    file2.read((char*)&this->clock, sizeof(sf::Clock));
    sf::Vector2f pos;
    file2.read((char*)&pos, sizeof(sf::Vector2f));
    this->player->setPosition(pos);
    file2.close();
}

// Reset game

void GAME::resetGame()
{
    playMusic(music["INGAME"]);
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
    enemyController.initNewLevel(levelManager.getLevel(level));
    // std::cout << "1";

    // this->gui->initPauseMenu();
}

// COLLISION

void GAME::checkCollision()
{
    // return;
    if (enemyController.isCollidewPlayer(this->player->getSprite().getGlobalBounds())) {
        scene = LOSESCENE;
        isDead = true;
        playMusic(music["LOSE"]);
        this->gui->initLose();

        std::cout << "Lost case!" << std::endl;
    }

    int minHeight = -1 * (this->gui->getBGSize().y - SCREEN_HEIGHT);
    if (this->player->getPos().y == minHeight) {
        this->scene = NEXTLEVEL;
        // std::cout
        level++;
        this->sceneManager.resetNextLevel();
        playMusic(music["WIN"]);
        // this->initPlayer();
        view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f));
        this->window->setView(view);
        this->gui->initWin();

        std::cout << "Win case!" << std::endl;
    }

    // damge monsteres and obstacles
    for (int i = 0; i < bullets.size(); i++) {
       // std::cout << i << "\n";
        MONSTER* tmp = enemyController.isShoot(bullets[i]->getSprite().getGlobalBounds());

        //std::cout << "passed check\n";
        if (tmp != nullptr) {
           // std::cout << "in check\n";
            tmp->recievedDmg(bullets[i]->getDamage());
           // std::cout << bullets.size() << "< < < < < <\n >>>>>>";
            bullets.erase(bullets.begin() + i);
           // std::cout << bullets.size() << "< < < < < <\n >>>>>>";
            i--;
            if (i < 0)
                break;
        }
       // std::cout << "Shooting\n";
    }
   // std::cout << "Finish Collision\n";
}

void GAME::playerShoot()
{
   // std::cout << "Shooting\n";
    sf::Vector2f pos = this->player->getPos();
    this->bullets.push_back(new BULLET(pos));
   // std::cout << "Done shooting\n";
}

void GAME::removeBullet()
{
    for (int i = 0; i < bullets.size(); i++) {
        if (bullets[i]->getMoveLength() == 0) {
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