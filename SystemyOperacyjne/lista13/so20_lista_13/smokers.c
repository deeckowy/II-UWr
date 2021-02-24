#include "./include/csapp.h"

static __unused void outc(char c) {
  Write(STDOUT_FILENO, &c, 1);
}

static __thread unsigned seed;

static sem_t tobacco;
static sem_t matches;
static sem_t paper;
static sem_t doneSmoking;

/* TODO: If you need any extra global variables, then define them here. */
static bool isPaper;
static bool isTobacco;
static bool isMatches;
static sem_t lock;
static sem_t pt;
static sem_t mt; 
static sem_t mp;

static void *agent(void *arg) {
  seed = pthread_self();

  while (true) {
    Sem_wait(&doneSmoking);

    int choice = rand_r(&seed) % 3;
    if (choice == 0) {
      Sem_post(&tobacco);
      Sem_post(&paper);
    } else if (choice == 1) {
      Sem_post(&tobacco);
      Sem_post(&matches);
    } else {
      Sem_post(&paper);
      Sem_post(&matches);
    }
  }

  return NULL;
}

/* TODO: If you need extra threads, then define their main procedures here. */

static void *tobaccohelper(void *arg)
{
  while(true)
  {
    Sem_wait(&tobacco);
    Sem_wait(&lock);
    if(isPaper)
    {
      isPaper=false;
      outc('T');
      outc('+');
      outc('P');
      outc('=');
      Sem_post(&pt);
    }
    else if(isMatches)
    {
      isMatches=false;
      outc('T');
      outc('+');
      outc('M');
      outc('=');
      Sem_post(&mt);
    }
    else 
      isTobacco=true;
    Sem_post(&lock);
  }
  return NULL;
}

static void *matcheshelper(void *arg)
{
  while(true)
  {
    Sem_wait(&matches);
    Sem_wait(&lock);
    if(isPaper)
    {
      isPaper=false;
      outc('M');
      outc('+');
      outc('P');
      outc('=');
      Sem_post(&mp);
    }
    else if(isTobacco)
    {
      outc('M');
      outc('+');
      outc('T');
      outc('=');
      isTobacco=false;
      Sem_post(&mt);
    }
    else 
      isMatches=true;
    Sem_post(&lock);
  }
  return NULL;
}

static void *paperhelper(void *arg)
{
  while(true)
  {
    Sem_wait(&paper);
    Sem_wait(&lock);
    if(isMatches)
    {
      isMatches=false;
      outc('P');
      outc('+');
      outc('M');
      outc('=');
      Sem_post(&mp);
    }
    else if(isTobacco)
    {
      isTobacco=false;
      outc('P');
      outc('+');
      outc('T');
      outc('=');
      Sem_post(&pt);
    }
    else 
      isPaper=true;
    Sem_post(&lock);
  }
  return NULL;
}

static void randsleep(void) {
  usleep(rand_r(&seed) % 1000 + 1000);
}

static void make_and_smoke(char smoker) {
  randsleep();
  outc(smoker);
  randsleep();
}

static void *smokerWithMatches(void *arg) {
  seed = pthread_self();

  while (true) {
    /* TODO: wait for paper and tobacco */
    Sem_wait(&pt);
    make_and_smoke('M');
    outc('\n');
    Sem_post(&doneSmoking);
  }

  return NULL;
}

static void *smokerWithTobacco(void *arg) {
  seed = pthread_self();

  while (true) {
    /* TODO: wait for paper and matches */
    Sem_wait(&mp);
    make_and_smoke('T');
    outc('\n');
    Sem_post(&doneSmoking);
  }

  return NULL;
}

static void *smokerWithPaper(void *arg) {
  seed = pthread_self();
 
  while (true) {
    /* TODO: wait for tobacco and matches */
    Sem_wait(&mt);
    make_and_smoke('P');    
    outc('\n');
    Sem_post(&doneSmoking);
  }

  return NULL;
}

int main(void) {
  Sem_init(&tobacco, 0, 0);
  Sem_init(&matches, 0, 0);
  Sem_init(&paper, 0, 0);
  Sem_init(&doneSmoking, 0, 1);

  /* TODO: Initialize your global variables here. */
  isTobacco=false;
  isMatches=false;
  isPaper=false;
  Sem_init(&pt,0,0);
  Sem_init(&mp,0,0);
  Sem_init(&mt,0,0);
  Sem_init(&lock,0,1);
  pthread_t match_h,paper_h,tobac_h;
  Pthread_create(&paper_h,NULL,paperhelper,NULL);
  Pthread_create(&match_h,NULL,matcheshelper,NULL);
  Pthread_create(&tobac_h,NULL,tobaccohelper,NULL);
  
  pthread_t agentThread;
  Pthread_create(&agentThread, NULL, agent, NULL);

  pthread_t smokerPaperThread, smokerMatchesThread, smokerTobaccoThread;
  Pthread_create(&smokerPaperThread, NULL, smokerWithPaper, NULL);
  Pthread_create(&smokerMatchesThread, NULL, smokerWithMatches, NULL);
  Pthread_create(&smokerTobaccoThread, NULL, smokerWithTobacco, NULL);

  Pthread_join(match_h,NULL);
  Pthread_join(paper_h,NULL);
  Pthread_join(tobac_h,NULL);
  Pthread_join(agentThread, NULL);
  Pthread_join(smokerPaperThread, NULL);
  Pthread_join(smokerMatchesThread, NULL);
  Pthread_join(smokerTobaccoThread, NULL);

  return 0;
}
