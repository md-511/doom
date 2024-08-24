// #include "raycaster.h"
// #include <SDL.h>

#include "raycaster.h"
#include <cmath>
#include <iostream>

Raycaster::Raycaster() : running(true), window(nullptr), renderer(nullptr) {
    // INITIALIZING

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Error occured while initializing " << SDL_GetError() << std::endl;
        SDL_Quit();
        exit(1);
    }

    // CREATING RENDERER

    window = SDL_CreateWindow("Run N' Gun", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer) {
        std::cout << "Error occured while creating renderer " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    // SETTING KEYBOARD STATE

    keystate[SDLK_w] = 0;
    keystate[SDLK_a] = 0;
    keystate[SDLK_s] = 0;
    keystate[SDLK_d] = 0;
    keystate[SDLK_LEFT] = 0;
    keystate[SDLK_RIGHT] = 0;
    // keystate[SDLK_ESCAPE] = 0;

    // SETTING PLAYER INITIAL VALUES

    // player.x = screenWidth / 2; player.y = screenHeight / 2;
    // Player's initial position should be inside the map bounds.
    // player.x = 12; // or some valid position
    // player.y = 10;

    // player.dirX = 0; player.dirY = -1;
    // player.planeX = 0; player.planeY = 0.66;

    // player.x = 12; // Ensure this is a valid starting position in the map.
    // player.y = 10; // Ensure this is a valid starting position in the map.
    // player.dirX = 0; // Direction should be valid.
    // player.dirY = -1;
    // player.planeX = 0;
    // player.planeY = 0.66;


    // player.speed = 0.05;

    // SETTING THE MAP UP

    map.width = 24;
    map.height = 24;
    map.data = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
        {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // map.height = 13;
    // map.width = 50;
    // map.data = {
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1},
    //     {1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 1},
    //     {1, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 0, 2, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 2, 2, 2, 0, 2, 0, 1},
    //     {1, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 0, 2, 0, 0, 0, 0, 2, 0, 2, 0, 1},
    //     {1, 0, 2, 0, 2, 0, 3, 3, 3, 3, 3, 0, 2, 0, 3, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 2, 0, 2, 0, 3, 3, 0, 2, 0, 2, 0, 1},
    //     {1, 0, 2, 0, 2, 0, 3, 0, 0, 0, 3, 0, 2, 0, 3, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 0, 3, 0, 3, 0, 2, 2, 0, 2, 0, 1},
    //     {1, 0, 2, 0, 2, 0, 3, 0, 3, 0, 3, 0, 2, 0, 3, 0, 3, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 3, 3, 0, 3, 0, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 0, 3, 0, 1},
    //     {1, 0, 2, 0, 2, 0, 3, 0, 3, 0, 3, 0, 2, 0, 3, 0, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 3, 3, 0, 3, 0, 3, 3, 0, 3, 0, 3, 0, 3, 0, 3, 3, 0, 3, 0, 1},
    //     {1, 0, 2, 0, 2, 0, 3, 0, 3, 0, 3, 0, 2, 0, 3, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 3, 3, 0, 3, 0, 2, 2, 0, 2, 0, 3, 0, 3, 0, 3, 3, 0, 3, 0, 1},
    //     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    // };

    // map.width = 50;
    // map.height = 50;
    // map.data = {
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    //     {1,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,3,3,0,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,3,3,0,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,3,3,0,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,3,3,0,3,3,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    // };

    // map.width = 50;
    // map.height = 50;
    // map.data = {
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    //     {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
    //     {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1},
    //     {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,2,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,1,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    //     {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    // };

    tileSize = std::min(screenWidth / map.width, screenHeight / map.height);

    player.x = map.width * tileSize / 2, player.y = map.height * tileSize / 2;
    player.a = 0;
    player.speed = 1;
    player.rotationSpeed = 0.05;
    player.dx = cos(player.a);
    player.dy = sin(player.a);
    player.fov = 60;
    player.distFromPlane = screenWidth / 2 / tan(PI * player.fov / 2 / 180);
    player.pitch = 0;
    player.offsetX = 0;
    player.offsetY = pow(sin(tan(player.offsetX)), 2);


    // tmp
    menu = false;
    inc = true;
    recoilAngle = 0;

    crosshairTexture = loadTexture("../assets/crosshair.png", renderer);
    gunTexture = loadTexture("../assets/handMain.png", renderer);
}

SDL_Texture* Raycaster::loadTexture(const std::string &path, SDL_Renderer *renderer) {
    SDL_Texture *newTexture = nullptr;
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == nullptr) {
        std::cout << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
    } else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            std::cout << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}

