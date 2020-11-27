#include <pthread.h>
#include "t6.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int visor, num_entrega;

void ocupar() {
  pthread_mutex_lock(&mutex);
  int mi_num = num_entrega++;
  while (visor != mi_num) {
    pthread_cond_wait(&cond, &mutex);
  }
  pthread_mutex_unlock(&mutex);
}

void desocupar() {
  pthread_mutex_lock(&mutex);
  visor++;
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
}