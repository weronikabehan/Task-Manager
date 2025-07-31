#include <iostream>
#include "interface.h"
#include "operations.h"
int main() {
    int choice;
    Manager manager;
    Operation operation(manager);

    operation.load("data.txt");
    operation.autoSave("data.txt");

    do {
        showMenu();

        try {
            choice = validChoice(0, 5);
        } catch(std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

        switch (choice) {
        case 1: IF_add(manager); break;
        case 2: IF_delete(manager); break;
        case 3: showTasks(manager); break;
        case 4: IF_done(manager); break;
        case 5: IF_edit(manager); break;
        case 0: std::cout << "\n\nGoodbye!";
        }

    } while (choice != 0);

    operation.stopAutoSave();
}
