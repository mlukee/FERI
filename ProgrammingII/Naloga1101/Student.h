#ifndef NALOGA1101_STUDENT_H
#define NALOGA1101_STUDENT_H


#include <string>
#include <memory>
#include <vector>
#include "Date.h"
#include "Address.h"

class Student {
private:
    unsigned int id;
    std::string name, surname, phone;
    Date dateOfBirth;
    Address address;
public:
    Student(unsigned int id, std::string name, std::string surname, std::string phone,Date dateOfBirth, Address address);
    std::string toString() const;
    static bool isGoodNumber(std::string number);
    static std::vector<std::shared_ptr<Student>> LoadFromFile(const std::string &filename);
    static void SaveToFile(const std::vector<std::shared_ptr<Student>> &students, const std::string &fileName);
};


#endif //NALOGA1101_STUDENT_H
