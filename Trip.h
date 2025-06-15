#ifndef TRIP_H
#define TRIP_H

#include <string>
#include "dynamic.h"
#include "CheckList.h"
#include "Note.h"
#include "Expense.h"
#include "Location.h"
#include "TransportLeg.h"

enum TripStatus{Completed, Current, Planned};

class Trip {
	string title;
	string startDate;
	string endDate;
	string travelBuddy;
	TripStatus status;
	CheckList checklist;
	Dynamic_array<Note*> notes;
	Dynamic_array<Expense*> expenses;
	Dynamic_array<Location*> locations;
	Dynamic_array<TransportLeg*> legs;
public:
	Trip();
	Trip(std::string t, std::string start, std::string end, std::string buddy, TripStatus s);
	~Trip();
	void addNote(Note*);
	void addExpense(Expense*);
	void addLocation(Location*);
	void addTransportLeg(TransportLeg*);
	void updateStatus(TripStatus);
	void displayTripSummary(float x, float y);
	void saveToFile(ofstream&);
	void loadFromFile(ifstream&);
	string getTitle() const;
	Dynamic_array<Note*>& getNotes();
};

#endif