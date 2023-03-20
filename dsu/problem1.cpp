/*
This problem is taken from https://www.codechef.com/problems/ABROADS, is called ancient berland roads;
*/

#include <bits/stdc++.h>

using namespace std;

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


int main() {
    // Reading input
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> population(n);
    vector<pair<int, int>> roads(m);

    for (int i = 0; i < n; i++) {
        cin >> population[i];
    }

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        roads[i] = {a - 1, b - 1};
    }

    // reading query to answer backwards
    vector<bool> deleted_roads(m, false);
    vector<tuple<char, int, int>> queries;

    while(q--) {
        char t;
        cin >> t;
        if (t == 'D') {
            int i; cin >> i;
            deleted_roads[i - 1] = true;
            queries.emplace_back(t, i - 1, 0);
        } else {
            int i, x; cin >> i >> x;
            queries.emplace_back(t, i - 1, population[i - 1]);
            population[i - 1] = x;
        }
    }

    Dsu dsu = {0};
    multiset<int> values;
    vector<int> region_population = population;

    for (int i = 0; i < n; i++) {
        dsu_make_set(&dsu, i);
        values.insert(population[i]);
    }

    auto merge_region = [&region_population, &dsu, &values] (int a, int b) {
        if (dsu_find(&dsu, a) == dsu_find(&dsu, b)) {
            return;
        }
        int population_a =  region_population[dsu_find(&dsu, a)];
        int population_b =  region_population[dsu_find(&dsu, b)];
        values.erase(values.find(population_a));
        values.erase(values.find(population_b));

        dsu_union(&dsu, a, b);
        region_population[dsu_find(&dsu, a)] = population_a + population_b;
        values.insert(population_a + population_b);

        return;
    };

    for (int i = 0; i < m; i++) {
        if (deleted_roads[i])
            continue;

        auto p = roads[i];

        merge_region(p.first, p.second);
    }

    vector<int> answer;
    // Reading query backwards
    for (auto q = queries.rbegin(); q != queries.rend(); q++) {
        // Bigger element
        if (!values.empty()) {
            int max_element = *(values.rbegin());
            answer.push_back(max_element);
        }
        char t;
        int i, x;
        tie(t, i, x) = *q;

        if (t == 'D') {
            auto p = roads[i];
            merge_region(p.first, p.second);
        }
        else {
            values.erase(values.find(region_population[dsu_find(&dsu, i)]));
            region_population[dsu_find(&dsu, i)] += (x - population[i]);
            values.insert(region_population[dsu_find(&dsu, i)]);
            population[i] = x;
        }
    }

    // Priting anwser
    for (auto i = answer.rbegin(); i != answer.rend(); i++) {
        cout << *i << endl;
    }

    return 0;
}
