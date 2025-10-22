#include <stdio.h>
#include <string.h>
#include "../include/orders.h"
#include "../include/shipments.h"
#include "../include/vehicles.h"

#define FUEL_PRICE 310.0

int currentDeliveryCount=0;
int deliverySource[MAX_DELIVERIES];
int deliveryDestination[MAX_DELIVERIES];
int deliveryVehicle[MAX_DELIVERIES];
double deliveryWeight[MAX_DELIVERIES];
double deliveryDistance[MAX_DELIVERIES];
double deliveryFuelUsed[MAX_DELIVERIES];
double deliveryFuelCost[MAX_DELIVERIES];
double deliveryTime[MAX_DELIVERIES];
double deliveryBaseCost[MAX_DELIVERIES];
double deliveryTotalCost[MAX_DELIVERIES];
double deliveryProfit[MAX_DELIVERIES];
double deliveryCharge[MAX_DELIVERIES];
char customerNames[MAX_DELIVERIES][MAX_LENGTH];


void createDelivery() {
    if (currentCityCount < 2) {
        printf("At least 2 cities are required to create a delivery.\n");
        return;
    }

    if (currentDeliveryCount >= MAX_DELIVERIES) {
        printf("Delivery limit reached!\n");
        return;
    }

    printf("\n--- Create New Delivery ---\n");
    printf("Enter customer name: ");
    scanf(" %s", customerNames[currentDeliveryCount]);

    displayCities();
    printf("Enter source city index: ");
    scanf("%d", &deliverySource[currentDeliveryCount]);

    printf("Enter destination city index: ");
    scanf("%d", &deliveryDestination[currentDeliveryCount]);

    if (deliverySource[currentDeliveryCount] < 0 || deliverySource[currentDeliveryCount] >= currentCityCount ||
        deliveryDestination[currentDeliveryCount] < 0 || deliveryDestination[currentDeliveryCount] >= currentCityCount ||
        deliverySource[currentDeliveryCount] == deliveryDestination[currentDeliveryCount])
        {
        printf("Invalid city selection!\n");
        return;
        }

    displayVehicles();
    printf("Enter vehicle index (0-%d): ", MAX_VEHICLES - 1);
    scanf("%d", &deliveryVehicle[currentDeliveryCount]);

    if (deliveryVehicle[currentDeliveryCount] < 0 || deliveryVehicle[currentDeliveryCount] >= MAX_VEHICLES)
        {
        printf("Invalid vehicle selection!\n");
        return;
        }

    printf("Enter delivery weight (kg): ");
    scanf("%lf", &deliveryWeight[currentDeliveryCount]);

    if (deliveryWeight[currentDeliveryCount] > vehicleCapacity[deliveryVehicle[currentDeliveryCount]])
        {
        printf("Weight exceeds vehicle capacity! Delivery cannot be created.\n");
        return;
        }

    calculateDeliveryCost(currentDeliveryCount);

    printf("\nDelivery created successfully!\n");
    printf("--------------------------------------\n");
    printf("Distance (km): %.2f\n", deliveryDistance[currentDeliveryCount]);
    printf("Time (hrs): %.2f\n", deliveryTime[currentDeliveryCount]);
    printf("Fuel Used (L): %.2f\n", deliveryFuelUsed[currentDeliveryCount]);
    printf("Fuel Cost (LKR): %.2f\n", deliveryFuelCost[currentDeliveryCount]);
    printf("Base Delivery Cost: %.2f\n", deliveryBaseCost[currentDeliveryCount]);
    printf("Total Operational: %.2f\n", deliveryTotalCost[currentDeliveryCount]);
    printf("Profit (25%%): %.2f\n", deliveryProfit[currentDeliveryCount]);
    printf("Customer Charge: %.2f\n", deliveryCharge[currentDeliveryCount]);
    printf("--------------------------------------\n");

    currentDeliveryCount++;
}

void calculateDeliveryCost(int i)
{
    int src = deliverySource[i];
    int dest = deliveryDestination[i];
    int vehicle = deliveryVehicle[i];
    double W = deliveryWeight[i];
    double D = distance[src][dest];
    double R = vehicleRatePerKm[vehicle];
    double S = vehicleSpeed[vehicle];
    double E = vehicleFuelEfficiency[vehicle];
    double F = FUEL_PRICE;

    deliveryDistance[i] = D;
    deliveryTime[i] = D / S;
    deliveryFuelUsed[i] = D / E;
    deliveryFuelCost[i] = deliveryFuelUsed[i] * F;

    deliveryBaseCost[i] = D * R * (1 + W / 10000.0);
    deliveryTotalCost[i] = deliveryBaseCost[i] + deliveryFuelCost[i];
    deliveryProfit[i] = deliveryBaseCost[i] * 0.25;
    deliveryCharge[i] = deliveryTotalCost[i] + deliveryProfit[i];
}

void listDelivery()
{
if (currentDeliveryCount == 0) {
        printf("No deliveries yet.\n");
        return;
    }

    printf("\n======= Delivery Summary =======\n");
    printf("%-5s %-15s %-15s %-10s %-10s %-10s %-10s\n",
           "No.", "Customer", "Vehicle", "Source", "Dest", "Cost(LKR)", "Charge(LKR)");

    for (int i = 0; i < currentDeliveryCount; i++)
        {
        printf("%-5d %-15s %-15s %-10s %-10s %-10.2f %-10.2f\n",
               i, customerNames[i],
               vehicleNames[deliveryVehicle[i]],
               cities[deliverySource[i]],
               cities[deliveryDestination[i]],
               deliveryTotalCost[i],
               deliveryCharge[i]);
        }
}

