#include "manager.h"

void Manager::changeNameORDesc(int index, int what, const std::string& name) {
	(what == 1) ? getVec().at(index)->setName(name) : getVec().at(index)->setDescription(name);
}

void Manager::changePriority(int index, int what) {
	switch (what) {
	case 1: getVec().at(index)->setPriority(prio::ASAP); break;
	case 2: getVec().at(index)->setPriority(prio::Later); break;
	case 3: getVec().at(index)->setPriority(prio::Whenever); break;
	}
}

void Manager::changeCategory(int index, const std::string& category) { getVec().at(index)->setCategory(category); }

void Manager::changeDone(int index) { 
	(getVec().at(index)->getDone() == true) ? getVec().at(index)->setDone(false) : getVec().at(index)->setDone(true);
}

void Manager::stringToTP(int day, int month, int year, int hour, int minute) {

}