# logistics-managment-system-AS20240628

### Developer: N.R.Perera
### Course: CSC 1012 - Introduction to Computer Programming
### Year: 2025

---

## Overview
This program simulates a logistics company system that manages cities, vehicles, and deliveries.
It calculates delivery cost, time, fuel usage, and profits based on distance and vehicle type.

---

## Features
1. City Management
2. Distance Management
3. Vehicle Management
4. Delivery Creation
5. Delivery Reports
6. Route Optimization(Shortest & Least-Cost)
7. Performance Reports
8. Data Maintenance(Clear or Reset Data)
9. Automatic File Backup
10. System Summary Report

---

### Technologies Used
- Language: C (Code::Blocks)
- File Handaling
- Modular Programming
- Menu-driven structure

### Folder Structure

## Project Structure

```text
logistics-management-system/
│
├── src/ # All .c source files (implementation)
│   ├── shipments.c # Handles cost, time, fuel, and backups
│   ├── vehicles.c # Manages vehicle data (rate, speed, efficiency)
│   └── orders.c # Manages deliveries and file handling
│
├── include/ # Header files (function prototypes and globals)
│   ├── shipments.h
│   ├── vehicles.h
│   └── orders.h
│
├── data/ # All data files (input/output and backups)
│   ├── cities.txt # Stores city names
│   ├── routes.txt # Stores shortest and least-cost path
│   ├── distances.txt # Stores distance matrix
│   ├── deliveries.txt # Stores delivery records
│   ├── cities_backup.txt # Backup of cities.txt
│   ├── distances_backup.txt # Backup of distances.txt
│   ├── deliveries_backup.txt # Backup of deliveries.txt
│   └── system_summary.txt # Auto-generated performance summary
│
├── LogisticsManagementSystem.c # Main program (menu + control flow)
├── README.md # Documentation / project overview
├── .gitignore # Git exclusions (build files, executables)
└── project.cbp # (Optional) Code::Blocks project file
