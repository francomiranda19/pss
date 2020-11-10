#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "maleta.h"

// Se crea la estructura
typedef struct {
    double *w;
    double *v;
    int *z;
    int n;
    double maxW;
    int k;
    double res;
} Args;

// Función del thread
void *thread_function(void *p) {
    // Se rescatan los parámetros
    Args *args = (Args *) p;
    double *w = args -> w;
    double *v = args -> v;
    int *z = args -> z;
    int n = args -> n;
    double maxW = args -> maxW;
    int k = args -> k;
    // Llenar maleta
    args -> res = llenarMaletaSec(w, v, z, n, maxW, k);
    return NULL;
}

// Función principal
double llenarMaletaPar(double w[], double v[], int z[], int n, double maxW, int k) {
    // 8 cores
    pthread_t pid[8];
    Args args[8];
    // Creación de los threads
    for (int i = 0; i < 8; i++) {
        args[i].w = w;
        args[i].v = v;
        args[i].z = malloc(n * sizeof(int));
        args[i].n = n;
        args[i].maxW = maxW;
        args[i].k = k / 8;
        pthread_create(&pid[i], NULL, thread_function, &args[i]);
    }
    // Esperar
    double best = -1;
    for (int i = 0; i < 8; i++) {
        pthread_join(pid[i], NULL);
        if (args[i].res > best) {
            best = args[i].res;
            for (int j = 0; j < n; j++) {
                z[j] = args[i].z[j];
            }
        }
        free(args[i].z);
    }
    return best;
}