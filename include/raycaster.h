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
#include <SDL_image.h>
#include <vector>
#include <cmath>
#include <unordered_map>
#include "player.h"
#include "map.h"
#include <climits>
#include <utility>
#include <string>
#include "movement.h"

#define PI 3.14159265359
// #define WALL_HEIGHT 

const int screenWidth = 1080;
const int screenHeight = 720;
const int numRays = 360;
const int fps = 60;
const int frameDelay = 1000 / fps;

class Raycaster {
public:
    Raycaster();
    void run();

private:
    void drawMiniMap();
    void handleEvents();
    void handleMouseMotion();
    void move();
    void raycast(bool debug);
    SDL_Texture* loadTexture(const std::string &path, SDL_Renderer *renderer);
    void renderCrosshair();
    void renderGun();
    bool checkCollision(double x, double y);
    double getDist(double x1, double y1, double x2, double y2);
    PlayerState getPlayerState();

    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;

    Player player;
    Map map;
    std::unordered_map<SDL_KeyCode, int> keystate;
    int tileSize;
    int menu;
    int inc;                // bobbing left or right
    SDL_Texture* crosshairTexture;
    SDL_Texture* gunTexture;
    SDL_Texture* wall1;

    // tmp
    double recoilAngle;
};

#endif

