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

/* Esta metodología podría no ser correcta porque se puede ingresar Control-C
en el momento en que el programa está copiando el arreglo z correspondiente,
o incluso no alcanzó a llegar a ese punto, y por lo tanto, al gatillarse la señal,
se vuelve al punto de retorno para longjmp, entregando el mínimo calculado
hasta el momento, pero el arreglo z pudiendo ser incorrecto ya que no se había
terminado de copiar (o ni siquiera empezó a hacerlo) */

static jmp_buf ring;

void end() {
  longjmp(ring, 1);
}

double viajante(int z[], int n, double **m, int nperm) {
  double min = DBL_MAX;
  void (*handler)() = signal(SIGINT, end);

  if (setjmp(ring) == 0) { // try
    for (int i = 1; i <= nperm; i++) {
    int x[n + 1];
    gen_ruta_alea(x, n);
    double d = dist(x, n, m);
    if (d < min) {
      min = d;
      for (int j = 0; j <= n; j++)
        z[j] = x[j];
      } 
    }
  }
  else { // catch
  
  }

  signal(SIGINT, handler);
  return min;
}