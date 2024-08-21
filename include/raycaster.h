// #pragma once

// class Raycaster {
// public:
//     void drawMiniMap() {}
//     void renderWorld() {}
//     void handelInput() {}
//     void update() {}
// private:
//     const int SCREEN_WIDTH = 640;
//     const int SCREEN_HEIGHT = 480;
//     const int MAP_WIDTH = 24;
//     const int MAP_HEIGHT = 24;
//     double player_x;
//     double player_y;
// };

#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <SDL.h>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "player.h"
#include "map.h"
#include <climits>
#include <utility>

#define PI 3.14159265359
// #define WALL_HEIGHT 

const int screenWidth = 1080;
const int screenHeight = 720;
const int numRays = 350;
const int fps = 60;
const int frameDelay = 1000 / fps;

class Raycaster {
public:
    Raycaster();
    void run();

private:
    void drawMiniMap();
    void handleEvents();
    void move();
    void raycast(bool debug);
    std::pair<bool, bool> checkCollision(int key, double x, double y, double dx, double dy);
    double getDist(double x1, double y1, double x2, double y2);

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Player player;
    Map map;
    std::unordered_map<SDL_KeyCode, int> keystate;
    int tileSize;
};

#endif

