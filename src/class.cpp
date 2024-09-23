#include <iostream>

#include "class.h"

Class::Class(int classNumber, const std::string& classTeacher) : classNumber(classNumber), classTeacher(classTeacher) {}

void Class::addStudent(const std::shared_ptr<Student>& student) {
    students.push_back(student);
}

int Class::getClassNumber() const {
    return classNumber;
}

std::string Class::getClassTeacher() const {
    return classTeacher;
}

void Class::displayClassInfo() const {
    std::cout << "Class number: " << classNumber << std::endl;
    std::cout << "Class teacher: " << classTeacher << std::endl;
    std::cout << "Students: " << std::endl;
    for (const auto& student : students) {
        student->display();
    }
}

nlohmann::json Class::toJson() const {
    nlohmann::json jsonData;
    jsonData["classNumber"] = classNumber;
    jsonData["classTeacher"] = classTeacher;
    jsonData["students"] = nlohmann::json::array();
    for (const auto& student : students) {
        jsonData["students"].push_back(student->toJson());
    }
    return jsonData;
}

std::shared_ptr<Class> createClass() {
    std::string teacher;
    int classNumber;
    std::cout << "Enter the class number: ";
    std::cin >> classNumber;
    std::cin.ignore();
    std::cout << "Enter the name of the class teacher: ";
    std::getline(std::cin, teacher);
    return std::make_shared<Class>(classNumber, teacher);
}