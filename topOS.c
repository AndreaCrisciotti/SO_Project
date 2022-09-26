#include "topOS.h" //include the dipendence of Project

int main(){
    //REMEMBER TO USE SUDO FOR START PROGRAM BECAUSE WITHOUT NOT WORK!!!!
    int choice = 0;
    pid_t pid = 0;

    while(choice != 7){
        system("clear");
        //Graphics of Program
        printf("\033[1;90m"); //COLOR HEADER
        printf("************************************************************************\n");
        printf("********************* SO_Project Crisciotti Andrea *********************\n");
        printf("*********************      Exame SO 2021/2022      *********************\n");
        printf("************************************************************************\n\n");
        printf("\033[0m"); //RESET COLOR

        //Print information of process in Execution
        takeInformationToProc();

        //Print commando to use
        printf("\033[1;93m"); //COLOR HEADER
        printf("\n\n1-Terminate\t2-Kill\t3-Suspend\t4-Resume\t5-View info Computer\t6-Refresh\t7-Exit\n");
        
        //Select choice by switch/case
        printf("What do you want to do?---> ");
        scanf("%d", &choice);
        printf("\033[0m"); //RESET COLOR

        switch (choice)
        {
            case 1:
                printf("Whitch process do you want to TERMINATE: ");
                scanf("%d",&pid);
                terminateProcess(pid);
                attend();
                attend();
                attend(); 
                break;

            case 2:
                printf("Whitch process do you want to KILL: ");
                scanf("%d",&pid);
                killProcess(pid);
                attend();
                attend();
                attend();                
                break;

            case 3:
                printf("Whitch process do you want to SUSPEND: ");
                scanf("%d",&pid);
                suspendProcess(pid);
                attend();
                attend();
                attend(); 
                break;

            case 4:
                printf("Whitch process do you want to RESUME: ");
                scanf("%d",&pid);
                resumeProcess(pid);
                attend();
                attend();
                attend(); 
                break;

            case 5:
                system("clear");
                printSpecificOfComputer();
                break;

            case 6:
                //Refresh board
                
                break;

            case 7:
                printf("Program Exit....");
                break;
            
            default:
                printf("Please, use a right choice!!!\n");
                attend();
                attend();
                attend();
                
                break;
        }
    }
    

}
