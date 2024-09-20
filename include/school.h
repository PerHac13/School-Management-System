#pragma once
#include <string>
#include <vector>
#include <memory>
#include "../lib/json.hpp"

#include "class.h"

class School {
    private:
        std::string schoolName;
        std::vector<std::shared_ptr<Class>> classes;

    public:
        School(const std::string& schoolName);
        
        void addClass(const std::shared_ptr<Class>& schoolClass);
        std::string getSchoolName() const;
        std::vector<std::shared_ptr<Class>> getClasses() const;
        void displaySchoolInfo() const;
        nlohmann::json toJson() const;
        void saveToFile() const;
        static std::vector<School> loadFromFileJSON(const std::string& filename);
};

std::shared_ptr<School> createSchool();