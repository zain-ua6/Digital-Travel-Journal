#ifndef EXPENSE_H
#define EXPENSE_H

#include "Trip entry.h"
#include <string>
#include "Date.h"
#include <fstream>
using namespace std;

class Expense : public TripEntry {
	double amount;
	string category;
	string description;
	Date date;

private:
	void display();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif