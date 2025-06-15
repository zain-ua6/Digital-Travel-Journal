#ifndef LOCATION_H
#define LOCATION_H

#include "String.h"
#include "Weather.h"
#include "Activity.h"
#include "dynamic.h"

class Location {
	string city;
	string country;
	string arrivalDate;
	string departureDate;
	Weather* weather;
	Dynamic_array<Activity*>activities;
private:
	void addActivity(Activity*);
	void setWeather(const Weather&);
	void displayLocation();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif
