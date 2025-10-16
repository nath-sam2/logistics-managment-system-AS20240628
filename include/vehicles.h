#ifndef VEHICLES_H
#define VEHICLES_H

#define MAX_VEHICLES 3
#define MAX_VEHICLE_NAME 30

char vehicleNames[MAX_VEHICLES][MAX_VEHICLE_NAME];
double vehicleRatePerKm[MAX_VEHICLES];
double vehicleCapacity[MAX_VEHICLES];
double vehicleSpeed[MAX_VEHICLES];
double vehicleFuelEfficiency[MAX_VEHICLES];

void initializeVehicles();
void displayVehicles();

#endif