void Raycaster::renderCrosshair() {
    float scale = 0.07f;
    // Calculate center position
    int crosshairWidth, crosshairHeight;
    SDL_QueryTexture(crosshairTexture, NULL, NULL, &crosshairWidth, &crosshairHeight);
    crosshairHeight *= scale;
    crosshairWidth *= scale;
    int crosshairX = (screenWidth - crosshairWidth) / 2;
    int crosshairY = (screenHeight - crosshairHeight) / 2;

    // Render crosshair
    SDL_Rect dstRect = {crosshairX, crosshairY, crosshairWidth, crosshairHeight};
    SDL_RenderCopy(renderer, crosshairTexture, NULL, &dstRect);
}

void Raycaster::renderGun() {
    float scale = 1.0f;
    int gunWidth, gunHeight;
    SDL_QueryTexture(gunTexture, NULL, NULL, &gunWidth, &gunHeight);
    gunWidth *= scale;
    gunHeight *= scale;
    int gunX = screenWidth - 0.85 * gunWidth + player.offsetX * 50;
    int gunY = screenHeight - gunHeight + 50 - player.offsetY * 50;

    SDL_Rect gunRect = {gunX, gunY, gunWidth, gunHeight};
    SDL_Point center = {gunWidth / 2, gunHeight};
    // SDL_RenderCopy(renderer, gunTexture, NULL, &gunRect);
    SDL_RenderCopyEx(renderer, gunTexture, NULL, &gunRect, recoilAngle, &center, SDL_FLIP_NONE);
    // recoilAngle = 0;
}

void Raycaster::run() {

    Uint32 prevTime = SDL_GetTicks();
    double accumulatedTime = 0.0;

    while (running) {
        Uint32 currTime = SDL_GetTicks();

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        accumulatedTime += currTime - prevTime;
        prevTime = currTime;

        if (accumulatedTime >= frameDelay) {
            handleEvents();
            move();
            accumulatedTime -= frameDelay;
        }

        raycast(false);
        renderCrosshair();
        renderGun();
        drawMiniMap();
        SDL_RenderPresent(renderer);
        // recoilAngle = 0;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Raycaster::handleEvents() {
    if (!menu) {
        SDL_SetRelativeMouseMode(SDL_TRUE);
    } else {
        SDL_SetRelativeMouseMode(SDL_FALSE);
    }

    // std::cout << menu << std::endl;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        keystate[SDLK_w] = 1;
                        // std::cout << "Up arrow key pressed!" << std::endl;
                        break;
                    case SDLK_a:
                        keystate[SDLK_a] = 1;
                        // std::cout << "Down arrow key pressed!" << std::endl;
                        break;
                    case SDLK_s:
                        keystate[SDLK_s] = 1;
                        // std::cout << "Left arrow key pressed!" << std::endl;
                        break;
                    case SDLK_d:
                        keystate[SDLK_d] = 1;
                        // std::cout << "Right arrow key pressed!" << std::endl;
                        break;
                    case SDLK_LEFT:
                        keystate[SDLK_LEFT] = 1;
                        break;
                    case SDLK_RIGHT:
                        keystate[SDLK_RIGHT] = 1;
                        break;
                    case SDLK_ESCAPE:
                        menu = !menu;
                        break;
                    default:
                        // std::cout << "Other key pressed: " << event.key.keysym.sym << std::endl;
                        break;
                }
                break;

            case SDL_KEYUP:
                // Handle key release if needed
                switch (event.key.keysym.sym) {
                    case SDLK_w:
                        keystate[SDLK_w] = 0;
                        // std::cout << "Up arrow key released!" << std::endl;
                        break;
                    case SDLK_a:
                        keystate[SDLK_a] = 0;
                        // std::cout << "Down arrow key released!" << std::endl;
                        break;
                    case SDLK_s:
                        keystate[SDLK_s] = 0;
                        // std::cout << "Left arrow key released!" << std::endl;
                        break;
                    case SDLK_d:
                        keystate[SDLK_d] = 0;
                        // std::cout << "Right arrow key released!" << std::endl;
                        break;
                    case SDLK_LEFT:
                        keystate[SDLK_LEFT] = 0;
                        break;
                    case SDLK_RIGHT:
                        keystate[SDLK_RIGHT] = 0;
                        break;
                    default:
                        // std::cout << "Other key released: " << event.key.keysym.sym << std::endl;
                        break;
                }
                break;

            case SDL_MOUSEMOTION:
                if (!menu) handleMouseMotion();
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    std::cout << "Bang!" << std::endl;
                    if (recoilAngle <= 2) recoilAngle = 10;
                }
                break;

            default:
                break;
        }
    }

    // keystate = SDL_GetKeyboardState(NULL);

    // if (keystate[SDL_SCANCODE_UP]) {
    //     std::cout << "Up arrow key is pressed!" << std::endl;
    // }
    // if (keystate[SDL_SCANCODE_DOWN]) {
    //     std::cout << "Down arrow key is pressed!" << std::endl;
    // }
    // if (keystate[SDL_SCANCODE_LEFT]) {
    //     std::cout << "Left arrow key is pressed!" << std::endl;
    // }
    // if (keystate[SDL_SCANCODE_RIGHT]) {
    //     std::cout << "Right arrow key is pressed!" << std::endl;
    // }
    if (recoilAngle > 0) recoilAngle -= 1;
}

