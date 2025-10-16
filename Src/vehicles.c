#include <stdio.h>
#include <string.h>
#include "../include/vehicles.h"

char vehicleNames[MAX_VEHICLES][MAX_VEHICLE_NAME];
double vehicleRatePerKm[MAX_VEHICLES];
double vehicleCapacity[MAX_VEHICLES];
double vehicleSpeed[MAX_VEHICLES];
double vehicleFuelEfficiency[MAX_VEHICLES];

void initializeVehicles()
{
    strcpy(vehicleNames[0], "Van");
    vehicleRatePerKm[0] = 30.0;
    vehicleCapacity[0] = 1000.0;
    vehicleSpeed[0] = 60.0;
    vehicleFuelEfficiency[0] = 12.0;

    strcpy(vehicleNames[1], "Truck");
    vehicleRatePerKm[1] = 40.0;
    vehicleCapacity[1] = 5000.0;
    vehicleSpeed[1] = 50.0;
    vehicleFuelEfficiency[1] = 6.0;

    strcpy(vehicleNames[2], "Lorry");
    vehicleRatePerKm[2] = 80.0;
    vehicleCapacity[2] = 10000.0;
    vehicleSpeed[2] = 45.0;
    vehicleFuelEfficiency[2] = 4.0;
}

void displayVehicles()
 {
    printf("\n======= Vehicle Information =======\n");
    printf("%-5s %-20s %-10s %-12s %-12s %-12s\n", "No.", "Vehicle", "Rate/km", "Capacity(kg)", "Speed(km/h)", "Fuel Efficiency(km/l)");

    for (int i = 0; i < MAX_VEHICLES; i++) {
        printf("%-5d %-20s %-10.2f %-12.2f %-12.2f %-12.2f\n",
               i, vehicleNames[i], vehicleRatePerKm[i],
               vehicleCapacity[i], vehicleSpeed[i], vehicleFuelEfficiency[i]);
    }
}
