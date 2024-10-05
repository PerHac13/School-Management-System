#include "student.h"
#include <iostream>

Student::Student(const std::string& name, const std::string& rollno, int age) : name(name), rollno(rollno), age(age) {};

void Student::display() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Roll No: " << rollno << std::endl;
    std::cout << "Age: " << age << std::endl;
}

std::string Student::getRollNo() const {
    return rollno;
}

nlohmann::json Student::toJson() const{
    return nlohmann::json {
        {"name", name},
        {"rollno", rollno},
        {"age", age}
    };
}

std::unique_ptr<Student> Student::createFromJson(const nlohmann::json& jsonData) {
    return std::make_unique<Student>(jsonData["name"], jsonData["rollno"], jsonData["age"].get<int>());
}

bool Student::operator == (const Student& other) const {
    return rollno == other.rollno;
}