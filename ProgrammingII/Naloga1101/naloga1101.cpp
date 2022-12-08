#include <iostream>
#include "Student.h"
#include "Date.h"
#include "UnparseableDateException.h"
#include <vector>

int main() {
    try{
        Date::GetDateFromString(Date(12,12,2022).toString()).print();
        Date::GetDateFromString("33.12.2022").print();
        Date::GetDateFromString("13.1o.2022").print();
    }catch (UnparseableDateException &exception){
        std::cout << exception.what() << std::endl;
    }

    std::vector<std::shared_ptr<Student>> studenti = Student::LoadFromFile("students.csv");
    for(auto& student : studenti){
        std::cout << student->toString() << std::endl;
    }

    Student::SaveToFile(studenti, "out.txt");
    return 0;
}
