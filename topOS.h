#include<stdio.h>
#include<stdlib.h>
#include<grp.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<ctype.h>
#include<string.h>
#include<signal.h>
#include<errno.h>
#include<sys/stat.h>
#include<sys/sysinfo.h>
#include<sys/resource.h>
#include<sys/time.h>
#include<unistd.h>

//Definition of struct process
struct TopStruct{
    pid_t pid;
    char user[128];
    uid_t uid;
    long int pr;
    long int ni;
    long int virt;
    long int shr;
    long int res;
    char name[10];
    char group[10];
    float cpu;
    float memory;
    char command[100];
};

//Wait function for scan and View information
void attend(){
    for(int i = 0; i< 100000000; ++i);
}

void killProcess(pid_t pid){

   if(kill(pid,SIGKILL) == 0){
        printf("\nProcess by PID = %d is Kill\n", pid);
        
            
    }else{
        printf("\nERROR - Process by PID = %d wasn't Kill\n", pid);
        printf("ERROR: %s\n", strerror(errno));
    }
    
}

void terminateProcess(pid_t pid){
    if(kill(pid,SIGTERM) == 0){
        printf("\nProcess by PID = %d is Terminate\n", pid);
               
    }else{
        printf("\nERROR - Process by PID = %d wasn't Terminate\n", pid);
        printf("ERROR: %s\n", strerror(errno));
    }
       
}

void resumeProcess(pid_t pid){
    if(kill(pid,SIGCONT) == 0){
        printf("\nProcess by PID = %d is Resume\n", pid);
               
    }else{
        printf("\nERROR - Process by PID = %d wasn't Resume\n", pid);
        printf("ERROR: %s\n", strerror(errno));
    }    
}

void suspendProcess(pid_t pid){
    if(kill(pid,SIGSTOP) == 0){
        printf("\nProcess by PID = %d is Suspend\n", pid);
               
    }else{
        printf("\nERROR - Process by PID = %d wasn't Suspend\n", pid);
        printf("ERROR: %s\n", strerror(errno));
    }    
}

//Print all the specific of a Computer
void printSpecificOfComputer(){
    char character[128];
    
    //Open file /PROC/CPUINFO
    FILE* fp = fopen("/proc/cpuinfo","r");
    while(fgets(character, 128, fp) != NULL){

        //Print all data of computer
        printf("%s", character);
        attend();

    }
    system("clear");
}

void printDataByOrder(struct TopStruct *info, int refresh){
    //Print data of Information
    for(int i = refresh ; i < refresh+20 ; i++){
        
        printf("%d\t", info[i].pid);
        printf("%s\t", info[i].name);
        printf("%s\t|\t", info[i].group);
        
        if(info[i].virt < 999999){
            printf("%ld\t", info[i].virt);
        }else{
            printf("%ld\t", info[i].virt / 100);
        }
        
        printf("%ld\t", info[i].shr);
        printf("%ld\t|\t", info[i].res);

        if(info[i].cpu < 0.0){
            printf("ERR\t");
            printf("ERR\t");
        }else{
            printf("%.2f%%\t", info[i].cpu);
            printf("%.2f\t", info[i].memory);
        }

        

        printf("%s\n", info[i].command);
    }
}

void takeVirtInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/status", info[count].pid);
    long unsigned int dataVirt = 0;
    FILE *fp = fopen(path, "r");
    if(fp!= NULL){
        char data[100];
        while(fgets(data,sizeof(data), fp) != NULL){
            if(strncmp(data,"VmSize:",7) == 0){
                sscanf(data, "%*s %lu",&dataVirt);
                break;
            }
        }
        fclose(fp);
    }
    info[count].virt = dataVirt;
}

void takeGroupInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/status", info[count].pid);
    struct stat buf;
    stat(path,&buf);
    struct group *group = getgrgid(buf.st_gid);
    if(group == NULL){
        printf("ERROR GROUP: %s\n", strerror(errno));
        exit(2);
    }
    strcpy(info[count].group, group->gr_name);
}

void takeShrInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/status", info[count].pid);
    long unsigned int dataRes = 0;
    FILE *fp = fopen(path, "r");
    if(fp!= NULL){
        char data[100];
        while(fgets(data,sizeof(data), fp) != NULL){
            if(strncmp(data,"VmData:",7) == 0){
                sscanf(data, "%*s %lu",&dataRes);
                break;
            }
        }
        fclose(fp);
    }
    info[count].res = dataRes;
}

void takeResInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/status", info[count].pid);
    long unsigned int dataShr = 0;
    FILE *fp = fopen(path, "r");
    if(fp!= NULL){
        char data[100];
        while(fgets(data,sizeof(data), fp) != NULL){
            if(strncmp(data,"VmRSS:",6) == 0){
                sscanf(data, "%*s %lu",&dataShr);
                break;
            }
        }
        fclose(fp);
    }
    info[count].shr = dataShr;
}

void takeUserInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/status", info[count].pid);
    struct stat buf;
    stat(path,&buf);
    struct passwd *pw = getpwuid(buf.st_uid);

    if(pw == NULL){
        printf("ERROR UID: %s\n", strerror(errno));
        exit(2);
    }
    strcpy(info[count-1].name, pw->pw_name);
}

void takeCommandInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/stat", info[count].pid);
    FILE *fp = fopen(path, "r");
    int unused;
    char comm[100];
    char state;
    int ppid;

    if(fp!= NULL){
        fscanf(fp, "%d %s %c %d", &unused, comm, &state, &ppid);
        strcpy(info[count].command, comm);
    }
    fclose(fp);
}

void takeCPUInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/stat", info[count].pid);
    FILE *fp = fopen(path, "r");

    long unsigned int utime, stime;
    long long unsigned int starttime;
    char state;

    // READ MAN PROC/[PID]/STAT
    //    seq_printf(m, "%d (%s) %c", pid_nr_ns(pid, ns), tcomm, state);  // 1, 2, 3
    //    seq_put_decimal_ll(m, ' ', ppid);                               // 4
    //    seq_put_decimal_ll(m, ' ', pgid);                               // 5
    //    seq_put_decimal_ll(m, ' ', sid);                                // 6
    //    seq_put_decimal_ll(m, ' ', tty_nr);                             // 7
    //    seq_put_decimal_ll(m, ' ', tty_pgrp);                           // 8
    //    seq_put_decimal_ull(m, ' ', task->flags);                       // 9
    //    seq_put_decimal_ull(m, ' ', min_flt);                           // 10
    //    seq_put_decimal_ull(m, ' ', cmin_flt);                          // 11
    //    seq_put_decimal_ull(m, ' ', maj_flt);                           // 12
    //    seq_put_decimal_ull(m, ' ', cmaj_flt);                          // 13
    //    seq_put_decimal_ull(m, ' ', cputime_to_clock_t(utime));         // 14
    //    seq_put_decimal_ull(m, ' ', cputime_to_clock_t(stime));         // 15
    //    seq_put_decimal_ll(m, ' ', cputime_to_clock_t(cutime));         // 16
    //    seq_put_decimal_ll(m, ' ', cputime_to_clock_t(cstime));         // 17
    //    seq_put_decimal_ll(m, ' ', priority);                           // 18
    //    seq_put_decimal_ll(m, ' ', nice);                               // 19
    //    seq_put_decimal_ll(m, ' ', num_threads);                        // 20
    //    seq_put_decimal_ull(m, ' ', 0);                                 // 21
    //    seq_put_decimal_ull(m, ' ', start_time);                        // 22
    //    seq_put_decimal_ull(m, ' ', vsize);                             // 23

    if (fp != NULL)
    {
        //Use * if you wan't take parameters for example *u if the parameters is an lu or ld
        fscanf(fp, "%*d %*s %c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*u %*u %*d %*d %llu %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*d %*d %*u %*u %*u %*u %*d %*u %*u %*u %*u %*u %*u %*u %*d", &state, &utime, &stime, &starttime);
        fclose(fp);
    }

    double uptime = 0;
    FILE *fp2 = fopen("/proc/uptime", "r");
    if (fp2 != NULL)
    {
        fscanf(fp2, "%lf", &uptime);
        fclose(fp2);
    }

    double cpuPercentage = (utime / sysconf(_SC_CLK_TCK) + stime / sysconf(_SC_CLK_TCK)) / (uptime - starttime / sysconf(_SC_CLK_TCK)) * 100;
    info[count].cpu = cpuPercentage;
}

void takeMemInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/stat", info[count].pid);
    long int rss;
    long unsigned int memory = 0;

    FILE *fp = fopen(path, "r");
    if(fp != NULL){
        fscanf(fp, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %*u %*u %*d %*d %*u %*u %*d %*d %*u %*u %ld %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*u %*d %*d %*u %*u %*u %*u %*d %*u %*u %*u %*u %*u %*u %*u %*d", &rss);
        
        fclose(fp);
    }
    
    FILE *fp2 = fopen("/proc/meminfo", "r");
    if(fp2 != NULL){
        char data[100];
        while(fgets(data, sizeof(data), fp2) != NULL){
            if(strncmp(data, "MemTotal:", 9) == 0){
                sscanf(data, "%*s %lu", &memory);
                break;
            }
        }
    }
    fclose(fp2);

    info[count].memory = (double)(rss * getpagesize() / 1024) / (double)memory * 100;
    
}

//Print the information of Computer into PROC
void takeInformationToProc(){
    //Header of information
    printf("\033[1;80m"); //COLOR HEADER
    printf("\nPID\tUSER\tGROUP\t|\tVIRT\tSHR\tRES\t|\tCPU%%\tMEMORY%%\tCOMMAND\n\n");
    printf("\033[0m"); //RESET COLOR

    //Init the struct for insert data
    struct TopStruct *info = calloc(0, sizeof(struct TopStruct));
    DIR *directiory;
    struct dirent *dirInfo;
    int count = 0;
    char path[30];
    
    //Extract PID to directory PROC
    if((directiory = opendir("/proc")) == NULL){
       printf("ERROR OPENDIR-PROC: %s\n", strerror(errno));
       exit(1);
    }else{
        while((dirInfo = readdir(directiory)) != NULL ){
            //Take only number for the directory
            int isNumber = 1;
            for(int i = 0; i < strlen(dirInfo->d_name); i++){
                if(isdigit(dirInfo->d_name[i]) == 0){
                    //If a d_name isn't a number close cicle
                    isNumber = 0;
                    break;
                }
            }
            //Jump to the new directory
            if(isNumber == 0){
                continue;
            }      
            
            count++;
            info = realloc(info, count * sizeof(struct TopStruct));

            //Take PID Information
            info[count-1].pid = atoi(dirInfo->d_name);
            
            //Take USER Information
            takeUserInformation(info, count-1, path);            

            //TAKE GROUP Information
            takeGroupInformation(info, count-1, path);            

            //TAKE COMMAND Information
            takeCommandInformation(info,count-1, path);

            //TAKE VIRT Information
            takeVirtInformation(info, count-1, path);

            //TAKE SHR Information
            takeShrInformation(info, count-1, path);

            //TAKE RES Information
            takeResInformation(info, count-1, path);

            //TAKE CPU Information
            takeCPUInformation(info, count-1, path);

            //TAKE MEMORY Information
            takeMemInformation(info, count-1, path);
        }
        closedir(directiory);
    }   

    printDataByOrder(info,rand() % 190 +1);
    free(info);
    free(dirInfo);

}