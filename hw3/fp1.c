#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int* parent, * rank;
} dj; //disjointset

int compare(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void idj(dj* ds, int n) { //init of dj
    ds->parent = (int*)malloc(n * sizeof(int));
    ds->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        ds->parent[i] = i;
        ds->rank[i] = 0;
    }
}

int findSet(dj* ds, int i) {
    if (ds->parent[i] != i)
        ds->parent[i] = findSet(ds, ds->parent[i]);
    return ds->parent[i];
}

void unionSet(dj* ds, int i, int j) {
    int ri = findSet(ds, i);
    int rj = findSet(ds, j);

    if (ri != rj) {
        if (ds->rank[ri] < ds->rank[rj])
            ds->parent[ri] = rj;
        else {
            ds->parent[rj] = ri;
            if (ds->rank[ri] == ds->rank[rj])
                ds->rank[ri]++;
        }
    }
}

int main(int argc, char* argv[]) {
    clock_t start, end;
    double tt;
    start = clock();
    if (argc != 2) {
        printf("usage: ./fp1 input_filename\n");
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");

    if (!fp) {
        printf("The input file does not exist.\n");
        return 1;
    }

    int n, e;
    fscanf(fp, "%d%d", &n, &e);

    Edge* edges = (Edge*)malloc(e * sizeof(Edge));

    for (int i = 0; i < e; i++)
        fscanf(fp, "%d%d%d", &edges[i].src, &edges[i].dest, &edges[i].weight);

    fclose(fp);

    qsort(edges, e, sizeof(Edge), compare);

    dj ds;
    idj(&ds, n);

    Edge* mst = (Edge*)malloc((n - 1) * sizeof(Edge));

    int count = 0, totalWeight = 0;

    for (int i = 0; i < e && count < n - 1; i++) {
        int uset = findSet(&ds, edges[i].src);
        int vset = findSet(&ds, edges[i].dest);

        if (uset != vset) {
            mst[count++] = edges[i];
            totalWeight += edges[i].weight;
            unionSet(&ds, uset, vset);
        }
    }

    fp = fopen("fp1_result.txt", "w");

    for (int i = 0; i < count; i++)
        fprintf(fp, "%d %d %d\n", mst[i].src, mst[i].dest, mst[i].weight);

    fprintf(fp, "%d\n", totalWeight);
    fprintf(fp, count == n - 1 ? "CONNECTED\n" : "DISCONNECTED\n");
    fclose(fp);

    printf("output written to fp1_result.txt.\n");

    free(edges);
    free(mst);
    free(ds.parent);
    free(ds.rank);
    end = clock();
    tt = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("running time: %.6f seconds\n", tt);

    return 0;
}