void saveDeliveriesToFile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error!\n");
        return;
    }

    fprintf(fp, "%d\n", currentDeliveryCount);
    for (int i = 0; i < currentDeliveryCount; i++) {
        fprintf(fp, "%s|%d|%d|%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f\n",
                customerNames[i],
                deliverySource[i],
                deliveryDestination[i],
                deliveryVehicle[i],
                deliveryWeight[i],
                deliveryDistance[i],
                deliveryFuelUsed[i],
                deliveryFuelCost[i],
                deliveryTime[i],
                deliveryBaseCost[i],
                deliveryTotalCost[i],
                deliveryProfit[i],
                deliveryCharge[i]);
    }

    fclose(fp);
    printf("Deliveries saved to file successfully.\n");
}

void loadDeliveriesFromFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No existing delivery file found.\n");
        return;
    }

    fscanf(fp, "%d\n", &currentDeliveryCount);
    for (int i = 0; i < currentDeliveryCount; i++) {
        fscanf(fp, "%s|%d|%d|%d|%lf|%lf|%lf|%lf|%lf|%lf|%lf|%lf|%lf\n",
               customerNames[i],
               &deliverySource[i],
               &deliveryDestination[i],
               &deliveryVehicle[i],
               &deliveryWeight[i],
               &deliveryDistance[i],
               &deliveryFuelUsed[i],
               &deliveryFuelCost[i],
               &deliveryTime[i],
               &deliveryBaseCost[i],
               &deliveryTotalCost[i],
               &deliveryProfit[i],
               &deliveryCharge[i]);
    }

    fclose(fp);
    printf("Loaded %d deliveries from file.\n", currentDeliveryCount);
}

void showReports() {
    if (currentDeliveryCount == 0) {
        printf("\nNo deliveries have been completed yet.\n");
        return;
    }

    double totalDistance = 0.0;
    double totalTime = 0.0;
    double totalRevenue = 0.0;
    double totalProfit = 0.0;

    double longestDistance = deliveryDistance[0];
    double shortestDistance = deliveryDistance[0];
    int longestIndex = 0;
    int shortestIndex = 0;

    for (int i = 0; i < currentDeliveryCount; i++) {
        totalDistance += deliveryDistance[i];
        totalTime += deliveryTime[i];
        totalRevenue += deliveryCharge[i];
        totalProfit += deliveryProfit[i];

        if (deliveryDistance[i] > longestDistance) {
            longestDistance = deliveryDistance[i];
            longestIndex = i;
        }

        if (deliveryDistance[i] < shortestDistance) {
            shortestDistance = deliveryDistance[i];
            shortestIndex = i;
        }
    }

    double avgTime = totalTime / currentDeliveryCount;

    printf("\n========== PERFORMANCE REPORTS ==========\n");
    printf("Total Deliveries Completed : %d\n", currentDeliveryCount);
    printf("Total Distance Covered : %.2f km\n", totalDistance);
    printf("Average Delivery Time : %.2f hours\n", avgTime);
    printf("Total Revenue Earned : %.2f LKR\n", totalRevenue);
    printf("Total Profit Gained : %.2f LKR\n", totalProfit);
    printf("-----------------------------------------\n");
    printf("Longest Route Completed:\n");
    printf(" Customer: %s\n", customerNames[longestIndex]);
    printf(" From %s -> %s (%.2f km)\n",
           cities[deliverySource[longestIndex]],
           cities[deliveryDestination[longestIndex]],
           longestDistance);
    printf("-----------------------------------------\n");
    printf("Shortest Route Completed:\n");
    printf(" Customer: %s\n", customerNames[shortestIndex]);
    printf(" From %s -> %s (%.2f km)\n",
           cities[deliverySource[shortestIndex]],
           cities[deliveryDestination[shortestIndex]],
           shortestDistance);
    printf("=========================================\n");
}

void clearAllDeliveries()
{
    char confirm;
    printf("\nWARNING: This will permanently delete all delivery records.\n");
    printf("Are you sure you want to continue? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y')
    {
        FILE *fp = fopen("data/deliveries.txt", "w");
        if (fp == NULL)
        {
            printf("Error: Unable to access deliveries.txt file.\n");
            return;
        }
        fclose(fp);

        currentDeliveryCount = 0;
        for (int i = 0; i < 100; i++)
        {
            strcpy(customerNames[i], "");
            deliveryDistance[i] = 0;
            deliveryTime[i] = 0;
            deliveryCharge[i] = 0;
            deliveryProfit[i] = 0;
        }

        printf("All delivery data cleared successfully.\n");
    }
    else
    {
        printf("Operation canceled. No data was deleted.\n");
    }
}

void dataMaintenanceMenu()
{
    int option;
    printf("\n========== DATA MAINTENANCE ==========\n");
    printf("1. Clear all delivery data\n");
    printf("0. Return to main menu\n");
    printf("Enter your choice: ");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            clearAllDeliveries();
            break;
        case 0:
            printf("Returning to main menu.\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
}
