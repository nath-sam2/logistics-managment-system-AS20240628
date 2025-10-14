#include <stdio.h>
#include <stdlib.h>

int main()
{
    int choice;
    do{
        printf("\n=====Logistics Management System=====\n");
        printf("1. City Management\n");
        printf("2. Distance Management\n");
        printf("3. Vehicle Management\n");
        printf("4. Place a delivery\n");
        printf("5. Reports\n");
        printf("6. Save Data\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
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
            break;
        case 6:
            break;
        case 7:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Choice!\n");
            break;
        }
    }while(choice != 0);
    return 0;
}
