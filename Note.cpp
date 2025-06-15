#include "Note.h"

Note::Note() : title(""), content(""), dateAdded("") {}
Note::Note(string t, string c, string d) : title(t), content(c), dateAdded(d) {}
string Note::getTitle() const {
	return title;
}
string Note::getContent() const {
	return content;
}
string Note::getDate() const {
	return dateAdded;
}