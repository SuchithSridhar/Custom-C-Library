# A vector library

This library can be used to create a vector. This vector will maintain the size
of the internal array, resize if required, check bounds when accessing element
etc. This does not store a pointer to the element but rather copies each
element.

Internally, the vector is stored as one contiguous block of memory.

Quick example:

```c
// Its a vector of ints with an initial capacity of 1.
ssv_vector_t *vec = ssv_init(sizeof(int), 1);

int a = 10;
int b = 20;

ssv_push(vec, &a); // copy value of a into the vector.
ssv_push(vec, &b); // copy value of b into the vector.

a = 100;
b = 200;

ssv_print(vec, print_int_func);  // [10 20]
```

It is designed in a way to be used without having to use the library functions.
So, to iterate over the values you can do something like this:

```c
int *array = vec->array;
for (int i = 0; i < vec->size; i++) {
    printf("vec has %d value at %d\n", array[i], i);
}
```

But when doing this, you as the programmer, are responsible for error checking
and edge case handling.
