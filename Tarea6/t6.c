#include <pthread.h>

#include "t6.h"

// *** Esta implementacion no funciona porque no respeta orden de llegada ***

pthread_mutex_t m= PTHREAD_MUTEX_INITIALIZER;

void ocupar() {
  pthread_mutex_lock(&m);
}

void desocupar() {
  pthread_mutex_unlock(&m);
}
