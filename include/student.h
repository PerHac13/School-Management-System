#pragma once
#include <string>
#include "../lib/json.hpp"

class Student {
    private: 
        std::string name;
        std::string rollno;
        int age;
    
    public:
        Student(const std::string& name, const std::string& rollno, int age);
        
        void display() const;
        nlohmann::json toJson();
};

std::shared_ptr<Student> createStudent();