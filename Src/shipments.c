#include <stdio.h>
#include <string.h>
#include <float.h>
#include <stdbool.h>
#include "../include/shipments.h"
#include "../include/vehicles.h"

#define FUEL_PRICE 310.0

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

    printf("Enter source city index(0 to %d): ",currentCityCount-1);
    if(scanf("%d",&src)!=1)
    {
        while(getchar()!='\n');
        printf("Invalid input.\n");
        return;
    }

    printf("Enter destination city index(0 to %d): ",currentCityCount-1);
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

    printf("====================Distance Table (km)====================\n");
    printf("%12s\t", "  ");

    for(int i = 0; i<currentCityCount; i++)
    {
        printf("%10s\t",cities[i]);
    }
    printf("\n");

    for (int i = 0; i<currentCityCount; i++)
    {
        printf("%10s\t",cities[i]);
        for(int j = 0; j<currentCityCount; j++)
        {
            printf("%10d\t",distance[i][j]);
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

int getMinDistanceIndex(double dist[], int visited[], int currentCityCount)
{
    double min = DBL_MAX;
    int minIndex = -1;

    for (int i = 0; i < currentCityCount; i++)
    {
        if (!visited[i] && dist[i] <= min)
        {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void findLeastDistanceRoute()
{
    if (currentCityCount < 2)
        {
        printf("Two cities required.\n");
        return;
    }

    displayCities();

    int src, dest;
    printf("Enter source city index: ");
    scanf("%d", &src);
    printf("Enter destination city index: ");
    scanf("%d", &dest);

    if (src < 0 || src >= currentCityCount || dest < 0 || dest >= currentCityCount || src == dest) {
        printf("Invalid selection.\n");
        return;
    }

    double dist[100];
    int visited[100];
    int parent[100];

    for (int i = 0; i < currentCityCount; i++)
        {
        dist[i] = DBL_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < currentCityCount - 1; count++) {
        int u = getMinDistanceIndex(dist, visited, currentCityCount);
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < currentCityCount; v++) {
            if (!visited[v] && distance[u][v] > 0 &&
                dist[u] + distance[u][v] < dist[v]) {
                dist[v] = dist[u] + distance[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[dest] == DBL_MAX) {
        printf("No route found between %s and %s.\n", cities[src], cities[dest]);
        return;
    }

    printf("\n===== Least-Distance Route =====\n");
    printf("From: %s\n", cities[src]);
    printf("To: %s\n", cities[dest]);
    printf("Shortest Distance: %.2f km\n", dist[dest]);

    printf("Route: ");
    int path[100];
    int count = 0;
    int current = dest;
    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", cities[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\n=================================\n");
}

int getMinCostIndex(double cost[], int visited[], int currentCityCount)
{
    double min = DBL_MAX;
    int minIndex = -1;
    for (int i = 0; i < currentCityCount; i++) {
        if (!visited[i] && cost[i] < min) {
            min = cost[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void findLeastCostRoute() {
    if (currentCityCount < 2) {
        printf("Two cities required.\n");
        return;
    }

    displayCities();
    int src, dest;
    printf("Enter source city index: ");
    scanf("%d", &src);
    printf("Enter destination city index: ");
    scanf("%d", &dest);

    if (src < 0 || src >= currentCityCount || dest < 0 || dest >= currentCityCount || src == dest) {
        printf("Invalid city selection.\n");
        return;
    }

    displayVehicles();
    int vehicle;
    printf("Enter vehicle index (0-%d): ", MAX_VEHICLES - 1);
    scanf("%d", &vehicle);

    if (vehicle < 0 || vehicle >= MAX_VEHICLES) {
        printf("Invalid selection.\n");
        return;
    }

    double rate = vehicleRatePerKm[vehicle];
    double efficiency = vehicleFuelEfficiency[vehicle];

    double cost[100], dist[100];
    int visited[100], parent[100];

    for (int i = 0; i < currentCityCount; i++) {
        cost[i] = DBL_MAX;
        dist[i] = DBL_MAX;
        visited[i] = 0;
        parent[i] = -1;
    }

    cost[src] = 0;
    dist[src] = 0;

    for (int count = 0; count < currentCityCount - 1; count++) {
        int u = getMinCostIndex(cost, visited, currentCityCount);
        if (u == -1)
            break;
        visited[u] = 1;

        for (int v = 0; v < currentCityCount; v++) {
            if (!visited[v] && distance[u][v] > 0) {
                double D = distance[u][v];

                double deliveryCost = D * rate;
                double fuelCost = (D / efficiency) * FUEL_PRICE;
                double totalEdgeCost = deliveryCost + fuelCost;

                if (cost[u] + totalEdgeCost < cost[v]) {
                    cost[v] = cost[u] + totalEdgeCost;
                    dist[v] = dist[u] + D;
                    parent[v] = u;
                }
            }
        }
    }

    if (cost[dest] == DBL_MAX) {
        printf("No route found between %s and %s.\n", cities[src], cities[dest]);
        return;
    }

    printf("\n===== Least-Cost Route =====\n");
    printf("From: %s\n", cities[src]);
    printf("To: %s\n", cities[dest]);
    printf("Vehicle: %s\n", vehicleNames[vehicle]);
    printf("Total Distance: %.2f km\n", dist[dest]);
    printf("Estimated Cost: %.2f LKR\n", cost[dest]);

    printf("Route: ");
    int path[100];
    int count = 0;
    int current = dest;
    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", cities[path[i]]);
        if (i != 0) printf(" -> ");
    }
    printf("\n=================================\n");
}

void saveCitiesToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: Unable to save city data.\n");
        return;
    }

    fprintf(fp, "%d\n", currentCityCount);
    for (int i = 0; i < currentCityCount; i++)
        {
        fprintf(fp, "%s\n", cities[i]);
        }

    fclose(fp);
    printf("Cities saved successfully to %s.\n", filename);
}

void loadCitiesFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
        {
        printf("No existing city data found. Starting fresh.\n");
        return;
        }

    fscanf(fp, "%d\n", &currentCityCount);
    for (int i = 0; i < currentCityCount; i++)
        {
        fgets(cities[i], 50, fp);
        cities[i][strcspn(cities[i], "\n")] = '\0'; // remove newline
        }

    fclose(fp);
    printf("Cities loaded successfully from %s.\n", filename);
}

void saveDistancesToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
        {
        printf("Error: Unable to save distances.\n");
        return;
        }

    fprintf(fp, "%d\n", currentCityCount);
    for (int i = 0; i < currentCityCount; i++)
        {
        for (int j = 0; j < currentCityCount; j++)
           {
            fprintf(fp, "%.2f ", distance[i][j]);
           }
        fprintf(fp, "\n");
        }

    fclose(fp);
    printf("Distances saved successfully to %s.\n", filename);
}

void loadDistancesFromFile(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No existing distance data found. Starting fresh.\n");
        return;
    }

    fscanf(fp, "%d\n", &currentCityCount);
    for (int i = 0; i < currentCityCount; i++)
        {
        for (int j = 0; j < currentCityCount; j++)
          {
            fscanf(fp, "%lf", &distance[i][j]);
          }
        }

    fclose(fp);
    printf("Distances loaded successfully from %s.\n", filename);
}
