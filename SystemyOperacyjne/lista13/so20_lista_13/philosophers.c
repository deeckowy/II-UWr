#include "./include/csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

static void randsleep(void) {
  usleep(rand() % 5000 + 5000000);
}

#define N 50

static pthread_t td[N];
static sem_t forks[N];
/* DONE: If you need extra shared state, define it here. */
static int free_forks;
static sem_t waiter;
#define WAITER(instruction){Sem_wait(&waiter);instruction;Sem_post(&waiter);}

void *philosopher(void *id) {
  int right = (intptr_t)id;
  int left = right == 0 ? N - 1 : right - 1;

  for (;;) {
    /* Think */
    printf("Philisopher [%d] is thinking now!\n",right);
    randsleep();

    //After thinking philosopher needs to ask waiter for forks 
    bool is_ready=false;
    while(is_ready)
    {
      WAITER(if(free_forks>2){free_forks--;is_ready=true;});
    }
    /* DONE: Take forks (without deadlock & starvation) */
    //Waiting for forks is allowed only if there are at least 2 free_forks 
    Sem_wait(&forks[right]);
    WAITER(free_forks--);
    Sem_wait(&forks[left]);

    /* Eat */
    printf("Philisopher [%d] is eating now!\n",right);
    randsleep();

    /* DONE: Put forks (without deadlock & starvation) */
    Sem_post(&forks[left]);
    WAITER(free_forks++);
    Sem_post(&forks[right]);
    WAITER(free_forks++);
  }
  return NULL;
}

int main(void) {
  /* TODO: If you need extra shared state, initialize it here. */
  Sem_init(&waiter,0,1);
  free_forks=N;

  for (int i = 0; i < N; i++)
    Sem_init(&forks[i], 0, 1);

  for (int i = 0; i < N; i++)
    Pthread_create(&td[i], NULL, philosopher, (void *)(intptr_t)i);

  for (int i = 0; i < N; i++)
    Pthread_join(td[i], NULL);
  
  return EXIT_SUCCESS;
}
