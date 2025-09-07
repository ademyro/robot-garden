#include "chunk/table.h"
#include "log/log.h"
#include <stdlib.h>

static inline void tableResize(Table *table) {
  u32 oldCap = table->cap;
  Entry *oldEntries = table->entries;

  table->cap = oldCap << 1;
  table->mask = table->cap - 1;
  table->size = 0;
  table->entries = calloc(table->cap, sizeof(Entry));

  for (int i = 0; i < oldCap; i++) {
    if (oldEntries[i].isOccupied) {
      tableAddChunk(table, oldEntries[i].chunk);
    }
  }

  free(oldEntries);
}

static inline void freeChunks(Table *table) {
  for (int i = 0; i < table->cap; i++) {
    if (table->entries[i].isOccupied) {
      free(table->entries[i].chunk);
    }
  }
}

Table *newTable() {
  Table *table = malloc(sizeof(*table));
  Entry *entries = calloc(DEFAULT_TABLE_CAP, sizeof(Entry));

  table->entries = entries;
  table->cap = DEFAULT_TABLE_CAP;
  table->mask = table->cap - 1;
  table->size = 0;

  return table;
}

u32 hashChunk(Table *table, i16 x, i16 y) {
  return (((u32)x * 73856093u) ^ ((u32)y * 19349663u)) & table->mask;
}

void tableAddChunk(Table *table, Chunk *chunk) {
  if (table->size >= ((table->cap << 1) + table->cap) >> 3) {
    tableResize(table); 
  }

  u32 index = hashChunk(table, chunk->x, chunk->y); 
  u32 begin = index;
  Entry *entry = &table->entries[index];

  while (entry->isOccupied) {
    index = (index + 1) & table->mask;

    if (index == begin) {
      debugLog(
        "The chunk hash table is full.  The chunk at (%d, %d) was not added.",
        chunk->x, chunk->y
      );

      return;
    }
  }

  entry->x = chunk->x;
  entry->y = chunk->y;
  entry->chunk = chunk;
  entry->isOccupied = true;
}

Chunk *tableFindChunk(Table *table, i16 x, i16 y) {
  u32 index = hashChunk(table, x, y); 
  const u32 begin = index;
  Entry *entry = &table->entries[index];

  while (entry->isOccupied && (entry->x != x || entry->y != y)) {
    index = (index + 1) & table->mask;
    entry = &table->entries[index];

    if (index == begin) {
      return NULL;
    }
  }

  return entry->chunk;
}

void tableFree(Table *table) {
  freeChunks(table);

  free(table->entries);
  table->cap = 0;
  table->mask = 0;
  table->size = 0;
}
