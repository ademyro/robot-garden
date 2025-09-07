#include "garden/tile.h"

#include <stdlib.h>

/**
  * The number of tiles in each row of the tile grid.
  */
#define TILE_ROW_SIZE 16

Tile **newTileGrid() {
  Tile **grid = malloc(TILE_ROW_SIZE * sizeof(Tile *));
  
  for (int i = 0; i < TILE_ROW_SIZE; i++) {
    grid[i] = malloc(TILE_ROW_SIZE * sizeof(Tile));
  }

  return grid;
}
