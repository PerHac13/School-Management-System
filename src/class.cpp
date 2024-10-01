#include <iostream>

#include "class.h"

Class::Class(int classNumber, const std::string& classTeacher) 
: classNumber(classNumber), classTeacher(classTeacher) {
    students.reserve(50);
}

void Class::reserveStudentCapacity(size_t capacity){
    students.reserve(capacity);
}

void Class::addStudent(const std::unique_ptr<Student> student) {
    students.push_back(std::move(student));
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

std::unique_ptr<Class> Class::createFromJson(const nlohmann::json& jsonData) {
    std::unique_ptr<Class> classPtr = std::make_unique<Class>(jsonData["classNumber"], jsonData["classTeacher"]);
    for (const auto& studentJSON : jsonData["students"]) {
        classPtr->addStudent(Student::createFromJson(studentJSON));
    }
    return classPtr;
}