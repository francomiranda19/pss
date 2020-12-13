#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "viajante.h"

int leer(int fd, void *vbuf, int n) {
    char *buf = vbuf;
    do {
        int rc = read(fd, buf, n);
        if (rc <= 0)
            return 1;
        n -= rc;
        buf += rc;
    } while (n > 0);
    return 0;
}

double viajante_par(int z[], int n, double **m, int nperm, int p) {
    int pids[p];
    int fds_aux[p];
    double min_distancia = DBL_MAX;

    for (int i = 0; i < p; i++) {
        int fds[2];
        pipe(fds);

        init_rand_seed(random());
        if ((pids[i] = fork()) == 0) {
            close(fds[0]);
            double min = viajante(z, n, m, nperm / p);
            double array[n + 2];
            array[0] = min;
            for (int j = 0; j <= n; j++) {
                array[j + 1] = z[j];
            }
            write(fds[1], &array, sizeof(array));
            exit(0);
        } else {
            close(fds[1]);
            fds_aux[i] = fds[0];
        }
    }

    for (int i = 0; i < p; i++) {
        double x[n + 2];
        leer(fds_aux[i], &x, sizeof(x));
        waitpid(pids[i], NULL, 0);
        close(fds_aux[i]);
        if (x[0] < min_distancia) {
            min_distancia = x[0];
            for (int j = 0; j <= n; j++) {
                z[j] = x[j + 1];
            }
        }
    }
    return min_distancia;
}