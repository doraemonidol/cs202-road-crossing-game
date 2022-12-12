#include "OBSTACLE.h"
#include "UFO.h"
#include "METEOR.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "main.h"
#include "GUI.h"
#include "GAME.h"
#include <iostream>
//Private functions
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
    this->level = 1;
    this->scene = MENUSCENE;
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

void GAME::initEnemies()
{
    this->spawnTimerMax = 50.f;
    this->spawnTimer = this->spawnTimerMax;
    spawnTimeCheck += clock.getElapsedTime();
    std::cout << spawnTimeCheck.asSeconds() << "\n";
    if (spawnTimeCheck.asSeconds() < 0.05f) {
        return;
    }
    spawnTimeCheck = sf::seconds(0);
    int size = 0;
    int height = SCREEN_HEIGHT - 150;
    int minHeight = -1*(this->gui->getBGSize().y - SCREEN_HEIGHT);
    std::cout << height << " " << minHeight << "\n";
    while (height >= minHeight) {
        std::cout << "doing here\n";
        int isSpawn = rand() % 2;
        if (isSpawn == 0) {
            height -= 150;
            continue;
        }
        int type = rand() % 4 + 1;
        std::cout << type << std::endl;
        int dir = rand() % 2;
        dir = dir == 1 ? 1 : -1;
        int pos = dir == 1 ? -100 : this->window->getSize().x + 160;
        if (type == 1) {
            monsters.push_back(new BIG_MONSTER(dir, pos, height));
        }
        else if (type == 2) {
            monsters.push_back(new SMALL_MONSTER(dir, pos, height));
        }
        else if (type == 3) {
            obstacles.push_back(new UFO(dir, pos, height));
        }
        else{
            obstacles.push_back(new METEOR(dir, pos, height));
        }
        height -= 150;
    }
   /* removeOutOfBoundEnemies();*/
}

void GAME::initGUI() {
    this->gui = new GUI(this->window, this->player);
}

void GAME::initMenu() {
    menu = MENU(200, 200);
    menu.init();
}

    //Con/Des
GAME::GAME()
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
    this->spawnTimeCheck = clock.getElapsedTime();
    this->initEnemies();

}

GAME::GAME(const int a) {
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

    //Delete textures
    for (auto& i : this->textures) {
        delete i.second;
    }

    for (MONSTER* monster : this->monsters) {
        delete monster;
    }
    monsters.clear();
}

//Functions
void GAME::run()
{
    while (this->window->isOpen()) {
        soundController->update();
        deltaTime = clock.restart().asSeconds();
        this->updatePollEvents();
        if (this->player->getHp() > 0)
            this->update();
        this->render();
        /*this->saveGame();*/
    }
}

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
}

void GAME::updateView() {
    float y = player->getPos().y;
    if (y > SCREEN_HEIGHT / 2)
        y = SCREEN_HEIGHT / 2;
    int tmp = (SCREEN_HEIGHT - this->gui->getBGSize().y);
    if (y < SCREEN_HEIGHT / 2 + tmp)
        y = SCREEN_HEIGHT / 2.0f + tmp;

    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, y));
    this->window->setView(view);
}

void GAME::update()
{
    switch (scene) {
    case INGAME:
        this->checkCollision();
        //std::cout << "Mouse pos: " << sf::Mouse::getPosition(*this->window).x << " " << sf::Mouse::getPosition(*this->window).y << "\n";
        // this->updateInput();
        this->initEnemies();
        this->player->update(this->gui->getBGSize().y, deltaTime);

        this->gui->update(this->level);

        this->updateWorld();

        this->updateView();
        break;
    }
}

