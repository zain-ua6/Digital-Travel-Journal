#ifndef WEATHER_H
#define WEATHER_H

#include <string>
#include <fstream>
using namespace std;

class Weather {
	string date;
	float temperature;
	string summary;
private:
	void displayWeather();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif