#include "Event.h"
#include <sstream>
#include <iostream>

Event::Event(std::string title, std::string description, Person * presenter, Date date) : title(title), description(description), presenter(presenter), date(date) {}

std::string Event::getTitle() const{
    return title;
}

std::vector<Person*> Event::getAttendees() const{
    return attendees;
}

Date Event::getDate() const {
    return date;
}

void Event::addAttendee(Person *person) {
    attendees.push_back(person);
}

void Event::printAttendees() const {
    for (int i = 0; i < attendees.size(); i++) {
        std::cout<<attendees[i]->toString() << std::endl;
    }
}

std::string Event::toString() const {
    std::stringstream ss;
    ss<< "Title: " << title << "\nDescription: " << description << "\nPresenter: " << presenter->toString() <<"\nDate: " << date.toString();
    return ss.str();
}