#include "ArenaAllocator.h"

#include <stdio.h>
#include <stdlib.h>

#ifndef  ARENA_ALLOC_SIZE
 #define ARENA_ALLOC_SIZE 0x1000
#endif
/**
 * @brief Create a new Arena.
 *
 * @param size The capacity in bytes of the arena and all of its children
 *
 * @return Pointer to the new Arena
 */
ArenaAllocator *ArenaNewSize(const u16 size) {
    ArenaAllocator *arena = malloc(sizeof(ArenaAllocator) + size);

    if (arena == nullptr) {
        INTERN_ERROR_LOCATION();
        fprintf(stderr, "Failed to allocate new Arena.\n");
        exit(1);
    }

    arena->capacity = size;
    arena->size = 0;

    arena->next = nullptr;

    for (u64 i = 0; i < size; i++) {
        arena->data[i] = 0;
    }

    return arena;
}

/**
 * @brief Create a new Arena.
 *
 * @return Pointer to the new Arena
 */

ArenaAllocator *ArenaNew() {
    return ArenaNewSize(ARENA_ALLOC_SIZE);
}

/**
 * @brief Free an Arena and all of its children.
 *
 * @param arena pointer to the Arena
 */
void ArenaFree(ArenaAllocator *arena) {
    if (arena->next != nullptr) ArenaFree(arena->next);
    free(arena);
}

/*
 * Returns a pointer for an object of a given size in a given Arena.
 * When the space in the given Arena is insufficient for the given size, it will prompt the next Arena to
 * Allocate the object.
 */

/**
 * @brief Allocate some space in the given Arena or any of its children.
 *
 * @param arena pointer to the Arena
 * @param size size
 *
 * @return Pointer to the newly allocated space
 */
void *ArenaAlloc(ArenaAllocator *arena, const size_t size) {
    if (size > arena->capacity) {
        INTERN_ERROR_LOCATION();
        fprintf(stderr, "Internal error: Allocated space bigger than Arena Allocator size.\n");
        exit(1);
    }
    if (arena->size + size > arena->capacity) {
        if (arena->next == nullptr) {
            arena->next = ArenaNewSize(arena->capacity);
        }
        return ArenaAlloc(arena->next, size);
    }

    void *data = &arena->data[arena->size];
    arena->size += (int) size;
    return data;
}