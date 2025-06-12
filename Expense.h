#ifndef EXPENSE_H
#define EXPENSE_H

#include "Trip entry.h"
#include "String.h"
#include "Date.h"
#include <fstream>
using namespace std;

class Expense : public TripEntry {
	double amount;
	String category;
	String description;
	Date date;

private:
	void display();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif