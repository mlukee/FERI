#include <iostream>
#include <sstream>
#include "Conference.h"

Conference::Conference(std::string title, Date startDate, Date endDate) : title(title), startDate(startDate), endDate(endDate) {}

std::vector<Event> Conference::getEvents() const{
    return events;
}

bool Conference::addEvent(const Event &event) {
        for (int i = 0; i < events.size(); i++) {
            if (events[i].getDate().toString() == event.getDate().toString())return false;
        }
    events.push_back(event);
    return true;
}

void Conference::printEvents() const{
    for(int i=0;i<events.size();i++){
        std::cout << events[i].toString()<<std::endl << "\nAttendees: " << std::endl;
        std::vector<Person*> attendees = events[i].getAttendees();
        for (int j = 0; j < attendees.size(); ++j) {
            std::cout << attendees[j]->toString() << std::endl;
        }
        std::cout << std::endl;
    }

}

bool contains(std::vector<Person*> v1, Person* person){
    for (int i = 0; i < v1.size(); ++i) {
        if(v1[i]->toString() == person->toString())
            return false;
    }
    return true;
}

std::vector<Person*> Conference::getAllAttendees() const{
    std::vector<Person*> attendees;
    for (int i = 0; i < events.size(); i++) {
        std::vector<Person*> eventAttendees = events[i].getAttendees();
        for (int j = 0; j < eventAttendees.size(); j++) {
            if(contains(attendees, eventAttendees[j]))
                attendees.push_back(eventAttendees[j]);
        }
    }
    return attendees;
}

std::string Conference::toString() const {
    std::stringstream ss;
    ss<< "Title: " << title << "\nStart Date: " << startDate.toString() << "\nEnd Date: " << endDate.toString();
    return ss.str();
}