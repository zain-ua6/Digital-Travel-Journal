#ifndef CHECKLIST_H
#define CHECKLIST_H

#include "dynamic.h"
#include "checkListItem.h"
#include <string>

class CheckList {
	Dynamic_array<CheckListItem*>checklist;
private:
	void addItem(string);
	void markItemComplete(int);
	void displayCheckList();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif 
