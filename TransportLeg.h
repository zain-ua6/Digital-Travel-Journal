#ifndef TRANSPORTLEG_H
#define TRANSPORTLEG_H

#include <string>
#include <fstream>
using namespace std;

class TransportLeg {
	string fromLocation;
	string toLocation;
	string transportMode;
	float distance;
	string travelTime;
private:
	void display();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif
