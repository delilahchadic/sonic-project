#ifndef WORLD_H
#define WORLD_H
#define TILE_SIZE 40
#define MAP_ROWS 11 // 11 * 40 = 440 pixels (perfect for a 450 window)
#define MAP_COLS 20

#include "raylib.h"

typedef struct {
    int* data;      // The actual tiles (the 1s and 0s)
    int columns;    // How wide is it?
    int rows;       // How tall is it?
    int tileSize;   // How big is each square?
} World;

World get_default_world();
int World_GetTile(World* w, int x, int y);
void Draw_World(World* w);
#endif