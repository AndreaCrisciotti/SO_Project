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

int MountFile(const char* src, const char* trgt, const unsigned long mntflags){

    int i = mount(src,trgt,"proc",mntflags,"");
    if (i == 0)
    {
        printf("\nMount created at %s...\n", trgt);
        return i;
    }
    else
    {
        printf("\nError : Failed to mount \n"
                "Reason: %s [%d]\n"
                , strerror(errno), errno);
        return i;
    }
}

int main(int argc, char** argv){
  
    //USE THE EXE FILE WHIT SUDO ---> sudo ./topOS
    printf("*********************SO_Project Crisciotti Andrea*********************\n");

    const char* src  = "none";
    const char* trgt = "/proc";
    const unsigned long mntflags = 0;

    int i = MountFile(src,trgt,mntflags);
    printf("%d",i);
    umount(trgt);
}
