#include "ArrayList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)
#define GROW_ARRAY(size, pointer, newCount) (realloc((pointer), (size) * (newCount)))

ArrayList *ArrayListNew(const size_t elementSize) {
    ArrayList *list = malloc(sizeof(ArrayList));

    list->capacity = 0;
    list->length = 0;

    list->elementSize = elementSize;

    list->elements = nullptr;

    return list;
}

void ArrayListFree(ArrayList *list) {
    free(list->elements);
    free(list);
}

void ArrayListAdd(ArrayList *list, const void *element) {
    if (list->length + 1 > list->capacity) {
        list->capacity = GROW_CAPACITY(list->capacity);
        void* new = GROW_ARRAY(list->elementSize, list->elements, list->capacity);
        if (new == nullptr) {
            INTERN_ERROR_LOCATION();
            fprintf(stderr, "Couldnt realloc ArrayList\n");
            exit(1);
        }
        list->elements = new;
    }


    void *dest = list->elements + list->elementSize * list->length;
    list->length++;

    memcpy(dest, element, list->elementSize);

}
void *ArrayListGet(const ArrayList *list, const u32 index) {
    if (index >= list->length) {
        INTERN_ERROR_LOCATION();
        fprintf(stderr, "Tried accessing list with length of %d at index %d\n", list->length, index);
        exit(1);
    }

    return list->elements + index * list->elementSize;
}