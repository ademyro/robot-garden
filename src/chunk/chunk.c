#include <stdlib.h>

#include "chunk/chunk.h"
#include "garden/tile.h"

Chunk *newChunk(int x, int y) {
  Chunk *chunk = malloc(sizeof(*chunk));
  Tile **grid = newTileGrid();
  
  chunk->grid = grid;

  chunk->x = y;
  chunk->y = y;

  return chunk;
}
