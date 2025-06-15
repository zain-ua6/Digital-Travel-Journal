#ifndef NOTE_H
#define NOTE_H

#include <string>
#include "Trip entry.h"

class Note : public TripEntry {
	string title;
	string content;
	string dateAdded;
public:
	Note();
	Note(string t, string c, string d );
	string getTitle() const;
	string getContent() const;
	string getDate() const;
};

#endif