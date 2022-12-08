#ifndef NALOGA0402_CONFERENCE_H
#define NALOGA0402_CONFERENCE_H

#include "Event.h"

class Conference{
private:
    std::string title;
    Date startDate;
    Date endDate;
    std::vector<Event> events;
public:
    Conference(std::string title, Date startDate, Date endDate);
    std::vector<Event> getEvents() const;
    void printEvents() const;
    bool addEvent(const Event& event);
    std::vector<Person*> getAllAttendees() const;
    std::string toString() const;
};


#endif //NALOGA0402_CONFERENCE_H
