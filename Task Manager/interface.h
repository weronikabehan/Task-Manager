#ifndef INTERFACE_H
#define INTERFACE_H

#include "manager.h"

int validChoice(int min, int max);

void showTasks(Manager& manager);

void IF_add(Manager& manager);
void IF_delete(Manager& manager);

#endif