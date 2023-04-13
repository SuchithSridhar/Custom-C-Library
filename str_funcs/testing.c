#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "str_funcs.h"

int test_count = 1;

void test_strings_equal(char *out, char *exp) {

    if (strcmp(out, exp) == 0) {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n", test_count);
    } else {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n", test_count);
        printf("'%s' expected but recieved '%s'\n", exp, out);
    }

    test_count++;
}

void test_true(bool value) {

    if (value) {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n", test_count);
    } else {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n", test_count);
    }

    test_count++;
}

void test_ints_equal(int out, int exp) {
    if (out == exp) {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;32mPassed\033[0m\n", test_count);
    } else {
        printf("==== \033[0;33mTEST %02d\033[0m ==== : \033[0;31mFailed\033[0m\n", test_count);
        printf("'%d' expected but recieved '%d'\n", exp, out);
    }

    test_count++;
}


int main() {
    bool bool_output;
    char *input;
    char *output;
    char *expected;

    printf("\n==== Testing trim_whitespace ====\n\n");

    input = "  lorem    ipsum  ld \n\n";
    output = trim_whitespace(input);
    expected = "lorem    ipsum  ld";
    test_strings_equal(output, expected);

    input = "    hello world";
    output = trim_whitespace(input);
    expected = "hello world";
    test_strings_equal(output, expected);

    input = "hello world    \n\t";
    output = trim_whitespace(input);
    expected = "hello world";
    test_strings_equal(output, expected);

    input = "    \n\n \t\t   ";
    output = trim_whitespace(input);
    expected = "";
    test_strings_equal(output, expected);

    input = "";
    output = trim_whitespace(input);
    expected = "";
    test_strings_equal(output, expected);

    printf("\n==== Testing is_substring ====\n\n");

    input = "hello world";
    bool_output = is_substring(input, "llo");
    test_true(bool_output);

    input = "hello world";
    bool_output = is_substring(input, "lol");
    test_true(!bool_output);

    input = "abc";
    bool_output = is_substring(input, "abc");
    test_true(bool_output);

    input = "";
    bool_output = is_substring(input, "abc");
    test_true(!bool_output);

    input = "";
    bool_output = is_substring(input, "");
    test_true(bool_output);

    input = "adsf";
    bool_output = is_substring(input, "");
    test_true(bool_output);

    input = "oodoodooo";
    bool_output = is_substring(input, "dooo");
    test_true(bool_output);

    printf("\n==== Testing index_of ====\n\n");

    {
        char *input, *substring;
        int start, output, expected;

        // Substring present at the beginning
        input = "hello world";
        substring = "hello";
        start = 0;
        expected = 0;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present in the middle
        input = "hello world";
        substring = "lo w";
        start = 0;
        expected = 3;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present at the end
        input = "hello world";
        substring = "world";
        start = 0;
        expected = 6;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring not present
        input = "hello world";
        substring = "notfound";
        start = 0;
        expected = -1;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present but search starts after it
        input = "hello world";
        substring = "hello";
        start = 1;
        expected = -1;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Empty substring
        input = "hello world";
        substring = "";
        start = 0;
        expected = 0;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Empty string
        input = "";
        substring = "hello";
        start = 0;
        expected = -1;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);
    }


    printf("\n==== Testing index_of with varying start indices ====\n\n");

    {
        int start, output, expected;
        char *input, *substring;

        // Substring present at the beginning, start index in the middle
        input = "hello world";
        substring = "hello";
        start = 3;
        expected = -1;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present in the middle, start index before it
        input = "hello world";
        substring = "lo w";
        start = 1;
        expected = 3;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present in the middle, start index at the beginning of it
        input = "hello world";
        substring = "lo w";
        start = 3;
        expected = 3;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present in the middle, start index after it
        input = "hello world";
        substring = "lo w";
        start = 5;
        expected = -1;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present at the end, start index in the middle
        input = "hello world";
        substring = "world";
        start = 4;
        expected = 6;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present multiple times, start index before first occurrence
        input = "hello world world";
        substring = "world";
        start = 0;
        expected = 6;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present multiple times, start index between first and second occurrence
        input = "hello world world";
        substring = "world";
        start = 7;
        expected = 12;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);

        // Substring present multiple times, start index after second occurrence
        input = "hello world world";
        substring = "world";
        start = 13;
        expected = -1;
        output = index_of(input, substring, start);
        test_ints_equal(output, expected);
    }

    printf("\n==== Testing get_substring ====\n\n");

    // Reverse a string
    input = "hello world";
    output = get_substring(input, -1, 0, -1);
    expected = "dlrow olleh";
    test_strings_equal(output, expected);

    // Forward direction substring
    input = "helloworld";
    output = get_substring(input, 2, 7, 1);
    expected = "llowor";
    test_strings_equal(output, expected);

    // Backward direction substring
    input = "helloworld";
    output = get_substring(input, 7, 2, -1);
    expected = "rowoll";
    test_strings_equal(output, expected);

    // Slice with negative indices
    input = "helloworld";
    output = get_substring(input, -6, -3, 1);
    expected = "owor";
    test_strings_equal(output, expected);

    // Slice with negative indices reverse step
    input = "helloworld";
    output = get_substring(input, -3, -6, -1);
    expected = "rowo";
    test_strings_equal(output, expected);

    // Slice with higher step multiple : 3
    input = "helloworld";
    output = get_substring(input, 0, -1, 3);
    expected = "hlod";
    test_strings_equal(output, expected);

    // Slice with higher step multiple : 2
    input = "helloworld";
    output = get_substring(input, 0, -1, 2);
    expected = "hlool";
    test_strings_equal(output, expected);

    // Slice with higher step multiple : 3
    input = "helloworld";
    output = get_substring(input, -1, 0, -3);
    expected = "dolh";
    test_strings_equal(output, expected);

    // Slice with higher step multiple : 2
    input = "helloworld";
    output = get_substring(input, -1, 0, -2);
    expected = "drwle";
    test_strings_equal(output, expected);

    printf("\n==== Testing to_uppercase ====\n\n");

    // Convert all characters to uppercase
    input = "helloworld";
    output = to_uppercase(input);
    expected = "HELLOWORLD";
    test_strings_equal(output, expected);

    // Convert only lowercase characters to uppercase
    input = " h *8e  ]13057o W '/.;' OrLd";
    output = to_uppercase(input);
    expected = " H *8E  ]13057O W '/.;' ORLD";
    test_strings_equal(output, expected);

    printf("\n==== Testing to_lowercase ====\n\n");

    // Convert all characters to lowercase
    input = "HELLOWORLD";
    output = to_lowercase(input);
    expected = "helloworld";
    test_strings_equal(output, expected);

    // Convert only uppercase characters to lowercase
    input = " h *8e  ]13057o W '/.;' OrLd";
    output = to_lowercase(input);
    expected = " h *8e  ]13057o w '/.;' orld";
    test_strings_equal(output, expected);

    return 0;
}
