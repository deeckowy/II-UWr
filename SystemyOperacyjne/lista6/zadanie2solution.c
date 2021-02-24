#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int my_acces(struct stat* sb,int mode)
{
    if(sb==NULL)
        return -1;
    int ac=7;
    ac&=mode;
    uid_t us=getuid();
    if(sb->st_uid==us)
        return (((sb->st_mode>>6)&ac)^ac)?-1:0;
    
    int gc=16;
    gid_t gs[gc];
    /*
        Tutaj powinien być mechanizm z zadania 7 który 
        rozszerza tablice gs oraz ustawia gc 
        tak aby pomiescic
        wszystkie grupy
    */ 
    for(int i=0;i<gc;i++)
        if(sb->st_gid==gs[i])
            return (((sb->st_mode>>3)&ac)^ac)?-1:0;

    return ((sb->st_mode&ac)^ac)?-1:0;
}