#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../lib/json.hpp"

#include "student.h"

class Class {
    private:
        int classNumber;
        std::string classTeacher;
        std::vector<std::shared_ptr<Student>> students;

    public:
        Class(int classNumber, const std::string& classTeacher);
        
        void addStudent(const std::shared_ptr<Student>& student);
        int getClassNumber() const;
        std::string getClassTeacher() const;
        void displayClassInfo() const;
        nlohmann::json toJson() const;
};

std::shared_ptr<Class> createClass();