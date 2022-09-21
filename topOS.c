#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include "binary_file_search.h"

typedef struct{
    char pid[128];
    char user[128];
    char pr[128];
    char ni[128];
    char virt[128];
    char name[128];
}TopStruct;


void TopStruct_init(TopStruct* top, char* pid,char* user, char* pr, char* ni, char* virt, char* name){
  strcpy(top->pid, pid);
  strcpy(top->user, user);
  strcpy(top->pr, pr);
  strcpy(top->ni, ni);
  strcpy(top->virt, virt);
  strcpy(top->name, name);
}

int main(int argc, char** argv){
  
    printf("*********************SO_Project Crisciotti Andrea*********************\n");

    const char* src  = "none";
    const char* trgt = "/proc";
    const unsigned long mntflags = 0;

    int i = mount(src,trgt,"proc",mntflags,"");
    if (i == 0)
    {
        printf("\nMount created at %s...\n", trgt);
        umount(trgt);
    }
    else
    {
        printf("\nError : Failed to mount \n"
                "Reason: %s [%d]\n"
                , strerror(errno), errno);
        return -1;
    }

    printf("%d",i);
    umount(trgt);
}
