#ifndef ORDERS_H_INCLUDED
#define ORDERS_H_INCLUDED

#define MAX_DELIVERIES 50

void createDelivery();
void listDelivery();
void saveDeliveriesToFile(char path[]);
int loadDeliveriesFromFile(char path[]);
void generateReports();
double findLeastDistance(int src, int destination);

#endif // ORDERS_H_INCLUDED
