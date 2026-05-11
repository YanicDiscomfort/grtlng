#include "HashMap.h"

#include <string.h>

#include "../global.h"

#define LOAD_FACTOR 0.75

typedef struct {
    
} Key;

u32 hashString(const char* key) {
    u32 hash = 2166136261u;
    const u16 length = strlen(key);
    for (int i = 0; i < length; i++) {
        hash ^= (u8) key[i];
        hash *= 16777619;
    }
    return hash;
}