#include <iostream>
#include "Person.h"
#include "Event.h"
#include "Conference.h"

int main() {
    std::string title, description, firstName, lastName;

    Conference konferenca ("Facebook events", {19,3,2022}, {16,4,2022});

    Person presenterPN("Josko", "Joraz");
    Event prvaNajvecja("Prva Najvecja", "Prva najvecja dijaska zabava", &presenterPN, {25,3,2022});
    Event domenKumer("Domen Kumer", "Domen Kumer @Diskotega Anton", &presenterPN, {19,3,2022});
    Event queen("Queen Real Tribute", "Glasbeni spektakel", &presenterPN, {16,4,2022});
    Event tmp("Rand event", "Testirajmo", &presenterPN, {16,4,2022});

    Person *person1 = new Person("Matic", "Lukezic");
    Person *person2 = new Person("Nejc", "Lukezic");
    Person *person3 = new Person("Gal", "Jeza");
    Person *person4 = new Person("Simon", "Plazar");
    Person *person5 = new Person("Jure", "Miklosic");
    Person *person6 = new Person("Nika", "Visenjak");
    Person *person7 = new Person("Vid", "Cabrian");
    Person *person8 = new Person("Masa","Gasparic");

    prvaNajvecja.addAttendee(person1);
    prvaNajvecja.addAttendee(person2);
    prvaNajvecja.addAttendee(person6);

    domenKumer.addAttendee(person3);
    domenKumer.addAttendee(person2);
    domenKumer.addAttendee(person5);

    queen.addAttendee(person4);
    queen.addAttendee(person7);
    queen.addAttendee(person8);

    konferenca.addEvent(prvaNajvecja);
    konferenca.addEvent(domenKumer);
    konferenca.addEvent(queen);
    konferenca.addEvent(tmp);

    std::cout << "Konferenca:\n";
    std::cout << konferenca.toString() << std::endl;
    std::cout << "EVENTS:\n";
    konferenca.printEvents();


    std::cout<<"--------------------------------------------------------------" << std::endl;
    std::cout << "All attendees: " << std::endl;
    std::cout<<"--------------------------------------------------------------" << std::endl;
    std::vector<Person*> allAttendess = konferenca.getAllAttendees();
    for (int i = 0; i < allAttendess.size(); i++) {
        std::cout << allAttendess[i]->toString() << std::endl;
    }

    delete person1;
    delete person2;
    delete person3;
    delete person4;
    delete person5;
    delete person6;
    delete person7;
    delete person8;
    return 0;
}
