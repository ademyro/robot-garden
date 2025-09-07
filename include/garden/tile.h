#ifndef RG_TILE_H
#define RG_TILE_H

/**
 * A specific kind of tile in the garden.
 */
typedef enum {
  TILE_DIRT,
  TILE_GRASS
} Tile;

/**
 * Allocates a 16 by 16 matrix of tiles.  
 *
 * The matrix is not 0-initialized.
 *
 * Ownership of the memory allocated by this function falls on the caller.
 */
Tile **newTileGrid();

#endif
