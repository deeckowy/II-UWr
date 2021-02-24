#include "../so20_lista_2/libcsapp/csapp.h"

static pid_t spawn(void (*fn)(void)) {
  pid_t pid = Fork();
  if (pid == 0) {
    fn();
    printf("(%d) I'm done!\n", getpid());
    exit(EXIT_SUCCESS);
  }
  return pid;
}


static void grandchild(void) {
  printf("(%d) Waiting for signal!\n", getpid());
  pause();
  printf("(%d) Got the signal!\n", getpid());
}

static void child(void) {
  setpgid(0,0);
  pid_t pid=spawn(grandchild);
  printf("(%d) Grandchild (%d) spawned!\n", getpid(), pid);
}

/* Runs command "ps -o pid,ppid,pgrp,stat,cmd" using execve(2). */
static void ps(void) {
  char* argv[]={
    "/bin/ps","-o","pid,ppid,pgrp,stat,cmd",NULL
  };
  execve(argv[0],argv,NULL);
}

int main(void) {
  #ifdef LINUX
  Prctl(PR_SET_CHILD_SUBREAPER, 1);
  #endif
  printf("(%d) I'm a reaper now!\n", getpid());

  int status;

  pid_t child_pid=spawn(child);
  Waitpid(child_pid,NULL,0);

  pid_t ps_pid=spawn(ps);
  Waitpid(ps_pid,NULL,0);
  
  Kill(-child_pid,2);
  printf("(%d) killing process (%d) with SIG_INT\n",getpid(),child_pid);
  Waitpid(-1,&status,0);
  printf("Proces (%d) exited with status %d\n",child_pid,status);

  return EXIT_SUCCESS;
}