void GAME::renderWorld()
{
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

        // Draw all the stuffs
        this->player->render(*this->window);
        for (int i = 0; i < monsters.size(); i++) {
            monsters[i]->update();
            monsters[i]->render(*this->window);
        }
        for (int i = 0; i < obstacles.size(); i++) {
            obstacles[i]->update();
            obstacles[i]->render(*this->window);
        }

        // Game over screen
        if (this->player->getHp() <= 0)
            this->gui->renderWin();
        break;

    case PAUSEGAME:
        this->renderWorld();
        this->gui->render();

        // Draw all the stuffs
        this->player->render(*this->window);
        for (int i = 0; i < monsters.size(); i++) {
            monsters[i]->render(*this->window);
        }
        for (int i = 0; i < obstacles.size(); i++) {
            obstacles[i]->render(*this->window);
        }
        this->gui->renderPauseMenu();
        break;

    case WINSCENE:
        this->renderWorld();
        this->gui->render();

        // Draw all the stuffs
        this->player->render(*this->window);
        for (int i = 0; i < monsters.size(); i++) {
            monsters[i]->render(*this->window);
        }
        for (int i = 0; i < obstacles.size(); i++) {
            obstacles[i]->render(*this->window);
        }
        this->gui->renderWin();
        break;

    case LOSESCENE:
        if (isDead) {
            isDead = !(this->player->upDead(deltaTime));
        }
        this->renderWorld();
        this->gui->render();

        // Draw all the stuffs
        this->player->render(*this->window);
        this->player->renderDead(*this->window);
        for (int i = 0; i < monsters.size(); i++) {
            monsters[i]->render(*this->window);
        }
        for (int i = 0; i < obstacles.size(); i++) {
            obstacles[i]->render(*this->window);
        }
        if (!isDead)
            this->gui->renderLose();
        break;
    
    }

    this->window->display();
}


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
    file.write((char*)&spawnTimer, sizeof(float));

    file.write((char*)&spawnTimerMax, sizeof(float));
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
    file2.read((char*)&this->spawnTimer, sizeof(float));
    file2.read((char*)&this->spawnTimerMax, sizeof(float));
    file2.close();
}

GAME& GAME::operator=(GAME other) {
    std::swap(window, other.window);
    /*std::swap()*/
    return *this;
}

void GAME::playMusic(std::string file)
{
    std::cout << "music1\n";
    soundController->playSound(file);
}

void GAME::playSound(std::string file)
{
    std::cout << "music4\n";
    soundController->playEffect(file);
}

void GAME::setSPACESHIP(SPACESHIP player) {
    swap(this->player, &player);
}

void GAME::setGUI(GUI gui) {
    swap(this->gui, &gui);
}

void GAME::setSpawnTimer(float spawnTimer) {
    this->spawnTimer = spawnTimer;
}

void GAME::setSpawnTimerMax(float spawnTimerMax) {
    this->spawnTimerMax = spawnTimerMax;
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

void GAME::removeOutOfBoundEnemies() {
    /*for (int i = 0; i < monsters.size(); i++) {
        if (monsters[i]->getDir() == 1 and monsters[i]->getPosition() > this->window->getSize().x + 100) {
            delete monsters[i];
            monsters.remove(monsters[i]);
            i--;
        }
    }*/
}


void GAME::checkCollision() {
    //return;
    for (MONSTER* monster : this->monsters) {
        if (monster->getSprite().getGlobalBounds().intersects(this->player->getSprite().getGlobalBounds())) {
            scene = LOSESCENE;
            isDead = true;
            playMusic(music["LOSE"]);
            this->gui->initLose();
            
            std::cout << "Lost case!" << std::endl;
        }
    }
    for (OBSTACLE* obstacle : this->obstacles) {
        if (obstacle->getSprite().getGlobalBounds().intersects(this->player->getSprite().getGlobalBounds())) {
            scene = LOSESCENE;
            isDead = true;
            playMusic(music["LOSE"]);
            this->gui->initLose();

            std::cout << "Lost case!" << std::endl;
        }
    }
    int minHeight = -1 * (this->gui->getBGSize().y - SCREEN_HEIGHT);
    if (this->player->getPos().y == minHeight) {
        scene = WINSCENE;
        playMusic(music["WIN"]);
        this->gui->initWin();

        std::cout << "Win case!" << std::endl;
    }
}

//reset game
void GAME::resetGame()
{
    playMusic(music["INGAME"]);
    // scene = MENUSCENE;
    view.setCenter(sf::Vector2f(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.0f));
    this->window->setView(view);
    delete this->player;
    this->initPlayer();
    monsters.clear();
    obstacles.clear();
    this->spawnTimeCheck = clock.getElapsedTime();
    this->initEnemies();
    //this->gui->initPauseMenu();

}