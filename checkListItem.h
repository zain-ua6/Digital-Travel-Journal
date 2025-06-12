#ifndef CheckListItem_H
#define CheckListItem_H

#include "String.h"

class CheckListItem {
	String item;
	bool isCompleted;
private:
	void markComplete();
	bool getStatus();
	String getItem();
};

#endif // !CheckListItem_H
