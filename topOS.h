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
#include<unistd.h>

//Definition of struct process
struct TopStruct{
    pid_t pid;
    char user[128];
    uid_t uid;
    long int pr;
    long int ni;
    long int virt;
    char name[10];
    char group[10];
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
    FILE* fp;
    char character[128];
    
    //Open file /PROC/CPUINFO
    fp=fopen("/proc/cpuinfo","r");
    while(fgets(character, 128, fp) != NULL){

        //Print all data of computer
        printf("%s", character);
        attend();

    }
    system("clear");
}

void printDataByOrder(struct TopStruct *info){
    //Print data of Information

    for(int i = 180 ; i < 200 ; i++){
        printf("%d\t", info[i].pid);
        printf("%s\t", info[i].name);
        printf("%s\t", info[i].group);
        printf("%.2f\t", info[i].cpu);
        printf("%ld\t", info[i].virt);
        printf("%s\n", info[i].command);

    }
}

void takeTimeInformation(struct TopStruct *info, int count){
    double time = 0;
    FILE *fp = fopen("/proc/uptime", "r");
    if(fp != NULL){
        fscanf(fp, "%lf", &time);
        
    }
    info[count].cpu = time/3600;
    fclose(fp);    
}

void takeVirtInformation(struct TopStruct *info, int count, char *path){
    
    long unsigned int dataVirt = 0;
    FILE *fp = fopen(path, "r");
    if(fp!= NULL){
        char data[100];
        while(fgets(data,sizeof(data), fp) != NULL){
            if(strncmp(data,"VmSize:",7) == 0){
                sscanf(data, "%lu",&dataVirt);
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
    }
    strcpy(info[count].group, group->gr_name);

}

void takeUserInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/status", info[count].pid);
    struct stat buf;
    stat(path,&buf);
    struct passwd *pw = getpwuid(buf.st_uid);

    if(pw == NULL){
        printf("ERROR UID: %s\n", strerror(errno));
    }
    strcpy(info[count-1].name, pw->pw_name);
}

void takeCommandInformation(struct TopStruct *info, int count, char *path){
    sprintf(path, "/proc/%d/stat", info[count].pid);
    FILE *f = fopen(path, "r");

    int unused;
    char comm[100];
    char state;
    int ppid;
    fscanf(f, "%d %s %c %d", &unused, comm, &state, &ppid);
    strcpy(info[count].command, comm);
    fclose(f);
}

//Print the information of Computer into PROC
void takeInformationToProc(){

    //Header of information
    printf("\nPID\tUSER\tGROUP\tCPU\tVIRT\t\tNI\tCOMMAND\n");

    struct TopStruct *info = calloc(0, sizeof(struct TopStruct));
    DIR *directiory;
    struct dirent *dirInfo;
    int count = 0;
    char path[30];
    
    //Extract PID to directory PROC
    if((directiory = opendir("/proc")) == NULL){
       printf("ERROR into Directory PROC!!");
       exit(1);
    }else{
        while((dirInfo = readdir(directiory)) != NULL ){
            
            //Take only number for the directory
            int isNumber = 1;
            for(int i = 0; i < strlen(dirInfo->d_name); i++){
                if(!isdigit(dirInfo->d_name[i])){
                    isNumber = 0;
                    break;
                }
            }
            if(!isNumber){
                continue;
            }      
            
            count++;
            info = realloc(info, count * sizeof(struct TopStruct));

            //Take PID Information
            info[count-1].pid = atoi(dirInfo->d_name);
            
            //END Take PID Information
            
            //Take USER Information

            takeUserInformation(info, count-1, path);
            
            //END Take USER Information

            //TAKE GROUP Information

            takeGroupInformation(info, count-1, path);
            
            //END TAKE GROUP Information

            //TAKE CPU Information

            takeTimeInformation(info,count-1);

            //END TAKE CPU Information

            //TAKE COMMAND Information

            takeCommandInformation(info,count-1, path);

            //END TAKE COMMAND Information


        }

        closedir(directiory);
    }   
    printDataByOrder(info);
    free(info);

}