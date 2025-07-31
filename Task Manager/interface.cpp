#include "interface.h"
#include "utils.h"
#include <iostream>
#include <sstream>

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

        int i = 1;
        for (const auto& t : manager.getVec()) {
            std::cout << i++ << ". " << t->getName()
                << " [ " << (t->getDone() ? "Done" : "Not done") << " ] \n"
                << "     Description: " << t->getDescription() << "\n"
                << "     Category   : " << t->getCategory() << "\n"
                << "     Priority   : " << priorityToString(t->getPriority()) << "\n"
                << "     Deadline in: " << deadlineToString(t->getDeadline())
                << "\n\n";
        }
    }

    std::cout << "=====================================================\n\n";
}

std::string chooseExistingCategory(Manager& manager) {
    std::vector<std::string> categories;
    for (auto& i : manager.getVec()) if (i->getCategory() != "--") categories.emplace_back(i->getCategory());

    if (categories.empty()) {
        std::cout << "\n\nThere is no categories available.\n\n";
        return "--";
    }
    else {
        std::cout << "\n\nAvailable categories:\n";
        int j = 1;
        for (std::string i : categories) std::cout << "[" << j++ << "] " << i << '\n';
        std::cout << '\n';

        int choice;
        std::cout << "Select which category do you choose: ";
        try { choice = validChoice(1, categories.size()); }
        catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

        choice--;
        std::string chosen = categories.at(choice);
        return chosen;
    }
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
    std::cout << "[0] Return";

    std::cout << "\n\nChoose task to delete: ";

    try { choice = validChoice(0, size); }
    catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

    if (choice == 0) return;

    choice--;
    std::string name = manager.getVec().at(choice)->getName();

    manager.deleteTask(choice);
    std::cout << "\nTask '" << name << "' deleted.\n\n";
}

void IF_edit(Manager& manager) {
    int index;
    int choice1, choice2;
    int size = manager.getVec().size();
    showTasks(manager);
    std::cout << "[0] Return";

    std::cout << "\n\nChoose task to edit: ";

    try { index = validChoice(0, size); }
    catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

    if (index == 0) return;

    index--;
    std::string name = manager.getVec().at(index)->getName();
    std::cout << "\n    [1] Change name\n    [2] Change description\n    [3] Change category\n    [4] Change priority\n    " 
        << "[5] Deadline\n    [0] Return\n    Your choice : ";
    try { choice1 = validChoice(0, 5); }
    catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }
    if (choice1 == 0) return;

    std::cout << "\n    [1] Edit\n    [2] Delete\n    [0] Return\n    Your choice: ";
    try { choice2 = validChoice(0, 2); }
    catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }
    if (choice2 == 0) return;


    switch (choice1) {
    case 1:
    case 2: {
        std::string x;
        if (choice2 == 1) {
            std::cout << "\nEnter new " << ((choice1 == 1) ? "name: " : "description: ");
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, x);
            manager.changeNameORDesc(index, choice1, x);
        }
        else {
            if (choice1 == 1) {
                int what;
                std::cout << "\nIf you delete a task name, that task will be completely deleted. Is that what you want?\n[1] Yes\n[2] No\nYour choice: ";

                try { what = validChoice(1, 2); }
                catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

                if (what == 1) manager.deleteTask(index);
                else return;
            }
            else manager.getVec()[index]->setDescription("--");
        }
        break;
    }
    case 3: {
        if (choice2 == 1) {
            int what;
            std::cout << "Do you want to:\n[1] Add to existing category\n[2] Create a new category\nYour choice: ";

            try { what = validChoice(1, 2); }
            catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

            if (what == 1) manager.changeCategory(index, chooseExistingCategory(manager));
            else if(what == 2) {
                std::string cat;
                std::cout << "\nEnter new category: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, cat);
                manager.changeCategory(index, cat);
            }
        }
        else manager.getVec().at(index)->setCategory("--");
        break;
    }
    case 4: {
        if (choice2 == 1) {
            int what;
            std::cout << "Choose the priority:\n[1] ASAP\n[2] Later\n[3] Whenever\nYour choice: ";

            try { what = validChoice(1, 3); }
            catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

            manager.changePriority(index, what);
        }
        else manager.getVec().at(index)->setPriority(prio::Whenever);
        break;
    }
    case 5: {
        if (choice2 == 1) IF_getDate(manager, index);
        else manager.getVec()[index]->setDeadline(system_clock::time_point{});
        break;
    }
    }
    std::cout << "\nTask '" << name << "' changed.\n\n";
}

void IF_done(Manager& manager) {
    int size = manager.getVec().size();
    int choice;
    showTasks(manager);
    std::cout << "[0] Return";
    std::cout << "\n\nSelect the task which readiness you want to change: ";

    try { choice = validChoice(0, size); }
    catch (std::exception& e) { std::cout << "Error: " << e.what() << '\n'; }

    if (choice == 0) return;
    choice--;
    manager.changeDone(choice);
    
    std::cout << "\nTask changed to " << ((manager.getVec()[choice]->getDone() == 1) ? "done" : "not done") << ".\n\n";
}

void IF_getDate(Manager& manager, int index) {
    std::string line;
    int day, month, year, hour, minute;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        std::cout << "\nEnter the deadline date in the format (DD-MM-YYYY,HH:MM): ";
        std::getline(std::cin, line);
        std::stringstream ss(line);
        std::string temp;

        try {
            std::getline(ss, temp, '-');
            day = std::stoi(temp);
            std::getline(ss, temp, '-');
            month = std::stoi(temp);
            std::getline(ss, temp, ',');
            year = std::stoi(temp);

            std::getline(ss, temp, ':');
            hour = std::stoi(temp);
            std::getline(ss, temp);
            minute = std::stoi(temp);

            if (day < 1 || day > 31) throw std::out_of_range("Invalid day");
            if (month < 1 || month > 12) throw std::out_of_range("Invalid month");
            if (year < 1900) throw std::out_of_range("Invalid year");
            if (hour < 0 || hour > 23) throw std::out_of_range("Invalid hour");
            if (minute < 0 || minute > 59) throw std::out_of_range("Invalid minute");

            break;
        }
        catch (const std::exception& e) {
            std::cerr << "Invalid input format or value: " << e.what() << ". Please try again.\n";
        }

    }
    manager.setTPfromSTR(day, month, year, hour, minute, index);
}