void Raycaster::handleMouseMotion() {
    int mouseX, mouseY;
    SDL_GetRelativeMouseState(&mouseX, &mouseY);

    // Sensitivity multiplier
    double sensitivity = 0.0005;

    // Adjust player direction based on mouse movement
    player.a += mouseX * sensitivity;
    player.pitch -= mouseY * sensitivity;

    double maxPitch = PI / 2;
    if (player.pitch > maxPitch) player.pitch = maxPitch;
    if (player.pitch < -maxPitch) player.pitch = -maxPitch;

    // Keep angle within 0 to 2*PI
    if (player.a < 0) player.a += 2 * M_PI;
    if (player.a >= 2 * M_PI) player.a -= 2 * M_PI;

    // Update direction vector
    player.dx = cos(player.a);
    player.dy = sin(player.a);
}

// void Raycaster::drawMiniMap() {

//     // int tileSize = ;

//     for (int y = 0; y < map.width; y++) {
//         for (int x = 0; x < map.height; x++) {
//             if (map.data[y][x] != 0) {
//                 SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
//             } else {
//                 SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
//             }
//             SDL_Rect tile;
//             tile.x = x * tileSize+0.5;
//             tile.y = y * tileSize+0.5;
//             tile.w = tileSize-0.5;
//             tile.h = tileSize-0.5;
//             SDL_RenderFillRect(renderer, &tile);
//         }
//     }

//     // Draw the player

//     SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
//     SDL_Rect playerRect;

//     playerRect.w = tileSize/2;
//     playerRect.h = tileSize/2;
//     playerRect.x = player.x - playerRect.w/2;
//     playerRect.y = player.y - playerRect.h/2;

//     SDL_RenderFillRect(renderer, &playerRect);

//     SDL_RenderDrawLine(renderer, player.x, player.y, player.x + player.dx*15, player.y + player.dy*15);

// }



void Raycaster::drawMiniMap() {
    int minimapSize = 150; // Define the size for the minimap
    double scaleFactor = static_cast<double>(minimapSize) / (map.width * tileSize);

    for (int y = 0; y < map.height; y++) {
        for (int x = 0; x < map.width; x++) {
            if (map.data[y][x] != 0) {
                SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  // Wall color
            } else {
                SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);  // Empty space color
            }

            SDL_Rect tile;
            tile.x = x * tileSize * scaleFactor;  // Scale down the x position
            tile.y = y * tileSize * scaleFactor;  // Scale down the y position
            tile.w = tileSize * scaleFactor + 5;  // Scale down the width
            tile.h = tileSize * scaleFactor + 5;  // Scale down the height

            SDL_RenderFillRect(renderer, &tile);
        }
    }

    // Draw the player on the minimap
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);  // Player color

    SDL_Rect playerRect;
    playerRect.w = (tileSize / 2) * scaleFactor;
    playerRect.h = (tileSize / 2) * scaleFactor;
    playerRect.x = player.x * scaleFactor - playerRect.w / 2;
    playerRect.y = player.y * scaleFactor - playerRect.h / 2;

    SDL_RenderFillRect(renderer, &playerRect);

    // Draw the player's direction line on the minimap
    SDL_RenderDrawLine(
        renderer,
        player.x * scaleFactor,
        player.y * scaleFactor,
        (player.x + player.dx * 15) * scaleFactor,
        (player.y + player.dy * 15) * scaleFactor
    );
}



