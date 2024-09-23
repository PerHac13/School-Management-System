#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "school.h"
#include "menu.h"


void displayMainMenu() {
    std::cout << "\nMain Menu\n";
    std::cout << "1. Create a new school\n";
    std::cout << "2. Select an existing school\n";
    std::cout << "3. Save to file\n";
    std::cout << "4. Exit\n";
    std::cout << "Enter your choice: ";
}

void handleMainMenu(std::vector<std::shared_ptr<School>>& schools) {
    int choice;
    std::cin >> choice;
    std::cin.ignore();

    switch (choice) {
        case 1: {
            schools.push_back(createSchool());
            break;
        }
        case 2: {
            if (schools.empty()) {
                std::cout << "No schools available. Please create a new school." << std::endl;
                break;
            }
            for (size_t i = 0; i < schools.size(); ++i) {
                std::cout << i + 1 << ". " << schools[i]->getSchoolName() << std::endl;
            }
            std::cout << "Select a school: ";
            int schoolChoice;
            std::cin >> schoolChoice;
            std::cin.ignore();
            if (schoolChoice > 0 && schoolChoice <= schools.size()) {
                handleSchoolMenu(schools[schoolChoice - 1]);
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
            break;
        }
        case 3: {
            nlohmann::json jsonData;
            for (const auto& school : schools) {
                jsonData.push_back(nlohmann::json::parse(school->toJson().dump()));
            }
            std::ofstream file("../data/schools.json");
            if(file.is_open()) {
                file << jsonData.dump(4);
                std::cout << "Data saved to data/schools.json" << std::endl;
                file.close();
            } else {
                std::cout << "Error: Could not open file." << std::endl;
            }
            exit(0);
        }
        case 4:
            std::cout << "Exiting program." << std::endl;
            exit(0);
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
    }
}

void displaySchoolMenu(const std::string& schoolName) {
    std::cout << "\nSchool: " << schoolName << std::endl;
    std::cout << "1. Create a new class\n";
    std::cout << "2. Select an existing class\n";
    std::cout << "3. Save to individuals file\n";
    std::cout << "4. Go back\n";
    std::cout << "Enter your choice: ";
}


void handleSchoolMenu(std::shared_ptr<School> school) {
    while (true) {
        displaySchoolMenu(school->getSchoolName());
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                school->addClass(createClass());
                std::cout << "Class added successfully." << std::endl;
                break;
            }
            case 2: {
                std::vector<std::shared_ptr<Class>> classes = school->getClasses();
                if (classes.empty()) {
                    std::cout << "No classes available. Please create a new class." << std::endl;
                    break;
                }
                std::cout << "Select a class: \n";
                for (size_t i = 0; i < classes.size(); ++i) {
                    std::cout << i + 1 << ". Class " << classes[i]->getClassNumber() << " by " << classes[i]->getClassTeacher() << std::endl;
                }
                std::cout << "Select a class by number: ";
                int classChoice;
                std::cin >> classChoice;
                std::cin.ignore();

                if (classChoice > 0 && classChoice <= classes.size()) {
                    handleClassMenu(classes[classChoice - 1]);
                } else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
                break;
            }
            case 3: {
                school->saveToFile();
                break;
            }
            case 4: {
                return;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
}

void displayClassMenu() {
    std::cout << "\n1. Add student to class\n";
    std::cout << "2. Display class info\n";
    std::cout << "3. Go back\n";
    std::cout << "Enter your choice: ";
}

void handleClassMenu(std::shared_ptr<Class> selectedClass) {
    while (true) {
        displayClassMenu();
        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                selectedClass->addStudent(createStudent());
                std::cout << "Student added successfully." << std::endl;
                break;
            }
            case 2: {
                selectedClass->displayClassInfo();
                break;
            }
            case 3: {
                return;
            }
            default: {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
}