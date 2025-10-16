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

    int src, dest, dist;
    displayCities();

    printf("Enter source city index: ");
    if(scanf("%d",&src)!=1)
    {
        while(getchar()!='\n');
        printf("Invalid input.\n");
        return;
    }

    printf("Enter destination city index: ");
    if(scanf("%d",&dest)!=1)
    {
        while(getchar()!='\n');
        printf("Invalid input.\n");
        return;
    }

    if(src<0 || dest<0 || src >= currentCityCount || dest>= currentCityCount)
    {
        printf("invalid index!");
        return;
    }

    if(src==dest)
    {
        printf("Same city, therefore destination is 0.\n");
        return;
    }

    printf("Enter distance between %s and %s(km): ",cities[src],cities[dest]);
    if(scanf("%d",&dist)!=1)
    {
        while(getchar()!='\n');
        printf("Invalid distance.\n");
        return;
    }

    if(dist<=0)
    {
        printf("Distance cannot be negative!\n");
        return;
    }

    distance[src][dest]=dist;
    distance[dest][src]=dist;

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

void saveRoutesToFile(char path[])
{
    FILE *fp = fopen(path, "w");
    if (fp == NULL){
        printf("Error: cannot open file to write!\n");
    return;
    }
    fprintf(fp, "%d\n", currentCityCount);

    for(int i = 0; i<currentCityCount; i++)
    {
        fprintf(fp, "%s\n", cities[i]);
    }

    for (int i = 0; i < currentCityCount; i++) {
        for (int j = 0; j < currentCityCount; j++) {
            fprintf(fp, "%d ", distance[i][j]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("Data saved successfully to %s!\n", path);
}

void loadRoutesFromFile(char path[]) {
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("No saved data found (file missing), starting from zero.\n");
        currentCityCount = 0;
        return;
    }
    fscanf(fp, "%d\n", &currentCityCount);

    for (int i = 0; i < currentCityCount; i++) {
        fgets(cities[i], MAX_NAME_LEN, fp);

        int len = strlen(cities[i]);
        if (len > 0 && cities[i][len - 1] == '\n')
            cities[i][len - 1] = '\0';
    }
    for (int i = 0; i < currentCityCount; i++) {
        for (int j = 0; j < currentCityCount; j++) {
            fscanf(fp, "%d", &distance[i][j]);
        }
    }

    fclose(fp);
    printf("Data loaded successfully from %s!\n", path);
}