// void Raycaster::move() {
//     if (keystate[SDLK_w]) {
//         player.x += player.dirX * player.speed;
//         player.y += player.dirY * player.speed;
//     }
//     if (keystate[SDLK_a]) {
//         player.x += player.dirY * player.speed;
//         player.y += -player.dirX * player.speed;
//     }
//     if (keystate[SDLK_s]) {
//         player.x += -player.dirX * player.speed;
//         player.y += -player.dirY * player.speed;
//     }
//     if (keystate[SDLK_d]) {
//         player.x += -player.dirY * player.speed;
//         player.y += player.dirX * player.speed;
//     }
//     if (keystate[SDLK_LEFT]) {
//         double oldX = player.dirX;
//         double oldY = player.dirY;
//         player.dirX = oldX * cos(-DEG) - oldY * sin(-DEG);
//         player.dirY = oldX * sin(-DEG) + oldY * cos(-DEG);

//         double oldPlaneX = player.planeX;
//         double oldPlaneY = player.planeY;
//         player.planeX = oldPlaneX * cos(-DEG) - oldPlaneY * sin(-DEG);
//         player.planeY = oldPlaneX * sin(-DEG) + oldPlaneY * cos(-DEG);
//     }
//     if (keystate[SDLK_RIGHT]) {
//         double oldX = player.dirX;
//         double oldY = player.dirY;
//         player.dirX = oldX * cos(DEG) - oldY * sin(DEG);
//         player.dirY = oldX * sin(DEG) + oldY * cos(DEG);

//         double oldPlaneX = player.planeX;
//         double oldPlaneY = player.planeY;
//         player.planeX = oldPlaneX * cos(DEG) - oldPlaneY * sin(DEG);
//         player.planeY = oldPlaneX * sin(DEG) + oldPlaneY * cos(DEG);
//     }
// }

PlayerState Raycaster::getPlayerState() {
    int w = keystate[SDLK_w];
    int a = keystate[SDLK_a];
    int s = keystate[SDLK_s];
    int d = keystate[SDLK_d];

    // 4 keys
    if (w && a && s && d) return STATIONARY;

    // 3 keys
    if (w && a && s) return LEFT;
    if (w && a && d) return FORWARD;
    if (w && s && d) return RIGHT;
    if (d && a && s) return BACKWARDS;

    // 2 keys
    if (w && a) return LEFT_FRONT;
    if (w && s) return STATIONARY;
    if (w && d) return RIGHT_FRONT;
    if (a && s) return LEFT_BACK;
    if (d && s) return RIGHT_BACK;
    if (a && d) return STATIONARY;

    // 1 key
    if (w) return FORWARD;
    if (s) return BACKWARDS;
    if (a) return LEFT;
    if (d) return RIGHT;

    return STATIONARY;

}

