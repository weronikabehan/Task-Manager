#include "interface.h"
#include <iostream>


int validChoice(int min, int max) {
    int choice;
    while (true) {
        if (std::cin >> choice) {
            if (choice >= min && choice <= max) return choice;
            else throw std::out_of_range ("Your choice is out of range. Please try again.");
        }
        else {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            throw std::invalid_argument("Your choice should be a number. Please try again.");
        }
    }
}

void showTasks(Manager& manager) {

    std::cout << "=====================================================\n";

    if (manager.getVec().empty()) {
        std::cout << "\nNo tasks available.\n";
    }
    else {
        std::cout << "\nList of tasks:\n\n";

        int i = 0;
        for (const auto& t : manager.getVec()) {
            std::cout << i++ << ". " << t->getName()
                << " [ " << (t->getDone() ? "Done" : "Not done") << " ] \n"
                << "     Description: " << t->getDescription() << "\n"
                << "     Category   : " << t->getCategory() << "\n"
                << "     Priority   : " << t->priorityToString(t->getPriority()) << "\n\n";
        }
    }

    std::cout << "=====================================================\n\n";
}

void IF_add(Manager& manager) {
	std::string name;
	std::cout << "Name of your new task: ";
	std::getline(std::cin, name);
	
	if (name.empty()) throw std::invalid_argument("Name can not be empty!");

	manager.addTask(name);
	std::cout << "\nTask '" << name << "' successfully added.\n\n";
}

void IF_delete(Manager& manager) {
    int choice;
    int size = manager.getVec().size();
    showTasks(manager);

    std::cout << "\n\nChoose task to delete: ";
    try { choice = validChoice(1, size); }
    catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; return; }

    choice--;
    std::string name = manager.getVec().at(choice)->getName();

    manager.getVec().erase(manager.getVec().begin() + choice);
    std::cout << "\nTask '" << name << "' deleted.\n\n";
}