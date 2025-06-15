#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "Trip entry.h"
#include <string>
#include "Date.h"

class Activity : public TripEntry {
	string name;
	string type;
	string description;
	Date date;
};

#endif