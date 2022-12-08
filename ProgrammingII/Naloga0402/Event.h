//
// Created by Matic on 3/18/2022.
//

#ifndef NALOGA0402_EVENT_H
#define NALOGA0402_EVENT_H


#include <vector>
#include "Person.h"

class Event{
private:
    std::string title;
    std::string description;
    Person * presenter;
    Date date;
    std::vector<Person*> attendees;
public:
    Event(std::string title, std::string description, Person * presenter, Date date);
    std::string getTitle() const;
    std::vector<Person*> getAttendees() const;
    Date getDate() const;
    void addAttendee(Person * person);
    std::string toString() const;
    void printAttendees() const;
};


#endif //NALOGA0402_EVENT_H
