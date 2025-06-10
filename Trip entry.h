#ifndef TRIPENTRY_H
#define TRIPENTRY_H

#include <fstream>
using namespace std;

class TripEntry {
public:
	void display();
	void saveTofile(ofstream&);
	void loadFromFile(ifstream&);
	virtual ~TripEntry();
};

#endif