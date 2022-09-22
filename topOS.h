#include<stdio.h>
#include<stdlib.h>
#include<grp.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<string.h>

//Definition of struct process
struct TopStruct{
    int pid;
    char user[128];
    long int pr[128];
    long int ni[128];
    long int virt[128];
    char name[128];
};

//Wait function for scan and View information
void attend(){
    for(int i = 0; i< 100000000; ++i);
}

//Print all the specific of a Computer
void printSpecificOfComputer(){
    FILE* fp;
    char character[128];
    
    //Open file /PROC/CPUINFO
    fp=fopen("/proc/cpuinfo","r");
    while(fgets(character, 128, fp) != NULL){

        //Print all data
        printf("%s", character);
        attend();

    }
    attend();
    system("clear");
}

//Print the information of Computer into PROC
void takeInformationToProc(){

    printf("COUNT\tUSER\tPR\tNI\tVIRT\tCOMMAND");

    struct TopStruct *info = calloc(0, sizeof(struct TopStruct));
    DIR *directiory = opendir("/proc");
    struct dirent *dirInfo = readdir(directiory);
    int count = 0;
    
    if(directiory == NULL){
       printf("ERROR into Directory PROC!!");
       exit(1);
    }else{
        while(dirInfo != NULL ){
            
            count++;
            info = realloc(info, count * sizeof(struct TopStruct));
            info[count-1].pid = atoi(dirInfo->d_name);
            // strcpy(info[count].pid, dirInfo->d_name);
            
        }
        closedir(directiory);
    }

    for(int i = 0; i < count ; i++){
        printf("%d\t\n", info[i].pid);
    }

    free(info);

}