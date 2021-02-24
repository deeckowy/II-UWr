/* WARNING: This code is buggy! */
#include "./include/csapp.h"
#define N 4

static void *thread(void *vargp) {
  int myid = *((int *)vargp);
  printf("Hello from thread %d\n", myid);
  return NULL;
}

int main(void) {
  pthread_t tid[N];
  int i;
  int t[N];
  for (i = 0; i < N; i++)
  {
    t[i]=i;
    Pthread_create(&tid[i], NULL, thread, &t[i]);
  }
  for (i = 0; i < N; i++)
    Pthread_join(tid[i], NULL);

  return EXIT_SUCCESS;
}
