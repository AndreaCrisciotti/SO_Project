#include "topOS.h" //include the dipendence of Project

int main(){

    //Print the Head Of Program
    //takeInformationToProc();
    int choice = 0;

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

                break;

            case 2:

                break;

            case 3:

                break;

            case 4:

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
