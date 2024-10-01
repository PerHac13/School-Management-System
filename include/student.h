#pragma once
#include <string>
#include <nlohmann/json.hpp>

class Student {
    private: 
        std::string name;
        std::string rollno;
        int age;
    
    public:
        Student(const std::string& name, const std::string& rollno, int age);
        
        void display() const;
        nlohmann::json toJson() const;

        static std::unique_ptr<Student> createFromJson(const nlohmann::json& jsonData);
};
