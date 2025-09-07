#ifndef RG_TABLE_H
#define RG_TABLE_H

#include "common/common.h"
#include "chunk/chunk.h"

/**
 * The default capacity chosen for the table of chunks.
 */
#define DEFAULT_TABLE_CAP 32

/**
 * An entry in the `Table` of `Chunks`.
 */
typedef struct {
  /**
   * The chunk’s normalized coordinates, used for comparison in case of 
   * hash collisions.
   */
  i16 x, y; 

  /**
   * The chunk being stored.
   */
  Chunk *chunk;

  /**
   * Whether this entry is occupied or not.
   */
  bool isOccupied;
} Entry;

/**
 * The table of chunks.
 */
typedef struct {
  /**
   * The array of chunk entries.
   */
  Entry *entries;

  /**
   * The table’s maximum capacity.
   *
   * This setting does not reflect the Table’s load factor—simply how many 
   * entries are allocated at present.
   *
   * The table has a load factor of 3/4, so once that threshold is reached,
   * the table’s maximum capacity is doubled and all elements are re-inserted.
   */
  u32 cap;

  /**
   * The mask—exactly `cap - 1` for fast lookup when doing linear probing.
   */
  u32 mask;

  /**
   * The table’s size—i.e. how many entries are occupied at present.
   */
  u32 size;
} Table;

/**
 * Allocates a new table with a maximum capacity of 32 entries.
 * All entires are free—none of them are occupied.
 */
Table *newTable();

/**
 * Hashes a chunk’s coordinates and returns an unsigned integer hash.
 *
 * The given table is used as a mask so that the hash fits within the table’s size.
 */
u32 hashChunk(Table *table, i16 x, i16 y);

/**
 * Adds the given entry to the `Table` of `Chunks`.
 *
 * This function does not check for duplicates.  If an already-existing Chunk 
 * is given to this function, it will simply be treated as if it were a 
 * hash collision.
 */
void tableAddChunk(Table *table, Chunk *chunk);

/**
 * Tries to find the `Chunk` in the given `Table` if it exists.
 *
 * Returns `NULL` otherwise.
 */
Chunk *tableFindChunk(Table *table, i16 x, i16 y);

/**
 * Frees the contents of the table.
 */
void tableFree(Table *table);

#endif
