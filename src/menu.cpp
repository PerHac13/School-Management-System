#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <limits>
#include "school_factory.h"
#include "school.h"
#include "menu.h"

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void printHeader(const std::string& title) {
    clearScreen();
    std::cout << std::string(50, '*') << std::endl;
    std::cout << "*" << std::string(48, ' ') << "*" << std::endl;
    std::cout << "*" << std::string((48 - title.length()) / 2, ' ') << title 
              << std::string((49 - title.length()) / 2, ' ') << "*" << std::endl;
    std::cout << "*" << std::string(48, ' ') << "*" << std::endl;
    std::cout << std::string(50, '*') << std::endl;
}

void displayMainMenu() {
    printHeader("Main Menu");
    std::cout << "1. Create a new school\n";
    std::cout << "2. Select an existing school\n";
    std::cout << "3. Save to file\n";
    std::cout << "4. Exit\n";
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter your choice: ";
}

void handleMainMenu(std::vector<std::unique_ptr<School>>& schools) {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: {
            schools.push_back(SchoolFactory::createSchool());
            std::cout << "School created successfully. Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 2: {
            if (schools.empty()) {
                std::cout << "No schools available. Please create a new school." << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.get();
                break;
            }
            printHeader("Select a School");
            for (size_t i = 0; i < schools.size(); ++i) {
                std::cout << i + 1 << ". " << schools[i]->getSchoolName() << std::endl;
            }
            std::cout << std::string(50, '-') << std::endl;
            std::cout << "Select a school: ";
            int schoolChoice;
            std::cin >> schoolChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (schoolChoice > 0 && schoolChoice <= static_cast<int>(schools.size())) {
                handleSchoolMenu(schools[schoolChoice - 1]);
            } else {
                std::cout << "Invalid choice. Press Enter to continue...";
                std::cin.get();
            }
            break;
        }
        case 3: {
            nlohmann::json jsonData;
            for (const auto& school : schools) {
                jsonData.push_back(school->toJson());
            }
            std::ofstream file("../data/schools.json");
            if(file.is_open()) {
                file << jsonData.dump(4);
                std::cout << "Data saved to data/schools.json" << std::endl;
                file.close();
            } else {
                std::cout << "Error: Could not open file." << std::endl;
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
            break;
        }
        case 4:
            std::cout << "Exiting program." << std::endl;
            exit(0);
        default:
            std::cout << "Invalid choice. Press Enter to continue...";
            std::cin.get();
    }
}

void displaySchoolMenu(const std::string& schoolName) {
    printHeader("School: " + schoolName);
    std::cout << "1. Create a new class\n";
    std::cout << "2. Select an existing class\n";
    std::cout << "3. Delete an existing class\n";
    std::cout << "4. Save to individual file\n";
    std::cout << "5. Go back\n";
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter your choice: ";
}

void handleSchoolMenu(std::unique_ptr<School>& school) {
    while (true) {
        displaySchoolMenu(school->getSchoolName());
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                school->addClass(SchoolFactory::createClass());
                std::cout << "Class added successfully. Press Enter to continue...";
                std::cin.get();
                break;
            }
            case 2: {
                const auto& classes = school->getClasses();
                if (classes.empty()) {
                    std::cout << "No classes available. Please create a new class." << std::endl;
                    std::cout << "Press Enter to continue...";
                    std::cin.get();
                    break;
                }
                printHeader("Select a Class");
                for (size_t i = 0; i < classes.size(); ++i) {
                    std::cout << i + 1 << ". Class " << classes[i]->getClassNumber() 
                              << " by " << classes[i]->getClassTeacher() << std::endl;
                }
                std::cout << std::string(50, '-') << std::endl;
                std::cout << "Select a class by number: ";
                int classChoice;
                std::cin >> classChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (classChoice > 0 && classChoice <= static_cast<int>(classes.size())) {
                    handleClassMenu(classes[classChoice - 1]);
                } else {
                    std::cout << "Invalid choice. Press Enter to continue...";
                    std::cin.get();
                }
                break;
            }
            case 3: {
                int classNumber;
                std::cout << "Enter class number to delete: ";
                std::cin >> classNumber;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                school->deleteClass(classNumber);
                std::cout << "Press Enter to continue...";
                std::cin.get();
                break;
            }
            case 4: {
                school->saveToFile();
                std::cout << "Press Enter to continue...";
                std::cin.get();
                break;
            }
            case 5: {
                return;
            }
            default: {
                std::cout << "Invalid choice. Press Enter to continue...";
                std::cin.get();
            }
        }
    }
}

void displayClassMenu(int classNumber, const std::string& teacherName) {
    printHeader("Class " + std::to_string(classNumber) + " by " + teacherName);
    std::cout << "1. Add student to class\n";
    std::cout << "2. Display class info\n";
    std::cout << "3. Go back\n";
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Enter your choice: ";
}

void handleClassMenu(const std::unique_ptr<Class>& selectedClass) {
    while (true) {
        displayClassMenu(selectedClass->getClassNumber(), selectedClass->getClassTeacher());
        int choice;
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: {
                selectedClass->addStudent(SchoolFactory::createStudent());
                std::cout << "Student added successfully. Press Enter to continue...";
                std::cin.get();
                break;
            }
            case 2: {
                selectedClass->displayClassInfo();
                std::cout << "Press Enter to continue...";
                std::cin.get();
                break;
            }
            case 3: {
                return;
            }
            default: {
                std::cout << "Invalid choice. Press Enter to continue...";
                std::cin.get();
            }
        }
    }
}