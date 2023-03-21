/*
This is a educational implementation of a dinamic array. This is not meant to use in production
*/

#include "stdio.h"
#include "assert.h"
#include "stdlib.h"

typedef struct
{
    size_t size;
    size_t capacity;
    int *elements;
} Da;

Da da_init(size_t size)
{
    size_t capacity = (size > 0 ? size : 1);
    int *data = (int*) malloc(capacity * sizeof(int));
    for (size_t i = 0; i < capacity; i++) {
        data[i] = 0;
    }

    return (Da) {
        .size = size,
        .capacity = capacity,
        .elements = data,
    };
}

void da_append(Da *da, int n)
{
    // If we don't have capacity, we double
    if (da->size + 1 > da->capacity) {
        size_t new_capacity = da->capacity * 2;
        int *new_data = (int*) malloc(new_capacity * sizeof(int));

        for (size_t i = 0; i < da->size; i++) {
            new_data[i] = da->elements[i];
        }
        free(da->elements);
        da->elements = new_data;
        da->capacity *= 2;
    }
    da->elements[da->size++] = n;
}

int da_get(Da *da, size_t i)
{
    assert(i < da->size);
    return da->elements[i];
}

void da_set(Da *da, size_t i, int n)
{
    assert(i < da->size);
    da->elements[i] = n;
}

int da_delete(Da *da, size_t i)
{
    assert(i < da->size);
    int element = da->elements[i];
    for (; i + 1 < da->size; i++) {
        da->elements[i] = da->elements[i + 1];
    }
    da->size--;

    // Shrink if the size is to low
    if (da->size < da->capacity/4) {
        int *new_data = (int *) malloc(da->capacity/2 * sizeof(int));

        for (i = 0; i < da->size; i++) {
            new_data[i] = da->elements[i];
        }

        free(da->elements);
        da->elements = new_data;
        da->capacity /= 2;
    }

    return element;
}

int da_pop(Da *da)
{
    return da_delete(da, da->size - 1);
}

// i = 2, n = 5
// 0 1 2 3
// a b c d
// a b c d d

void da_insert(Da *da, size_t index, int n)
{
    assert(index < da->size);
    da_append(da, 0);

    for (int i = da->size - 2; i >= (int) index; i--) {
        da->elements[i + 1] = da->elements[i];
    }
    da->elements[index] = n;
}


#define N 100
int main(void)
{
    Da da = da_init(N);
    for (int i = 0; i < N; i++) {
        da_set(&da, i, i);
    }
    for (int i = N - 1; i >= 0; i--) {
        assert(i == da_pop(&da));
    }
    for (int i = 0; i < N; i++) {
        da_append(&da, i);
    }
    da_append(&da, N);
    assert(N == da_get(&da, N));

    assert(0 == da_delete(&da, 0));
    assert(1 == da_get(&da, 0));

    da_insert(&da, 0, 0);
    assert(0 == da_get(&da, 0));
    assert(1 == da_get(&da, 1));
    assert(N == da_get(&da, N));

    printf("%zu\n", da.size);
    free(da.elements);
    return 0;
}
