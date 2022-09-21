#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mount.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "binary_file_search.h"

typedef struct{
    char pid[128];
    char user[128];
    char pr[128];
    char ni[128];
    char virt[128];
    char name[128];
}TopStruct;

struct Stat {
    dev_t     st_dev;         /* ID of device containing file */
    ino_t     st_ino;         /* Inode number */
    mode_t    st_mode;        /* File type and mode */
    nlink_t   st_nlink;       /* Number of hard links */
    uid_t     st_uid;         /* User ID of owner */
    gid_t     st_gid;         /* Group ID of owner */
    dev_t     st_rdev;        /* Device ID (if special file) */
    off_t     st_size;        /* Total size, in bytes */
    blksize_t st_blksize;     /* Block size for filesystem I/O */
    blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */

    /* Since Linux 2.6, the kernel supports nanosecond
        precision for the following timestamp fields.
        For the details before Linux 2.6, see NOTES. */

    struct timespec st_atim;  /* Time of last access */
    struct timespec st_mtim;  /* Time of last modification */
    struct timespec st_ctim;  /* Time of last status change */

    #define st_atime st_atim.tv_sec      /* Backward compatibility */
    #define st_mtime st_mtim.tv_sec
    #define st_ctime st_ctim.tv_sec
}InfoStat;



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
    system("clear");
    printf("*********************SO_Project Crisciotti Andrea*********************\n");

    const char* src  = "SO_Project/";
    const char* trgt = "/proc";
    const unsigned long mntflags = 0;
    const char* path = "../SO_Project/proc";

    MountFile(src,trgt,mntflags);

    int fileOpen = open(path, O_CREAT|O_RDWR, 0666);

    printf("\n%d",fileOpen);

    remove(path);
    close(fileOpen);

    umount(trgt);
}
