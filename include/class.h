#pragma once
#include <string>
#include <vector>
#include <memory>
#include <nlohmann/json.hpp>

#include "student.h"

class Class {
    private:
        int classNumber;
        std::string classTeacher;
        std::vector<std::unique_ptr<Student>> students;

    public:
        Class(int classNumber, const std::string& classTeacher);
        
        void addStudent(std::unique_ptr<Student> student);
        int getClassNumber() const;
        std::string getClassTeacher() const;
        void displayClassInfo() const;
        nlohmann::json toJson() const;
        void reserveStudentCapacity(size_t capacity);
        
        static std::unique_ptr<Class> createFromJson(const nlohmann::json& jsonData);
};
