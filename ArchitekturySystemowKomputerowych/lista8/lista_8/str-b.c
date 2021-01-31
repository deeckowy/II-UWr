#include <stdlib.h>


char *somestr(void) 
{
  static char t1[]="Hello, world!";
  char* t=&t1; 
  return t;
}
