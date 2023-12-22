#include "../ssvector.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int test_count = 0;
int pass_count = 0;

void test_is_equal_ptr_int(void *output, void *expected) {
    if (output != NULL && *(int*)expected == *(int*)output) {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n", test_count);
        pass_count++;
    } else {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n", test_count);
        if (output != NULL) 
            printf("expected %d but got %d\n", *(int*)expected, *(int*)output);
        else
            printf("expected %d but got NULL\n", *(int*)expected);
    }

    test_count++;
}

void test_is_equal_int(int output, int expected) {
    if (output == expected) {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n", test_count);
        pass_count++;
    } else {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n", test_count);
        printf("expected %d but got %d\n", expected, output);
    }

    test_count++;
}

void test_is_not_null(void *ptr) {
    if (ptr != NULL) {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n", test_count);
        pass_count++;
    } else {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n", test_count);
        printf("expected non-NULL but recieved NULL pointer\n");
    }

    test_count++;
}

int compare_int_helper(void *a, void *b) {
    if (a == NULL || b == NULL) return -1;
    return *(int *)a - *(int *)b;
}
// Define a structure for test vectors.
typedef struct {
    int value;
} test_struct;

// Utility function to create a test vector.
ssv_vector_t* create_test_vector(size_t initial_size) {
    ssv_vector_t* vec = ssv_init(sizeof(test_struct), initial_size);
    for (size_t i = 0; i < initial_size; ++i) {
        test_struct elem = {i};  // Replace with actual data initialization.
        ssv_push(vec, &elem);
    }
    return vec;
}

// Utility function to check the contents of the vector.
void check_vector_contents(ssv_vector_t* vec, int* expected_contents, size_t expected_size) {
    assert(vec->size == expected_size);
    for (size_t i = 0; i < expected_size; ++i) {
        test_struct* elem = (test_struct*)ssv_get(vec, i);
        assert(elem && elem->value == expected_contents[i]);
    }
}

// Test function.
void test_ssv_delete_range() {
    printf("Starting ssv_delete_range tests...\n");

    // Normal case: Delete a range from the middle.
    ssv_vector_t* vec = create_test_vector(10);
    size_t deleted = ssv_delete_range(vec, 3, 7);
    assert(deleted == 4);
    int expected_contents1[] = {0, 1, 2, 7, 8, 9};
    check_vector_contents(vec, expected_contents1, 6);
    printf("=== Passed ssv_delete_range test 1 ==\n");

    // Edge case: Delete the entire range.
    deleted = ssv_delete_range(vec, 0, vec->size);
    assert(deleted == 6);
    assert(vec->size == 0);
    printf("=== Passed ssv_delete_range test 2 ==\n");

    // Error case: Invalid range (start >= end).
    deleted = ssv_delete_range(vec, 5, 5);
    assert(deleted == 0);
    printf("=== Passed ssv_delete_range test 3 ==\n");

    // Error case: start or end out of bounds.
    deleted = ssv_delete_range(vec, 0, 100);
    assert(deleted == 0);
    printf("=== Passed ssv_delete_range test 4 ==\n");

    // Normal case: Delete at the beginning.
    vec = create_test_vector(10);
    deleted = ssv_delete_range(vec, 0, 3);
    assert(deleted == 3);
    int expected_contents2[] = {3, 4, 5, 6, 7, 8, 9};
    check_vector_contents(vec, expected_contents2, 7);
    printf("=== Passed ssv_delete_range test 5 ==\n");

    // Normal case: Delete at the end.
    vec = create_test_vector(10);
    deleted = ssv_delete_range(vec, 4, 10);
    assert(deleted == 6);
    int expected_contents3[] = {0, 1, 2, 3};
    check_vector_contents(vec, expected_contents3, 4);
    printf("=== Passed ssv_delete_range test 6 ==\n");

    ssv_destroy(vec);
    printf("All tests for ssv_delete_range passed.\n");
}

int main(int argc, char *argv[]) {
    printf("\n==== Testing initialize ====\n\n");
    {
        ssv_vector_t *vec = ssv_init(sizeof(int), 1);
        test_is_not_null(vec);
    }

    printf("\n==== Testing ssv_push, ssv_get ====\n\n");
    {
        int item1, item2, item3;
        item1 = 10;
        item2 = 20;
        item3 = 30;

        ssv_vector_t *vec = ssv_init(sizeof(int), 1);
        test_is_not_null(vec);

        ssv_push(vec, &item1);
        ssv_push(vec, &item2);
        ssv_push(vec, &item3);

        test_is_equal_ptr_int(ssv_get(vec, 0), &item1);
        test_is_equal_ptr_int(ssv_get(vec, 1), &item2);
        test_is_equal_ptr_int(ssv_get(vec, 2), &item3);
    }

    test_ssv_delete_range();


    return EXIT_SUCCESS;
}
