#ifndef SHIPMENTS_H
#define SHIPMENTS_H

#define MAX_CITIES 30
#define MAX_NAME_LEN 50

char cities[MAX_CITIES][MAX_NAME_LEN];
int distance[MAX_CITIES][MAX_CITIES];
int currentCityCount;

void addCity();
void renameCity();
void removeCity();
void displayCities();
void editDistance();
void displayDistanceTable();

void saveRoutesToFile(char path[]);
void loadRoutesFromFile(char path[]);
void findLeastDistanceRoute();
int getMinDistanceIndex(double dist[], int visited[], int currentCityCount);

void findLeastCostRoute();
int getNameCostIndex(double cost[], int visited[], int currentCityCount);

#endif
