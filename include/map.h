#ifndef MAP_H
#define MAP_H

#include <vector>

struct Map {
    int width;
    int height;
    std::vector<std::vector<int>> data;
};

#endif