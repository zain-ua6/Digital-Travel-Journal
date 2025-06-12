#ifndef USER_H
#define USER_H

#include "String.h"
#include "dynamic.h"
#include "Trip.h"

class User {
	String username;
	String email;
	Dynamic_array<Trip*>trips;
private:
	void createTrip(Trip*);
	void displayAllTrips();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
};

#endif