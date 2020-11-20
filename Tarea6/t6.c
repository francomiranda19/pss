#include <pthread.h>
#include "t6.h"

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER, m2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int visor;
int num_entrega;

void ocupar() {
  pthread_mutex_lock(&m1);
  int mi_num = num_entrega++;
  pthread_mutex_unlock(&m1);
  pthread_mutex_lock(&m2);
  while (visor != mi_num) {
    pthread_cond_wait(&cond, &m2);
  }
}

void desocupar() {
  visor++;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&m2);
}