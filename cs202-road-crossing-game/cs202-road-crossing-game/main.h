#pragma once
#include <chrono>
#include <conio.h>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <io.h>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <map>
#include <sstream>
#include <unordered_map> 
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <set>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Config.hpp>
#include <SFML/GpuPreference.hpp>
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#pragma warning(disable : 4996)

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
#define DESTROY_ZONE 150
#define MAX_ENEMY_TYPE 4
#define MAX_LEVEL 3

enum btnState {
    DEFAULT,
    HOVER,
    ACTIVE,
    btnStateCnt
};

enum Scene {
    MENUSCENE,
    INGAME,
    NEXTLEVEL,
    FINALLEVEL,
    PAUSEGAME,
    WINSCENE,
    LOSESCENE,
    ENDGAME,
    INSTRUCTIONSCENE,
    SAVEGAMESCENE,
    LOADGAMESCENE,
    sceneCnt
};

enum Alignment {
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT
};

enum btnFunc {
    NEWGAME,
    LOADGAME,
    TOGGLESOUND,
    TOGGLETHEME,
    EXIT
};

enum pauseMenuBtn {
    BACKTOGAME,
    RESTART,
    SAVEGAME,
    LEADERBOARD,
    BACKTOMENU
};

enum enemyType {
    SMALLMONSTER,
    BIGMONSTER,
    UFOENEMY,
    LASERENEMY
};

#include "SoundEffect.hpp"
#include "SoundManager.hpp"
#include "ANIMATION.h"
#include "TRAFFICLIGHT.h"
#include "SPACESHIP.h"
#include "UTILS.h"
#include "BULLET.h"
#include "BOSS.h"
#include "OPTIONS.h"
#include "MENU.h"
#include "SCREEN_MANAGER.h"  
#include "GUI.h"
#include "ENEMY_BASE.h"
#include "MONSTER.h"
#include "BIG_MONSTER.h"
#include "SMALL_MONSTER.h"
#include "OBSTACLE.h"
#include "LASER.h"
#include "UFO.h"
#include "LEVEL_MANAGER.h"
#include "ENEMY_CONTROLLER.h"
#include "GAME.h"