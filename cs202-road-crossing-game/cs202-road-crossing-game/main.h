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

enum btnState {
    DEFAULT,
    HOVER,
    ACTIVE,
    btnStateCnt
};

enum Scene {
    MENUSCENE,
    INGAME,
    PAUSEGAME,
    WINSCENE,
    LOSESCENE,
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