void Raycaster::move() {
    PlayerState state = getPlayerState();

    if (state != STATIONARY) {
        double newX = player.x, newY = player.y;
        switch (state)
        {
            case FORWARD:
                newX += player.dx * player.speed;
                newY += player.dy * player.speed;
                break;
            
            case BACKWARDS:
                newX += -player.dx * player.speed;
                newY += -player.dy * player.speed;
                break;
            
            case LEFT:
                newX += player.dy * player.speed;
                newY += -player.dx * player.speed;
                break;

            case RIGHT:
                newX += -player.dy * player.speed;
                newY += player.dx * player.speed;
                break;

            case LEFT_FRONT:
                newX += (player.dx + player.dy) / sqrt(2) * player.speed;
                newY += (player.dy - player.dx) / sqrt(2) * player.speed;
                break;
            
            case RIGHT_FRONT:
                newX += (player.dx - player.dy) / sqrt(2) * player.speed;
                newY += (player.dy + player.dx) / sqrt(2) * player.speed;
                break;

            case LEFT_BACK:
                newX += (player.dy - player.dx) / sqrt(2) * player.speed;
                newY += (-player.dx - player.dy) / sqrt(2) * player.speed;
                break;

            case RIGHT_BACK:
                newX += (-player.dy - player.dx) / sqrt(2) * player.speed;
                newY += (player.dx - player.dy) / sqrt(2) * player.speed;
                break;

            default:
                std::cout << "Invalid State!" << std::endl;
                exit(1);
                break;
        }

        if (!checkCollision(newX, player.y)) {
            player.x = newX;
        }

        if (!checkCollision(player.x, newY)) {
            player.y = newY;
        }

        if (inc) {
            player.offsetX += 0.1;
        } else {
            player.offsetX -= 0.1;
        }

        if (player.offsetX >= 1) inc = 0;
        if (player.offsetX <= -1) inc = 1;

        player.offsetY = pow(sin(tan(player.offsetX)), 2);

    } else {
        // std::cout << player.offsetX << std::endl;

        if (abs(player.offsetX) < 0.01) {
            player.offsetX = 0;
        } else if (player.offsetX < 0) {
            player.offsetX += 0.1;
        } else if (player.offsetX > 0) {
            player.offsetX -= 0.1;
        }

        player.offsetY = pow(sin(tan(player.offsetX)), 2);
    }

    // if (keystate[SDLK_w]) {
    //     // player.x += player.dirX * player.speed;
    //     // player.y += player.dirY * player.speed;
    //     std::pair<bool, bool> collisionStatus = checkCollision(0, player.x, player.y, player.dx, player.dy);

    //     if (!collisionStatus.first) {
    //         player.x += player.dx;
    //     }

    //     if (!collisionStatus.second) {
    //         player.y += player.dy;
    //     }

    //     if (inc) {
    //         player.offsetX += 0.1;
    //     } else {
    //         player.offsetX -= 0.1;
    //     }

    //     if (player.offsetX >= 1) inc = 0;
    //     if (player.offsetX <= -1) inc = 1;

    //     player.offsetY = pow(sin(tan(player.offsetX)), 2);
    // }
    // if (keystate[SDLK_s]) {
    //     // player.x -= player.dirX * player.speed;
    //     // player.y -= player.dirY * player.speed;
    //     std::pair<bool, bool> collisionStatus = checkCollision(1, player.x, player.y, player.dx, player.dy);

    //     if (!collisionStatus.first) {
    //         player.x -= player.dx;
    //     }

    //     if (!collisionStatus.second) {
    //         player.y -= player.dy;
    //     }

    //     if (inc) {
    //         player.offsetX += 0.1;
    //     } else {
    //         player.offsetX -= 0.1;
    //     }

    //     if (player.offsetX >= 1) inc = 0;
    //     if (player.offsetX <= -1) inc = 1;

    //     player.offsetY = pow(sin(tan(player.offsetX)), 2);
    // }
    // if (keystate[SDLK_a]) {
    //     // player.x += player.dirY * player.speed;
    //     // player.y -= player.dirX * player.speed;
    //     std::pair<bool, bool> collisionStatus = checkCollision(2, player.x, player.y, player.dx, player.dy);

    //     if (!collisionStatus.first) {
    //         player.x += player.dy;
    //     }

    //     if (!collisionStatus.second) {
    //         player.y -= player.dx;
    //     }

    //     if (inc) {
    //         player.offsetX += 0.1;
    //     } else {
    //         player.offsetX -= 0.1;
    //     }

    //     if (player.offsetX >= 1) inc = 0;
    //     if (player.offsetX <= -1) inc = 1;

    //     player.offsetY = pow(sin(tan(player.offsetX)), 2);
    // }
    // if (keystate[SDLK_d]) {
    //     // player.x -= player.dirY * player.speed;
    //     // player.y += player.dirX * player.speed;
    //     std::pair<bool, bool> collisionStatus = checkCollision(3, player.x, player.y, player.dx, player.dy);

    //     if (!collisionStatus.first) {
    //         player.x -= player.dy;
    //     }

    //     if (!collisionStatus.second) {
    //         player.y += player.dx;
    //     }

    //     if (inc) {
    //         player.offsetX += 0.1;
    //     } else {
    //         player.offsetX -= 0.1;
    //     }

    //     if (player.offsetX >= 1) inc = 0;
    //     if (player.offsetX <= -1) inc = 1;

    //     player.offsetY = pow(sin(tan(player.offsetX)), 2);
    // }
    if (keystate[SDLK_LEFT]) {
        player.a -= player.rotationSpeed;
        if (player.a < 0) { player.a += 2*PI; }
        player.dx = cos(player.a);
        player.dy = sin(player.a);
    }
    if (keystate[SDLK_RIGHT]) {
        player.a += player.rotationSpeed;
        if (player.a > 2*PI) { player.a -= 2*PI; }
        player.dx = cos(player.a);
        player.dy = sin(player.a);
    }

    // std::cout << "Speed: " << sqrt(pow(player.dx, 2) + pow(player.dy, 2));
}

bool Raycaster::checkCollision(double x, double y) {
    int mapX = static_cast<int>(x / tileSize), mapY = static_cast<int>(y / tileSize);
    // std::cout << "MapX: " << mapX << " MapY: " << mapY << " Wall: " << (map.data[mapX][mapY] > 0) << std::endl;
    return map.data[mapY][mapX] > 0;
}

//     float oldDirX = player.dirX;
//     player.dirX = player.dirX * cos(rotSpeed) - player.dirY * sin(rotSpeed);
//     player.dirY = oldDirX * sin(rotSpeed) + player.dirY * cos(rotSpeed);

