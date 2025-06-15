#ifndef USER_H
#define USER_H

#include <string>
#include "dynamic.h"
#include "Trip.h"

class User {
	string username;
	string email;
	Dynamic_array<Trip*>trips;
private:
	void createTrip(Trip*);
	void displayAllTrips();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif