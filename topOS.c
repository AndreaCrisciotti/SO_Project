#include "topOS.h" //include the dipendence of Project

int main(){
    //REMEMBER TO USE SUDO FOR START PROGRAM BECAUSE WITHOUT NOT WORK!!!!
    int choice = 0;
    pid_t pid = 0;

    while(choice != 6){
        system("clear");
        printf("*********************SO_Project Crisciotti Andrea*********************\n");
        takeInformationToProc();
        printf("1)Terminate\t2)Kill\t3)Suspend\t4)Resume\t5)View info Computer\t6)Exit\n");
        printf("What do you want to do?---> ");
        scanf("%d", &choice);

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
                printf("Program Exit....");
                break;
            
            default:
                printf("Please, use a right choice!!!\n");
                break;
        }
    }
    

}
