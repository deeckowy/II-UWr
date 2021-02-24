#include "./include/csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

#define N 100
#define M 100

static struct {
  /* TODO: Put semaphores and shared variables here. */
  sem_t lock;
  sem_t empty;
  sem_t full;
  int cauldron;
} *shared = NULL;


static void savage(void) {
  for (;;) {
    /* TODO Take a meal or wait for it to be prepared. */
    Sem_wait(&shared->lock);
    if(shared->cauldron==0)
    {
      Sem_post(&shared->empty);
      Sem_post(&shared->full);
    }
    shared->cauldron--;
    printf("[%d] is eating now!\n",getpid());
    Sem_post(&shared->lock);
    /* Sleep and digest. */
    usleep(rand() % 1000 + 1000);
  }
  exit(EXIT_SUCCESS);
}

static void cook(void) {
  for (;;) {
    /* TODO Cook is asleep as long as there are meals.
     * If woken up they cook exactly M meals. */
    Sem_wait(&shared->empty);
    shared->cauldron=M;
    printf("[%d] is cooking now!\n",getpid());
    Sem_post(&shared->full);
  }
}

/* Do not bother cleaning up after this process. Let's assume that controlling
 * terminal sends SIGINT to the process group on CTRL+C. */
int main(void) {
  shared = Mmap(NULL, getpagesize(), PROT_READ|PROT_WRITE, MAP_ANON|MAP_SHARED,
                -1, 0);

  /* TODO: Initialize semaphores and other shared state. */
  shared->cauldron=M;
  Sem_init(&shared->full,1,0);
  Sem_init(&shared->empty,1,0);
  Sem_init(&shared->lock,1,1);

  for (int i = 0; i < N; i++)
    if (Fork() == 0)
      savage();
  cook();

  return EXIT_SUCCESS;
}
