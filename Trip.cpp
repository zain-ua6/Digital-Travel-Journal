#include "Trip.h"
#include <raylib.h>
#include <string>
using namespace std;

Trip::Trip() : title(""), startDate(""), endDate(""), travelBuddy(""), status(Planned) {}

Trip::Trip(string t, string start, string end, string buddy, TripStatus s) : title(t), startDate(start), endDate(end), travelBuddy(buddy), status(s) {}

Trip::~Trip() {
    for (int i = 0; i < notes.size(); ++i) {
        delete notes[i];
    }
    for (int i = 0; i < expenses.size(); ++i) {
        delete expenses[i];
    }
    for (int i = 0; i < locations.size(); ++i) {
        delete locations[i];
    }
    for (int i = 0; i < legs.size(); ++i) {
        delete legs[i];
    }
}

void Trip::addNote(Note* n) {
    notes.push(n);
}

void Trip::addExpense(Expense* e) {
    expenses.push(e);
}

void Trip::addLocation(Location* l) {
    locations.push(l);
}

void Trip::addTransportLeg(TransportLeg* t) {
    legs.push(t);
}

void Trip::updateStatus(TripStatus s) {
    status = s;
}


void Trip::displayTripSummary(float x, float y) {
    DrawText(("Trip Name: " + title).c_str(), x, y, 20, DARKGRAY);
    DrawText(("Start Date: " + startDate).c_str(), x, y + 30, 20, DARKGRAY);
    DrawText(("End Date: " + endDate).c_str(), x, y + 60, 20, DARKGRAY);
    DrawText(("Travel Buddy: " + travelBuddy).c_str(), x, y + 90, 20, DARKGRAY);

    string statusStr;
    switch (status) {
    case Planned: statusStr = "Planned"; break;
    case Current: statusStr = "Ongoing"; break;
    case Completed: statusStr = "Completed"; break;
    }

    DrawText(("Status: " + statusStr).c_str(), x, y + 120, 20, DARKGRAY);
}

string Trip::getTitle() const {
    return title;
}

Dynamic_array<Note*>& Trip::getNotes() {
    return notes;
}