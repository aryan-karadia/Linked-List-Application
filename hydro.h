// hydro.h

#ifndef HYDRO_H
#define HYDRO_H

#include "list.h"

void displayHeader();

void pressEnter();

int readData(const char *filename, FlowList &list);

int menu();

void displayData(const FlowList &list);

void addData(FlowList &list, int count);

void removeData(FlowList &list);

int averageData(const FlowList &list);

void saveData(const FlowList &list);

#endif