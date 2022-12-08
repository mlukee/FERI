#include <iostream>
#include "Date.h"
#include "SmartPointer.h"
#include "Rectangle.h"
#include <memory>

int main() {

    SmartPointer<Date> date1(new Date(6,5,2022));
    SmartPointer<Date> date5(new Date(5,5,2022));

    //Prekrivanje operatorja <<
    std::cout << *date5 << std::endl;

    //Prekrivanje operatorja ==
    std::cout << "Prekrivanje operatorja == \n";
    if(*date1==(*date5)){
        std::cout << "Datuma " << *date1 << " in " << *date5 << " sta enaka\n\n";
    }else
        std::cout << "Datuma " << *date1 << " in " << *date5 << " nista enaka\n\n";

    //Prekrivanje prefiksnega operatorja++
    std::cout <<"prefix ++: " << ++(*date5) << std::endl << std::endl;

    //Prekrivanje postfix operatorja++
    std::cout <<"postfix ++: " << (*date1)++ << std::endl << std::endl;

    SmartPointer<Rectangle> rec1(new Rectangle(4,6));
    std::cout << "Povrsina rec1: " << rec1->getSurfaceArea() << std::endl;
    std::cout << *rec1 << std::endl << std::endl;
    std::cout << --(*rec1) << std::endl <<(*rec1).getSurfaceArea() << std::endl << std::endl;
    std::cout << *rec1 << std::endl <<((*rec1)--).getSurfaceArea() << std::endl << std::endl;
    std::cout << *rec1 << std::endl <<(*rec1).getSurfaceArea() << std::endl << std::endl;

    std::shared_ptr<Rectangle> ptr1(new Rectangle(5,7));
    std::shared_ptr<Rectangle> ptr2;
    ptr2 = ptr1;
    std::cout << "shared_ptr ptr1: " << (*ptr1).getSurfaceArea()<< std::endl;
    std::cout << "shared_ptr ptr2: " << (*ptr2).getSurfaceArea() << std::endl;
    std::cout << "Count of ptr1: " << ptr2.use_count() << std::endl << std::endl;

    SmartPointer<Date> date6 (new Date(1,1,2002));
    std::cout << *date6 << std::endl;
    --(*date6);
    std::cout << (*date6)-- << std::endl;
    std::cout << *date6;

    return 0;
}