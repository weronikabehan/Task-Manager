#ifndef INTERFACE_H
#define INTERFACE_H

#include "manager.h"

int validChoice(int min, int max);

void showTasks(Manager& manager);
std::string chooseExistingCategory(Manager& manager);

void IF_add(Manager& manager);
void IF_delete(Manager& manager);
void IF_edit(Manager& manager);
void IF_done(Manager& manager);
void IF_getDate(Manager& manager, int index);

#endif