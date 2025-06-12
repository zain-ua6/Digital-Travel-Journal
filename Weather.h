#ifndef WEATHER_H
#define WEATHER_H

#include "String.h"
#include <fstream>
using namespace std;

class Weather {
	String date;
	float temperature;
	String summary;
private:
	void display();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif // !WEATHER_H
