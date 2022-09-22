#include<stdio.h>
#include<stdlib.h>
#include<grp.h>
#include<dirent.h>
#include<pwd.h>
#include<grp.h>
#include<ctype.h>
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

    printf("\nCOUNT\tUSER\tPR\tNI\tVIRT\tCOMMAND\n\n");

    struct TopStruct *info = calloc(0, sizeof(struct TopStruct));
    DIR *directiory;
    struct dirent *dirInfo;
    int count = 0;
    
    if((directiory = opendir("/proc")) == NULL){
       printf("ERROR into Directory PROC!!");
       exit(1);
    }else{
        while((dirInfo = readdir(directiory)) != NULL ){
            
            int is_number = 1;
            for(int i = 0; i < strnlen(dirInfo->d_name,1000000); i++){
                if(!isdigit(dirInfo->d_name[i])){
                    is_number = 0;
                    break;
                }
            }
            if(!is_number){
                continue;
            }

            count++;
            info = realloc(info, count * sizeof(struct TopStruct));
            info[count-1].pid = atoi(dirInfo->d_name);
            
        }
        closedir(directiory);
    }

    for(int i = 0; i < 15 ; i++){
        printf("%d\t\n", info[i].pid);
    }

    free(info);

}