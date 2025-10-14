#ifndef SHIPMENTS_H_INCLUDED
#define SHIPMENTS_H_INCLUDED

#define MAX_CITIES 30

void addCity();
void renameCity();
void removeCity();
void displayCities();
void editDistance();
void displayDistanceTable();
void saveRoutesToFile(char path[]);
int loadDeliveriesFromFile(char path[]);

#endif // SHIPMENTS_H_INCLUDED
