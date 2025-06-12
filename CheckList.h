#ifndef CHECKLIST_H
#define CHECKLIST_H

#include "dynamic.h"
#include "checkListItem.h"
#include "String.h"

class CheckList {
	Dynamic_array<CheckListItem*>checklist;
private:
	void addItem(String);
	void markItemComplete(int);
	void displayCheckList();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif // !CHECKLIST_H
