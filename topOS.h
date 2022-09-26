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
    float time;
    float cpu;
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
        printf("%s\t\t", info[i].group);
        printf("%.2f\t", info[i].time);
        // printf("%f\t", info[i].cpu);
        printf("%ld\t\t", info[i].virt);
        printf("%ld\t\t", info[i].shr);
        printf("%ld\t\t", info[i].res);
        printf("%s\n", info[i].command);
    }
}

void takeTimeInformation(struct TopStruct *info, int count){
    double time = 0;

    FILE *fp = fopen("/proc/uptime", "r");
    if(fp != NULL){
        fscanf(fp, "%lf", &time);
    }
    info[count].time = time;
    fclose(fp);
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

    //FIND A SOLUTION
}

//Print the information of Computer into PROC
void takeInformationToProc(){
    //Header of information
    printf("\033[1;80m"); //COLOR HEADER
    printf("\nPID\tUSER\tGROUP\t\tTIME\t\tVIRT \t\tSHR\t\tRES\t\tCOMMAND\n\n");
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

            //TAKE CPU Information
            takeTimeInformation(info,count-1);

            //TAKE COMMAND Information
            takeCommandInformation(info,count-1, path);

            //TAKE VIRT Information
            takeVirtInformation(info, count-1, path);

            //TAKE SHR Information
            takeShrInformation(info, count-1, path);

            //TAKE RES Information
            takeResInformation(info, count-1, path);

            //TO FIND SOLUTION
            takeCPUInformation(info, count-1, path);
        }
        closedir(directiory);
    }   

    printDataByOrder(info,rand() % 190 +1);
    free(info);
    free(dirInfo);

}