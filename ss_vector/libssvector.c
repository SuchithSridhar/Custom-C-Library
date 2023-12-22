#include "ssvector.h"
#include "internal_ssvector.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

ssv_vector_t* ssv_init(size_t memb_size, size_t init_size) {
    ssv_vector_t *vec = malloc(sizeof(ssv_vector_t));

    if (vec == NULL) return NULL;

    vec->size = 0;
    vec->memb_size = memb_size;
    vec->capacity = init_size;

    vec->array = malloc(memb_size * init_size);
    if (vec->array == NULL) {
        free(vec);
        return NULL;
    }

    return vec;
}

bool ssv_destroy(ssv_vector_t *vec) {
    if (vec == NULL) return true;

    free(vec->array);
    free(vec);

    return true;
}

void* ssv_get(ssv_vector_t *vec, size_t index) {
    if (vec && index < vec->size) {
        return (void*)((char*)vec->array + (index * vec->memb_size));
    }

    return NULL;   
}

void* ssv_peek(ssv_vector_t *vec) {
    if (vec && vec->size > 0) {
        return (void*)((char*)vec->array + ((vec->size-1) * vec->memb_size));
    }

    return NULL;   
}

bool ssv_push(ssv_vector_t *vec, void *item) {
    if (vec == NULL || item == NULL) return false;
    bool success = true;
    if (vec->size == vec->capacity) {
        success = _internal_ssv_resize(vec);
        if (!success) return false;
    }

    void *dest = (char *) vec->array + (vec->memb_size * vec->size);
    memcpy(dest, item, vec->memb_size);
    vec->size++;

    return true;
}

void* ssv_pop(ssv_vector_t *vec) {
    if (vec == NULL || vec->size == 0) return NULL;

    void *src = (char *) vec->array + (vec->memb_size * (vec->size - 1));
    void *elem = malloc(vec->memb_size);

    memcpy(elem, src, vec->memb_size);
    vec->size--;
    return elem;
}

bool ssv_clear(ssv_vector_t *vec) {
    if (vec == NULL) return false;
    vec->size = 0;
    return true;
}

bool ssv_delete(ssv_vector_t *vec) {
    if (vec == NULL || vec->size == 0) return false;
    vec->size--;
    return true;
}

bool ssv_delete_at(ssv_vector_t *vec, size_t index) {
    if (vec == NULL || vec->size == 0 || index >= vec->size) {
        return false;
    }

    void *to_delete = (char*)vec->array + (index * vec->memb_size);

    if (index < vec->size - 1) {
        void *start = (char*)to_delete + vec->memb_size;
        size_t bytes_to_move = (vec->size - index - 1) * vec->memb_size;
        memmove(to_delete, start, bytes_to_move);
    }
    vec->size--;

    return true;
}

void* ssv_pop_at(ssv_vector_t *vec, size_t index) {
    if (vec == NULL || vec->size == 0 || index >= vec->size) {
        return NULL;
    }

    void *elem = malloc(vec->memb_size);
    void *to_delete = (char*)vec->array + (index * vec->memb_size);

    memcpy(elem, to_delete, vec->memb_size);

    if (index < vec->size - 1) {
        void *start = (char*)to_delete + vec->memb_size;
        size_t bytes_to_move = (vec->size - index - 1) * vec->memb_size;
        memmove(to_delete, start, bytes_to_move);
    }
    vec->size--;
    return elem;
}

bool ssv_push_at(ssv_vector_t *vec, void *item, size_t index) {
    if (!vec || index > vec->size) {
        return false;
    }

    if (vec->size == vec->capacity) {
        bool success = _internal_ssv_resize(vec);
        if (!success) return false;
    }

    if (index < vec->size) {
        void *start = (char*)vec->array + (index * vec->memb_size);
        size_t bytes_to_move = (vec->size - index) * vec->memb_size;
        memmove((char*)start + vec->memb_size, start, bytes_to_move);
    }

    void *destination = (char*)vec->array + (index * vec->memb_size);
    memcpy(destination, item, vec->memb_size);

    vec->size++;

    return true;
}

bool ssv_replace_at(ssv_vector_t *vec, void *item, size_t index) {
    if (!vec || index > vec->size) {
        return false;
    }

    void *start = (char*)vec->array + (index * vec->memb_size);
    memcpy(start, item, vec->memb_size);
    return true;
}

size_t ssv_index_of(ssv_vector_t *vec, void *item) {
    if (vec == NULL || item == NULL) return SIZE_MAX;

    void *elem;
    for (size_t i = 0; i < vec->size; i++) {
        elem = (char *) vec->array + (vec->memb_size * i);
        if (memcmp(item, elem, vec->memb_size) == 0) {
            return i;
        }
    }
    return SIZE_MAX;
}

void ssv_print(ssv_vector_t *vec, void (*print_elem) (void*)) {
    printf("[");
    for (size_t i = 0; i < vec->size - 1; i++) {
        print_elem((char*) vec->array + (i * vec->memb_size));
        printf(", ");
    }
    print_elem((char*) vec->array + ((vec->size - 1) * vec->memb_size));
    printf("]\n");
}

void ssv_sort(ssv_vector_t *vec, int (*compare)(const void*, const void*)) {
    qsort(vec->array, vec->memb_size, vec->size, compare);
}

bool _internal_ssv_resize(ssv_vector_t *vec) {
    if (vec == NULL) return false;
    size_t new_size = vec->capacity * GROWTH_FACTOR;

    // Something went wrong. Overflow?
    if (new_size < vec->capacity) return false;

    void *new_array = realloc(vec->array, new_size * vec->memb_size);
    if (new_array == NULL) return false;

    vec->array = new_array;
    vec->capacity = new_size;
    return true;
}

