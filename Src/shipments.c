#include <stdio.h>
#include <string.h>
#include "../include/shipments.h"

char cities[MAX_CITIES][MAX_NAME_LEN];
int distance[MAX_CITIES][MAX_CITIES];
int currentCityCount=0;

char name[MAX_NAME_LEN];

void addCity()
{
  if(currentCityCount>=MAX_CITIES)
  {
      printf("Can't add more cities!\n");
      return;
  }
  else
  {
      printf("Enter City Name: ");
      scanf("%s", &name);

      for(int i = 0; i< currentCityCount; i++)
      {
          if(strcmp(cities[i],name)==0)
          {
              printf("City already exists!\n");
              return;
          }
      }
      strcpy(cities[currentCityCount], name);
      currentCityCount++;

      for(int i = 0; i<currentCityCount; i++)
      {
          distance[i][currentCityCount-1]=0;
          distance[currentCityCount-1][i]=0;
      }
      printf("City added successfully!\n");
  }
}


void renameCity()
{
  int index;
  if(currentCityCount==0)
  {
      printf("There are no cities saved!\n");
      return;
  }

  displayCities();
  printf("Enter city index to rename(0-%d): ",currentCityCount-1);
  scanf("%d",&index);

  if(index<0 || index >= currentCityCount)
  {
      printf("Invalid index!\n");
      return;
  }

  char newName[MAX_NAME_LEN];
  printf("Enter new name: ");
  scanf("%s",newName);

  strcpy(cities[index], newName);
  printf("City renamed successfully!\n");
}


void removeCity()
{
  int index;
  if(currentCityCount==0)
  {
      printf("No cities available!\n");
      return;
  }
  displayCities();
  printf("Enter city index to remove(0-%d): ", currentCityCount-1);
  scanf("%d",&index);

  if(index<0 || index >= currentCityCount)
  {
      printf("Invalid index!\n");
      return;
  }

  for (int i = index; i<currentCityCount; i++)
  {
      strcpy(cities[i], cities[i+1]);
  }

  for (int i = index; i<currentCityCount; i++)
  {
      for (int j = 0; j<currentCityCount; j++)
      {
          distance[i][j]=distance[i+1][j];
      }
  }

  for (int i = index; i<currentCityCount; i++)
  {
      for (int j = 0; j<currentCityCount; j++)
      {
          distance[i][j]=distance[i][j+1];
      }
  }

  currentCityCount--;
  printf("City has been removed!\n");
}


void displayCities()
{
  if(currentCityCount == 0)
  {
      printf("No cities added yet\n");
      return;
  }
  else
  {
      printf("=====City List=====\n");
      for(int i = 0; i<currentCityCount; i++)
      {
          printf("%2d. %s\n",i+1,cities[i]);
      }
  }
}

void editDistance()
{
    if(currentCityCount<2)
    {
        printf("Not enough cities are saved to edit distances. \n");
        return;
    }

    int i, j, d;
    displayCities();

    printf("Enter initial city index: ");
    scanf("%d", &i);

    printf("Enter destination city index: ");
    scanf("%d", &j);

    if(i<0 || j<0 || i >= currentCityCount || j>= currentCityCount)
    {
        printf("invalid indexes!");
        return;
    }

    if(i==j)
    {
        printf("Same city\n");
        return;
    }

    printf("Enter distance between %s and %s(km): ",cities[i]);
    scanf("%d",&d);

    if(d<=0)
    {
        printf("Distance cannot be negative\n");
        return;
    }

    distance[i][j]=d;
    distance[j][i]=d;

    printf("Distance updated successfully!\n");
}

void displayDistanceTable()
{
    if(currentCityCount==0)
    {
        printf("No cities added yet.\n");
        return;
    }

    printf("=====Distance Table (km)=====\n");
    printf("%12s"," ");

    for(int i = 0; i<currentCityCount; i++)
    {
        printf("%10s",cities[i]);
    }
    printf("\n");

    for (int i = 0; i<currentCityCount; i++)
    {
        printf("%10s",cities[i]);
        for(int j = 0; j<currentCityCount; j++)
        {
            printf("%10d",distance[i][j]);
        }
        printf("\n");
    }
}
