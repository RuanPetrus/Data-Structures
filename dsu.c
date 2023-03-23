#include <stdio.h>
#include <assert.h>


#define DSU_MAX_SIZE 10000

typedef struct {
    int sizes[DSU_MAX_SIZE];
    int parents[DSU_MAX_SIZE];
} Dsu;

void dsu_make_set(Dsu *dsu, int element)
{
    // Already in dsu
    if (dsu->sizes[element] > 0) {
        return;
    }

    dsu->parents[element] = element;
    dsu->sizes[element] = 1;
}

int dsu_find(Dsu *dsu, int element)
{
    // Not in dsu
    if (dsu->sizes[element] <= 0) {
        return -1;
    }

    if (dsu->parents[element] == element) {
        return element;
    }
    return dsu->parents[element] = dsu_find(dsu, dsu->parents[element]);
}

void dsu_union(Dsu *dsu, int a, int b)
{
    a = dsu_find(dsu, a);
    b = dsu_find(dsu, b);

    // a and b in the same set
    if (a == b) {
        return;
    }

    if (dsu->sizes[a] < dsu->sizes[b]) {
        int aux = a;
        a = b;
        b = aux;
    }

    dsu->parents[b] = a;
    dsu->sizes[a] += dsu->sizes[b];
}

int main()
{
    Dsu dsu = {0};
    dsu_make_set(&dsu, 0);
    dsu_make_set(&dsu, 1);
    dsu_make_set(&dsu, 2);
    dsu_make_set(&dsu, 3);
    // DSU = {0}, {1}, {2}, {3}

    dsu_union(&dsu, 0, 1);
    dsu_union(&dsu, 2, 3);
    // DSU = {0,1}, {2,3}

    assert(dsu_find(&dsu, 0) == dsu_find(&dsu, 1));
    assert(dsu_find(&dsu, 2) == dsu_find(&dsu, 3));
    assert(dsu_find(&dsu, 0) != dsu_find(&dsu, 2));

    dsu_union(&dsu, 1, 2);
    // DSU = {0,1,2,3}
    assert(dsu_find(&dsu, 0) == dsu_find(&dsu, 2));

    return 0;
}
