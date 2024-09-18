#include "student.h"
#include <iostream>

Student::Student(const std::string& name, const std::string& rollno, int age) : name(name), rollno(rollno), age(age) {};

void Student::display() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "Roll No: " << rollno << std::endl;
    std::cout << "Age: " << age << std::endl;
}

nlohmann::json Student::toJson() {
    return nlohmann::json {
        {"name", name},
        {"rollno", rollno},
        {"age", age}
    };
}