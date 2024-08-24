#ifndef PLAYER_H
#define PLAYER_H

struct Player {
    double x, y; // Player position
    double dx, dy;
    double a;
    double rotationSpeed;
    double pitch;
    // double dirX, dirY; // Direction vector
    // double planeX, planeY; // Camera plane
    double speed;
    int fov;
    double distFromPlane;
    double offsetX, offsetY;
};

#endif
