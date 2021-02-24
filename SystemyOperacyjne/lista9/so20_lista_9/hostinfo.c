#include "./include/csapp.h"

int main(int argc, char **argv) {
  struct addrinfo *p, *listp, hints;
  int rc, flags;
  char *dmn=NULL;
  char *srv=NULL;
  switch (argc)
  {
    case 3:
      srv=argv[2];
    case 2:
      dmn=argv[1];
    break;
    default:
      app_error("usage: %s <domain name> [service]\n", argv[0]);
    break;
  }


  /* Get a list of addrinfo records */
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC; /* ALL adresess */
  hints.ai_socktype = SOCK_STREAM;
  /* Connections only */
  if ((rc = getaddrinfo(dmn,srv, &hints, &listp)) != 0)
    gai_error(rc, "getaddrinfo");

  /* Walk the list and display each IP address */
  flags = NI_NUMERICHOST|NI_NUMERICSERV; /* Display address string and service instead of domain name */

  for (p = listp; p; p = p->ai_next) 
  {
    char hostbuf[MAXLINE];
    char servbuf[MAXLINE];
    Getnameinfo(p->ai_addr, p->ai_addrlen, hostbuf, MAXLINE,servbuf,MAXLINE,flags);
    if(srv&&p->ai_family==AF_INET6)
      printf("[%s]:%s\n",hostbuf,servbuf);
    else if(p->ai_family==AF_INET6)
      printf("[%s]\n",hostbuf);
    else if(srv)
      printf("%s:%s\n",hostbuf,servbuf);
    else 
      printf("%s\n",hostbuf);

  }

  /* Clean up */
  freeaddrinfo(listp);

  return EXIT_SUCCESS;
}
