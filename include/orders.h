#ifndef ORDERS_H
#define ORDERS_H

#define MAX_DELIVERIES 50
#define MAX_LENGTH 50

int currentDeliveryCount;
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

void createDelivery();
void listDelivery();
void calculateDeliveryCost(int index);

#endif
