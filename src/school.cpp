#include <iostream>
#include <fstream>
#include <algorithm>

#include "school.h"

// Class members implementation

School::School(const std::string& schoolName) : schoolName(schoolName) {}

void School::addClass(const std::shared_ptr<Class>& schoolClass) {
    classes.push_back(schoolClass);
}

std::string School::getSchoolName() const {
    return schoolName;
}

std::vector<std::shared_ptr<Class>> School::getClasses() const {
    return classes;
}

void School::displaySchoolInfo() const {
    std::cout << "School name: " << schoolName << std::endl;
    std::cout << "Classes: " << std::endl;
    for (const auto& schoolClass : classes) {
        schoolClass->displayClassInfo();
    }
}

nlohmann::json School::toJson() const {
    nlohmann::json jsonData;
    jsonData["schoolName"] = schoolName;
    jsonData["classes"] = nlohmann::json::array();
    for (const auto& schoolClass : classes) {
        jsonData["classes"].push_back(schoolClass->toJson());
    }
    return jsonData;
}

// Phase 2: Save the school data to a file individually
void School::saveToFile() const {
    nlohmann::json jsonData = toJson();
    std::string filename = schoolName;
    std::replace(filename.begin(), filename.end(), ' ', '_');
    filename = "../data/"+filename + ".json";

    std::ofstream file(filename);
    if(file.is_open()) {
        file << jsonData.dump(4);
        std::cout << "Data saved to " << filename << std::endl;
        file.close();
    } else {
        std::cerr << "Error: Could not open file." << std::endl;
    }
}

std::vector<School> School::loadFromFileJSON(const std::string& filename) {
    std::vector<School> schools;
    std::ifstream file("../data/" + filename);
    
    if(file.is_open()) {
        nlohmann::json jsonData;
        file >> jsonData;
        file.close();

        for (const auto& schoolJSON :jsonData){
            School school(schoolJSON["schoolName"]);
            for (const auto& classJSON : schoolJSON["classes"]) {
                std::shared_ptr<Class> schoolClass = std::make_shared<Class>(classJSON["classNumber"], classJSON["classTeacher"]);
                for (const auto& studentJSON : classJSON["students"]) {
                    schoolClass->addStudent(std::make_shared<Student>(studentJSON["name"], studentJSON["rollno"] ,studentJSON["age"]));
                }
                school.addClass(schoolClass);
            }
            schools.push_back(school);
        }
        std::cout << "Data loaded from " << filename << std::endl;
    }else {
        std::cout << "Error: Could not open file." << std::endl;
    }
    return schools;
}

void School::deleteClass(int classNumber) {
    auto it = std::find_if(classes.begin(), classes.end(),
        [classNumber](const std::shared_ptr<Class>& c) { return c->getClassNumber() == classNumber; });
    
    if (it != classes.end()) {
        classes.erase(it);
        std::cout << "Class " << classNumber << " has been deleted." << std::endl;
    } else {
        std::cout << "Class " << classNumber << " not found." << std::endl;
    }
}

void School::changeSchoolName(const std::string& newName) {
    schoolName = newName;
    std::cout << "School name has been changed to: " << newName << std::endl;
}

// Function implementation
std::shared_ptr<School> createSchool() {
    std::string schoolName;
    std::cout << "Enter the school name: ";
    std::getline(std::cin, schoolName);
    return std::make_shared<School>(schoolName);
}