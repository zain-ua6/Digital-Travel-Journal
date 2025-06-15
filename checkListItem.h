#ifndef CheckListItem_H
#define CheckListItem_H

#include <string>

class CheckListItem {
	string item;
	bool isCompleted;
private:
	void markComplete();
	bool getStatus();
	string getItem();
};

#endif
