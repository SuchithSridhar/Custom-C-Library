#include "../ssvector.h"

#include <stdlib.h>
#include <stdio.h>

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


    return EXIT_SUCCESS;
}