//     // Store the old plane
//     float oldPlaneX = player.planeX;
//     player.planeX = player.planeX * cos(rotSpeed) - player.planeY * sin(rotSpeed);
//     player.planeY = oldPlaneX * sin(rotSpeed) + player.planeY * cos(rotSpeed);
// }

// void Raycaster::raycast() {
//     int hHit = 0;
//     double hx = 0, hy = 0;
//     double firstX, firstY;
//     double ra = player.a;

//     bool facingDown = ra > 0 && ra < PI;
//     bool facingUp = !facingDown;

//     // Debugging: print the ray angle and facing direction
//     // printf("Ray Angle: %f, Facing Up: %d, Facing Down: %d\n", ra, facingUp, facingDown);

//     // Adjust firstY based on whether we're facing up or down
//     if (facingUp) {
//         firstY = floor(player.y / tileSize) * tileSize - 0.00001;
//     } else if (facingDown) {
//         firstY = floor(player.y / tileSize) * tileSize + tileSize;
//     }

//     // Calculate firstX using the adjusted firstY
//     firstX = (firstY - player.y) / tan(ra) + player.x;

//     double nextX = firstX, nextY = firstY;

//     double xo, yo;

//     // Set step values for the ray
//     if (facingUp) {
//         yo = -tileSize;
//     } else if (facingDown) {
//         yo = tileSize;
//     }

//     xo = yo / tan(ra);

//     // Debugging: print the initial values
//     // printf("Initial Values -> nextX: %f, nextY: %f, xo: %f, yo: %f\n", nextX, nextY, xo, yo);

//     // Cast the ray until we hit a wall or go out of bounds
//     while (nextX <= screenWidth && nextX >= 0 && nextY <= screenHeight && nextY >= 0) {
//         int mapX = static_cast<int>(nextX / tileSize);
//         int mapY = static_cast<int>(nextY / tileSize);

//         // Debugging: print the map indices
//         // printf("Checking map position -> mapX: %d, mapY: %d\n", mapX, mapY);

//         // Check for a wall hit
//         if (mapX < map.width && mapY < map.height && map.data[mapY][mapX]) {
//             hHit = 1;
//             hx = nextX;
//             hy = nextY;
//             // printf("Hit at -> hx: %f, hy: %f\n", hx, hy);
//             break;
//         } else {
//             nextX += xo;
//             nextY += yo;
//             // Debugging: print new position after stepping
//             // printf("New Position -> nextX: %f, nextY: %f\n", nextX, nextY);
//         }
//     }

//     // Draw the line from the player to the hit position
//     // if (hit) {
//     //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set color for debugging
//     //     SDL_RenderDrawLine(renderer, player.x, player.y, hx, hy);
//     // }

//     // Vertical

//     int vHit = 0;
//     bool facingRight = ra < PI/2 || ra > 3*PI/2;
//     bool facingLeft = !facingRight;

//     double vx = 0, vy = 0;

//     if (facingRight) {
//         firstX = floor(player.x / tileSize) * tileSize + tileSize;
//     } else if (facingLeft) {
//         firstX = floor(player.x / tileSize) * tileSize - 0.00001;
//     }

//     firstY = player.y + (firstX - player.x) * tan(ra);

//     nextX = firstX;
//     nextY = firstY;

//     if (facingRight) {
//         xo =  tileSize;
//     } else if (facingLeft) {
//         xo = -tileSize;
//     }

//     yo = xo * tan(ra);

//     while (nextX <= screenWidth && nextX >= 0 && nextY <= screenHeight && nextY >= 0) {
//         int mapX = static_cast<int>(nextX / tileSize);
//         int mapY = static_cast<int>(nextY / tileSize);

//         // Debugging: print the map indices
//         // printf("Checking map position -> mapX: %d, mapY: %d\n", mapX, mapY);

//         // Check for a wall hit
//         if (mapX < map.width && mapY < map.height && map.data[mapY][mapX]) {
//             vHit = 1;
//             vx = nextX;
//             vy = nextY;
//             // printf("Hit at -> hx: %f, hy: %f\n", hx, hy);
//             break;
//         } else {
//             nextX += xo;
//             nextY += yo;
//             // Debugging: print new position after stepping
//             // printf("New Position -> nextX: %f, nextY: %f\n", nextX, nextY);
//         }
//     }

//     // Draw the line from the player to the hit position
//     // if (hit) {
//     //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set color for debugging
//     //     SDL_RenderDrawLine(renderer, player.x, player.y, vx, vy);
//     // }

//     double hDist, vDist;

//     if (hHit) {
//         hDist = getDist(player.x, player.y, hx, hy);
//     } else {
//         hDist = 9999999;
//     }

