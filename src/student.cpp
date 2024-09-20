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

std::shared_ptr<Student> createStudent() {
    std::string name;
    std::string rollno;
    int age;
    std::cout << "Enter the name of the student: ";
    std::getline(std::cin, name);
    std::cout << "Enter the roll number of the student: ";
    std::getline(std::cin, rollno);
    std::cout << "Enter the age of the student: ";
    std::cin >> age;
    return std::make_shared<Student>(name, rollno, age);
}