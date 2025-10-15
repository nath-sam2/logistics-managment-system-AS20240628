#include <stdio.h>
#include <stdlib.h>

void cityManagementMenu();
void distanceManagementMenu();

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
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
        case 1:
            cityManagementMenu();
            break;
        case 2:
            distanceManagementMenu();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 0:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid Choice!\n");
        }
    }while(choice != 0);
    return 0;
}

void cityManagementMenu()
{
    int cityChoice;
            do{
                printf("\n---City Management---\n");
                printf("1. Add City\n");
                printf("2. Rename City\n");
                printf("3. Remove City\n");
                printf("4. Display Cities\n");
                printf("0. Back\n");
                printf("Enter your choice: ");
                scanf("%d",&cityChoice);

                switch(cityChoice)
                {
             case 1:
                addCity();
                break;
             case 2:
                renameCity();
                break;
             case 3:
                removeCity();
                break;
             case 4:
                displayCities();
                break;
             case 0:
                printf("Returning to the main menu!\n");
                break;
             default:
                printf("Invalid choice!\n");
                }
            }while(cityChoice !=0);
}

void distanceManagementMenu()
{
    int distChoice;
                do{
                    printf("\n---Distance Management---\n");
                    printf("1. Edit Distance\n");
                    printf("2. Display Distance\n");
                    printf("0. Back\n");
                    printf("Enter your choice: ");
                    scanf("%d",&distChoice);

                switch(distChoice)
                {
             case 1:
                editDistance();
                break;
             case 2:
                displayDistanceTable();
                break;
             case 0:
                 printf("Returning to the main menu!\n");
                break;
             default:
                printf("Invalid choice!\n");
                }
            }while(distChoice !=0);
}
