#pragma once

#include <stddef.h>

#include "../global.h"
#include "ArrayList.h"

typedef struct {
    u16 capacity, count;
    u16 valueSize;
    void *values;
} HashMap;

void HashMapInit(HashMap *map, size_t valueSize);
void HashMapFree(HashMap *map);

bool HashMapSet(HashMap *map, char *key, const void *value);
bool HashMapGet(const HashMap *map, const char *key, void *value);
bool HashMapHas(HashMap *map, char *key);
ArrayList *HashMapAll(HashMap *map);