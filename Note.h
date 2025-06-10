#ifndef NOTE_H
#define NOTE_H

#include "String.h"
#include "Date.h"
#include "Trip entry.h"

class Note : public TripEntry {
	String title;
	String content;
	Date dateAdded;
};


#endif