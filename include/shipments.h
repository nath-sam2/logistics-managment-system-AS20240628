#ifndef SHIPMENTS_H_INCLUDED
#define SHIPMENTS_H_INCLUDED

#define MAX_CITIES 30
#define MAX_NAME_LEN 50

char cities[MAX_CITIES][MAX_NAME_LEN];
int currentCityCount;

void addCity();
void renameCity();
void removeCity();
void displayCities();

#endif // SHIPMENTS_H_INCLUDED
