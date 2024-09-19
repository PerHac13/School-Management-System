#include <iostream>

#include "class.h"

Class::Class(int classNumber, const std::string& classTeacher) : classNumber(classNumber), classTeacher(classTeacher) {}

void Class::addStudent(const std::shared_ptr<Student>& student) {
    students.push_back(student);
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