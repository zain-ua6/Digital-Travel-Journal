#ifndef TRIP_H
#define TRIP_H

#include "String.h"
#include "dynamic.h"
#include "CheckList.h"
#include "Note.h"
#include "Expense.h"
#include "Location.h"
#include "TransportLeg.h"

enum TripStatus{Completed, Current, Planned};

class Trip {
	String title;
	String startDate;
	String endDate;
	String travelBuddy;
	TripStatus status;
	CheckList checklist;
	Dynamic_array<Note*> notes;
	Dynamic_array<Expense*> expenses;
	Dynamic_array<Location*> locations;
	Dynamic_array<TransportLeg*> legs;
private:
	void addNote(Note*);
	void addExpense(Expense*);
	void addLocation(Location*);
	void addTransportLeg(TransportLeg*);
	void updateStatus(TripStatus);
	void displayTripSummary();
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);

};

#endif