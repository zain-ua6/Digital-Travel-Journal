#ifndef ACTIVITY_H
#define ACTIVITY_H

#include "Trip entry.h"
#include "String.h"
#include "Date.h"

class Activity : public TripEntry {
	String name;
	String type;
	String description;
	Date date;
};

#endif