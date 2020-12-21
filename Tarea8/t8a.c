#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <setjmp.h>

#include "viajante.h"

volatile int flag;

void ring() {
  flag = 0;
}

double viajante(int z[], int n, double **m, int nperm) {
  double min = DBL_MAX;
  void (*handler)() = signal(SIGINT, ring);
  flag = 1;

  for (int i = 1; i <= nperm && flag; i++) {
    int x[n + 1];
    gen_ruta_alea(x, n);
    double d = dist(x, n, m);
    if (d < min) {
      min = d;
      for (int j = 0; j <= n; j++)
        z[j] = x[j];
    } 
  }

  signal(SIGINT, handler);
  return min;
}