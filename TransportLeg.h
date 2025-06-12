#ifndef TRANSPORTLEG_H
#define TRANSPORTLEG_H

#include "String.h"
#include <fstream>
using namespace std;

class TransportLeg {
	String fromLocation;
	String toLocation;
	String transportMode;
	float distance;
	String travelTime;
private:
	void display();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif // !TRANSPORTLEG_H
