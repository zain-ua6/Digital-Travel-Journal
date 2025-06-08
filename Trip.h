#ifndef TRIP_H
#define TRIP_H

#include "String.h"
#include "dynamic.h"

enum TripStatus{Completed, Current, Planned};

class Trip {
	String title;
	String startDate;
	String endDate;
	String travelBuddy;
	TripStatus status;
};

#endif