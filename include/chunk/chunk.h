#ifndef RG_CHUNK_H
#define RG_CHUNK_H

#include "garden/tile.h"
#include "util/maybe.h"

/**
 * The chunk’s size, i.e. how many tiles per column a single chunk has.
 *
 * In Robot Garden, Chunks are 16 by 16.
 */
#define CHUNK_SIZE 16

/**
 * A 16 by 16 area of the garden with its own set of tiles.
 */
typedef struct {
  /**
   * The chunk’s coordinates, normalized—divided by 16.
   *
   * For example—if a Chunk begins at (x: 64, y: 32), its normalized coordinates
   * will be (x: 4, y: 2)
   */
  i16 x, y;

  /**
   * A heap-allocated 16 by 16 matrix of tiles owned by the chunk.
   */
  Tile **grid;
} Chunk;

/**
 * Allocates a new Chunk with the given coordinates.
 *
 * The tiles are left as garbage values—they are not 0-initialized.
 *
 * The ownership of the memory this function allocates falls on the caller.
 */
Chunk *newChunk(int x, int y);

#endif
