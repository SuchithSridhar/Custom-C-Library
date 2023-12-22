#ifndef SS_VECTOR_H
#define SS_VECTOR_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
    /** The internal array container. */
    void *array;
    /** The current number of elements in the vector. */
    size_t size;
    /** The max capacity of the vector at a given time. */
    size_t capacity;
    /** The size of each element in the vector. */
    size_t memb_size;
} ssv_vector_t;

/**
 * Initialize a vector for elements of size memb_size.
 * @param memb_size the size of each element.
 * @return A new vector allocated on the heap.
 */
ssv_vector_t* ssv_init(size_t memb_size, size_t init_size);

/**
 * Destroy the vector and free its memory.
 * @param vec the ssv_vector_t to destroy.
 * @return true if the operation is successful, false otherwise.
 */
bool ssv_destroy(ssv_vector_t *vec);

/**
 * Get an element from the vector at a specified index.
 * @param vec the ssv_vector_t to operate on.
 * @param index the index of the element to be retrieved.
 * @return a pointer within the vector to the element if found, NULL otherwise.
 */
void* ssv_get(ssv_vector_t *vec, size_t index);

/**
 * Push an element to the end of the vector.
 * @param vec the ssv_vector_t to operate on.
 * @param item the element to be added.
 * @return true if the operation is successful, false otherwise.
 */
bool ssv_push(ssv_vector_t *vec, void *item);

/**
 * Get an element from the end of the vector.
 * @param vec the ssv_vector_t to operate on.
 * @return a pointer within the vector to the element if exists, else NULL.
 */
void* ssv_peek(ssv_vector_t *vec);

/**
 * Pop an element from the end of the vector.
 * The returned element needs to be freed.
 * @param vec the ssv_vector_t to operate on.
 * @return a pointer to the popped element (on heap), NULL if fails.
 */
void* ssv_pop(ssv_vector_t *vec);

/**
 * Clear all the elements of the array.
 * Note that this only updated the size
 * and does not actually clear the array.
 * @param vec the ssv_vector_t to clear.
 * @return true if operation is successful, false otherwise.
 */
bool ssv_clear(ssv_vector_t *vec);

/**
 * Delete an element from the end of the vector.
 * @param vec the ssv_vector_t to operate on.
 * @return true if operation is successful, false otherwise.
 */
bool ssv_delete(ssv_vector_t *vec);

/**
 * Delete an element at the specified index.
 * @param index the index at which the element is to be deleted.
 * @param vec the ssv_vector_t to operate on.
 * @return true if operation is successful, false otherwise.
 */
bool ssv_delete_at(ssv_vector_t *vec, size_t index);

/**
 * Pop an element from the vector at a specified index.
 * @param vec the ssv_vector_t to operate on.
 * @param index the index at which the element is to be popped.
 * @return a pointer to the popped element, NULL otherwise.
 */
void* ssv_pop_at(ssv_vector_t *vec, size_t index);

/**
 * Push an element into the vector at a specified index.
 * @param vec the ssv_vector_t to operate on.
 * @param item the element to be inserted.
 * @param index the index at which the element is to be inserted.
 * @return true if the operation is successful, false otherwise.
 */
bool ssv_push_at(ssv_vector_t *vec, void *item, size_t index);

/**
 * Replace an element in the vector at a specified index with another element.
 * @param vec the ssv_vector_t to operate on.
 * @param item the new element to insert.
 * @param index the index of the element to be replaced.
 * @return true if the operation is successful, false otherwise.
 */
bool ssv_replace_at(ssv_vector_t *vec, void *item, size_t index);

/**
 * Find the index of an element in the vector.
 * @param vec the ssv_vector_t to operate on.
 * @param item the element to search for.
 * @return the index of the element if found, SIZE_MAX otherwise.
 */
size_t ssv_index_of(ssv_vector_t *vec, void *item);

/**
 * Print the elements inside the vector.
 * @param vec the ssv_vector_t to operate on.
 * @param print_elem a function pointer to print an element.
 */
void ssv_print(ssv_vector_t *vec, void (*print_elem) (void*));

/**
 * Sort the vector based on the provided compare function.
 * @param vec the ssv_vector_t to operate on.
 * @param compare a function point to a function to compare two elements.
 */
void ssv_sort(ssv_vector_t *vec, int (*compare)(const void*, const void*));

#endif