//     if (vHit) {
//         vDist = getDist(player.x, player.y, vx, vy);
//     } else {
//         vDist = 9999999;
//     }

//     // double hDist = getDist(player.x, player.y, hx, hy);
//     // double vDist = getDist(player.x, player.y, vx, vy);

//     double hitX, hitY;

//     if (hDist < vDist) {
//         hitX = hx;
//         hitY = hy;
//     } else {
//         hitX = vx;
//         hitY = vy;
//     }

//     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set color for debugging
//     SDL_RenderDrawLine(renderer, player.x, player.y, hitX, hitY);

// }

void Raycaster::raycast(bool debug=false) {

    double ra = player.a - PI * player.fov / 2 / 180;
    double stepSize = (player.fov / (double)numRays) * PI / 180;
    // std::cout << stepSize << std::endl;
    double dist;

    for (int i = 0; i < numRays; i++) {
        int hHit = 0;
        double hx = 0, hy = 0;
        double firstX, firstY;

        bool facingDown = ra > 0 && ra < PI;
        bool facingUp = !facingDown;

        // Debugging: print the ray angle and facing direction
        // printf("Ray Angle: %f, Facing Up: %d, Facing Down: %d\n", ra, facingUp, facingDown);

        // Adjust firstY based on whether we're facing up or down
        if (facingUp) {
            firstY = floor(player.y / tileSize) * tileSize - 0.00001;
        } else if (facingDown) {
            firstY = floor(player.y / tileSize) * tileSize + tileSize;
        }

        // Calculate firstX using the adjusted firstY
        firstX = (firstY - player.y) / tan(ra) + player.x;

        double nextX = firstX, nextY = firstY;

        double xo, yo;

        // Set step values for the ray
        if (facingUp) {
            yo = -tileSize;
        } else if (facingDown) {
            yo = tileSize;
        }

        xo = yo / tan(ra);

        // Debugging: print the initial values
        // printf("Initial Values -> nextX: %f, nextY: %f, xo: %f, yo: %f\n", nextX, nextY, xo, yo);

        // Cast the ray until we hit a wall or go out of bounds
        while (nextX <= screenWidth && nextX >= 0 && nextY <= screenHeight && nextY >= 0) {
            int mapX = static_cast<int>(nextX / tileSize);
            int mapY = static_cast<int>(nextY / tileSize);

            // Debugging: print the map indices
            // printf("Checking map position -> mapX: %d, mapY: %d\n", mapX, mapY);

            // Check for a wall hit
            if (mapX < map.width && mapY < map.height && map.data[mapY][mapX]) {
                // if (map.data[mapY][mapX] == 1) SDL_SetRenderDrawColor(renderer, 217, 105, 98, 255);
                hHit = 1;
                hx = nextX;
                hy = nextY;
                // printf("Hit at -> hx: %f, hy: %f\n", hx, hy);
                break;
            } else {
                nextX += xo;
                nextY += yo;
                // Debugging: print new position after stepping
                // printf("New Position -> nextX: %f, nextY: %f\n", nextX, nextY);
            }
        }

        // Draw the line from the player to the hit position
        // if (hit) {
        //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set color for debugging
        //     SDL_RenderDrawLine(renderer, player.x, player.y, hx, hy);
        // }

        // Vertical

        int vHit = 0;
        bool facingRight = ra < PI/2 || ra > 3*PI/2;
        bool facingLeft = !facingRight;

        double vx = 0, vy = 0;

        if (facingRight) {
            firstX = floor(player.x / tileSize) * tileSize + tileSize;
        } else if (facingLeft) {
            firstX = floor(player.x / tileSize) * tileSize - 0.00001;
        }

        firstY = player.y + (firstX - player.x) * tan(ra);

        nextX = firstX;
        nextY = firstY;

        if (facingRight) {
            xo =  tileSize;
        } else if (facingLeft) {
            xo = -tileSize;
        }

        yo = xo * tan(ra);

        while (nextX <= screenWidth && nextX >= 0 && nextY <= screenHeight && nextY >= 0) {
            int mapX = static_cast<int>(nextX / tileSize);
            int mapY = static_cast<int>(nextY / tileSize);

            // Debugging: print the map indices
            // printf("Checking map position -> mapX: %d, mapY: %d\n", mapX, mapY);

            // Check for a wall hit
            if (mapX < map.width && mapY < map.height && map.data[mapY][mapX]) {
                vHit = 1;
                vx = nextX;
                vy = nextY;
                // printf("Hit at -> hx: %f, hy: %f\n", hx, hy);
                break;
            } else {
                nextX += xo;
                nextY += yo;
                // Debugging: print new position after stepping
                // printf("New Position -> nextX: %f, nextY: %f\n", nextX, nextY);
            }
        }

        // Draw the line from the player to the hit position
        // if (hit) {
        //     SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set color for debugging
        //     SDL_RenderDrawLine(renderer, player.x, player.y, vx, vy);
        // }

        double hDist, vDist;

        if (hHit) {
            hDist = getDist(player.x, player.y, hx, hy);
        } else {
            hDist = 9999999;
        }

        if (vHit) {
            vDist = getDist(player.x, player.y, vx, vy);
        } else {
            vDist = 9999999;
        }

        // double hDist = getDist(player.x, player.y, hx, hy);
        // double vDist = getDist(player.x, player.y, vx, vy);

        double hitX, hitY;
        double fadeFactor;
        double maxDistance = 800.0;
        dist = std::min(hDist, vDist);
        fadeFactor = 1.0 - std::min(dist / maxDistance, 1.0);

        if (hDist < vDist) {
            hitX = hx;
            hitY = hy;
            // dist = hDist;
            // SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
            int mapX = hx / tileSize, mapY = hy / tileSize;

            if (map.data[mapY][mapX] == 1) SDL_SetRenderDrawColor(renderer, 217 * fadeFactor, 105 * fadeFactor, 98 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 2) SDL_SetRenderDrawColor(renderer, 39 * fadeFactor, 219 * fadeFactor, 92 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 3) SDL_SetRenderDrawColor(renderer, 190 * fadeFactor, 230 * fadeFactor, 80 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 4) SDL_SetRenderDrawColor(renderer, 140 * fadeFactor, 59 * fadeFactor, 184 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 5) SDL_SetRenderDrawColor(renderer, 50 * fadeFactor, 101 * fadeFactor, 209 * fadeFactor, 255);

        } else {
            hitX = vx;
            hitY = vy;
            // dist = vDist;

            int mapX = vx / tileSize, mapY = vy / tileSize;
 
            if (map.data[mapY][mapX] == 1) SDL_SetRenderDrawColor(renderer, 110 * fadeFactor, 51 * fadeFactor, 47 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 2) SDL_SetRenderDrawColor(renderer, 20 * fadeFactor, 122 * fadeFactor, 107 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 3) SDL_SetRenderDrawColor(renderer, 112 * fadeFactor, 135 * fadeFactor, 47 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 4) SDL_SetRenderDrawColor(renderer, 76 * fadeFactor, 32 * fadeFactor, 99 * fadeFactor, 255);
            if (map.data[mapY][mapX] == 5) SDL_SetRenderDrawColor(renderer, 26 * fadeFactor, 50 * fadeFactor, 102 * fadeFactor, 255);
        }

        if (debug) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Set color for debugging
            SDL_RenderDrawLine(renderer, player.x, player.y, hitX, hitY);
        }

        // fixing fisheye
        dist *= cos(ra - player.a);

        double projectedHeight = 1 * tileSize / dist * player.distFromPlane;
        double drawStart = screenHeight / 2 - projectedHeight / 2 + (player.pitch * screenHeight);
        // double drawEnd = projectedHeight;
        double drawEnd = screenHeight / 2 + projectedHeight / 2 + (player.pitch * screenHeight);

        double rectWidth = screenWidth / numRays;
        // double rectHeight = drawEnd - drawStart;

        SDL_Rect column;
        column.x = i * rectWidth;
        column.y = drawStart;
        column.w = rectWidth;
        column.h = drawEnd - drawStart;

        SDL_Rect gameFloor;
        gameFloor.x = i * rectWidth;
        gameFloor.y = drawEnd;
        gameFloor.w = rectWidth;
        gameFloor.h = screenHeight - drawEnd;

        SDL_Rect gameCeil;
        gameCeil.x = i * rectWidth;
        gameCeil.y = 0;
        gameCeil.w = rectWidth;
        gameCeil.h = drawStart;

        if (!debug) {
            SDL_RenderFillRect(renderer, &column);
            SDL_SetRenderDrawColor(renderer, 24, 24, 24, 255 * fadeFactor);
            SDL_RenderFillRect(renderer, &gameFloor);
            SDL_SetRenderDrawColor(renderer, 0, 50, 170, 255 * fadeFactor);
            SDL_RenderFillRect(renderer, &gameCeil);
        }
            



        ra += stepSize;
        if (ra >= 2*PI) ra -= 2*PI;
        if (ra <= 0) ra += 2*PI;
    }

}

double Raycaster::getDist(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
}


