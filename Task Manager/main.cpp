#include <iostream>
#include "interface.h"
int main()
{
    Manager manager;
    std::cout << "Hello World!\n";
    
    IF_add(manager);
    showTasks(manager);
    IF_edit(manager);
    showTasks(manager);

    
}
