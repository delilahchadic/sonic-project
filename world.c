#include "world.h"


int worldMap[MAP_ROWS][MAP_COLS] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 0 (Top)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 1
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 2
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 3
    {0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 4 (Floating platform)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 5
    {0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0}, // Row 6 (Floating platform)
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 7
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 8
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, // Row 9
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}  // Row 10 (THE FLOOR)
};

World get_default_world(){
  World world = {0};
  world.data = (int*) worldMap;
  world.columns = MAP_COLS;
  world.rows = MAP_ROWS;
  world.tileSize = TILE_SIZE;
  return world;
}

int World_GetTile(World* w, int x, int y) {
    // 1. Safety first: check bounds so the game doesn't crash
    if (x < 0 || x >= w->columns || y < 0 || y >= w->rows) return 0;

    // 2. Return the math
    return w->data[y * w->columns + x];
}

void Draw_World(World* world){
  for (int row = 0; row < world->rows; row++) {
    for (int col = 0; col < world->columns; col++) {
        // If the map has a 1 at this spot, draw a rectangle
        if (World_GetTile(world, col,row) == 1) {
            DrawRectangle(col * world->tileSize, row * world->tileSize, world->tileSize - 1, world->tileSize - 1, GRAY);
        }
    }
  }
}