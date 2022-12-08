#include <sstream>
#include <fstream>
#include <iostream>
#include "Student.h"
#include "Address.h"
#include "UnparseableDateException.h"
#include "WrongPhoneNumberException.h"

Student::Student(unsigned int id, std::string name, std::string surname, std::string phone,Date dateOfBirth, Address address):
                id(id), name(name), surname(surname),dateOfBirth(dateOfBirth), address(address) {
    if(Student::isGoodNumber(phone))
        this->phone = phone;
    else
        throw(WrongPhoneNumberException(phone));
}

std::string Student::toString() const {
    std::stringstream ss;
    ss << id << "," << name << "," << surname << "," << phone << ","<< dateOfBirth.toString() << "," << address.toString();
    return ss.str();
}

bool Student::isGoodNumber(std::string number) {
    char ch;
    for(int i =0;i<number.length();i++){
        ch = number[i];
        if((ch >= 'a' && ch<='z') ||(ch >= 'A' && ch<='Z'))
            return false;
    }
    return true;
}

std::vector<std::shared_ptr<Student>> Student::LoadFromFile(const std::string &filename){
    std::vector<std::shared_ptr<Student>> students;
    std::ifstream file(filename);
    Date date;
    std::string phoneNumber;
    if(!file.is_open()){
        std::cout << "ERROR!" << std::endl;
        return {};
    }else{
        while(!file.eof()){
            std::vector<std::string> eachStudent;
            std::string line;
            std::getline(file, line);
            std::istringstream divideLine(line);
            while(divideLine.good()){
                std::string substr;
                std::getline(divideLine, substr, ',');
                eachStudent.push_back(substr);
            }
            try{
                phoneNumber = eachStudent[3];
                date = Date::GetDateFromString(eachStudent[4]);
                if(eachStudent.size() < 8)
                    continue;
                students.push_back(std::make_shared<Student>(std::stoi(eachStudent[0]),
                                                             eachStudent[1],
                                                             eachStudent[2],
                                                             phoneNumber,
                                                             date,
                                                             Address(eachStudent[5], eachStudent[6],
                                                                     eachStudent[7])));
            }catch(UnparseableDateException &exception){
                std::cout << exception.what() << std::endl;
            }catch(WrongPhoneNumberException &exception){
                std::cout << exception.what() << std::endl;
            }
        }
    }
    file.close();
    return students;
}

void Student::SaveToFile(const std::vector<std::shared_ptr<Student>> &students, const std::string &fileName){
    std::ofstream file(fileName);
    if(!file.is_open()){
        std::cout << "ERROR" << std::endl;
        return;
    }
    for(const auto &student : students)
        file << student->toString() << std::endl;
    file.close();
}