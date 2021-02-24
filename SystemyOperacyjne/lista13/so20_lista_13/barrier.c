#include "./include/csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

typedef struct {
  /* TODO: Use this structure to store barrier internal state. */
  unsigned int index;
  int n;
  unsigned int turn;
  int passed;
  sem_t start;
  sem_t lock;
} barrier_t;

static barrier_t *barrier_init(int n) {
  if (n < 1)
    app_error("barrier_init requires n > 0");

  barrier_t *b = Mmap(NULL, sizeof(barrier_t), PROT_READ|PROT_WRITE,
                      MAP_ANON|MAP_SHARED, -1, 0);

  /* TODO: Initialize barrier internal state. */
  b->n=n;
  b->index=0;
  b->passed=0;
  b->turn=0;
  Sem_init(&b->lock,1,1);
  Sem_init(&b->start,1,0);
  return b;
}

static void barrier_wait(barrier_t *b) {
  /* TODO: Provide wait procedure implementation here. */
  Sem_wait(&b->lock);
  int pturn=b->index/b->n;
  b->index++;
  if(b->index&&b->index%b->n==0)
    Sem_post(&b->start);
  sem_post(&b->lock);
  bool exit=false;
  while(!exit)
  {
    Sem_wait(&b->start);
    Sem_wait(&b->lock);
    if(pturn==b->turn)
    {
      exit=true;
      b->passed++;
      if(b->passed==b->n)
      {
        b->turn++;
        if(b->turn>b->index)
          b->turn=0;
        b->passed=0;
        Sem_post(&b->lock);
        return;
      }
    } 
    Sem_post(&b->lock);
    Sem_post(&b->start);
  }
}

static void barrier_destroy(barrier_t *b) {
  /* TODO: Provide destroy procedure implementation here. */
  Munmap(b,sizeof(barrier_t));
}

#define K 100
#define N 50
#define P 100

static noreturn void horse(barrier_t *b) {
  int n = rand() % K + K;

  outc('+');
  for (int i = 0; i < n; i++) {
    barrier_wait(b);
    usleep(rand() % 2000 + 1000);
  }

  outc('-');

  exit(EXIT_SUCCESS);
}

/* Do not bother cleaning up after this process. Let's assume that controlling
 * terminal sends SIGINT to the process group on CTRL+C. */
int main(void) {
  barrier_t *b = barrier_init(N);

  int horses = 0;

  for (;;) {
    do {
      if (Fork() == 0) {
        srand(getpid());
        horse(b);
      }
      horses++;
    } while (horses < P);

    Wait(NULL);
    horses--;
  }

  barrier_destroy(b);

  return EXIT_SUCCESS;
}
