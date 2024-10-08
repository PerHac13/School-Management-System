#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <limits>
#include <fmt/core.h>
#include <fmt/color.h>
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
    fmt::print("{}\n", fmt::format(fg(fmt::color::gold), std::string(50, '*')));
    fmt::print("*{:^48}*\n", "");
    fmt::print("*{:^48}*\n", title);
    fmt::print("*{:^48}*\n", "");
    fmt::print("{}\n", fmt::format(fg(fmt::color::gold), std::string(50, '*')));
}

void displayMainMenu() {
    printHeader("Main Menu");
    fmt::print("1. Create a new school\n");
    fmt::print("2. Select an existing school\n");
    fmt::print("3. Save to file\n");
    fmt::print("4. Exit\n");
    fmt::print("{}\n", std::string(50, '-'));
    fmt::print("Enter your choice: ");
}

void handleMainMenu(std::vector<std::unique_ptr<School>>& schools) {
    int choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: {
            schools.push_back(SchoolFactory::createSchool());
            fmt::print("School created successfully. Press Enter to continue...");
            std::cin.get();
            break;
        }
        case 2: {
            if (schools.empty()) {
                fmt::print("No schools available. Please create a new school.\n");
                fmt::print("Press Enter to continue...");
                std::cin.get();
                break;
            }
            printHeader("Select a School");
            for (size_t i = 0; i < schools.size(); ++i) {
                fmt::print("{}. {}\n", i + 1, schools[i]->getSchoolName());
            }
            fmt::print("{}\n", std::string(50, '-'));
            fmt::print("Select a school: ");
            int schoolChoice;
            std::cin >> schoolChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (schoolChoice > 0 && schoolChoice <= static_cast<int>(schools.size())) {
                handleSchoolMenu(schools[schoolChoice - 1]);
            } else {
                fmt::print("Invalid choice. Press Enter to continue...");
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
                fmt::print("Data saved to data/schools.json\n");
                file.close();
            } else {
                fmt::print(fg(fmt::color::red), "Error: Could not open file.\n");
            }
            fmt::print("Press Enter to continue...");
            std::cin.get();
            break;
        }
        case 4:
            fmt::print("Exiting program.\n");
            exit(0);
        default:
            fmt::print(fg(fmt::color::red), "Invalid choice. Press Enter to continue...");
            std::cin.get();
    }
}

void displaySchoolMenu(const std::string& schoolName) {
    printHeader(fmt::format("School: {}", schoolName));
    fmt::print("1. Create a new class\n");
    fmt::print("2. Create a new class with existing class\n");
    fmt::print("3. Select an existing class\n");
    fmt::print("4. Delete an existing class\n");
    fmt::print("5. Save to individual file\n");
    fmt::print("6. Go back\n");
    fmt::print("{}\n", std::string(50, '-'));
    fmt::print("Enter your choice: ");
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
                fmt::print("Class added successfully. Press Enter to continue...");
                std::cin.get();
                break;
            }
            case 2: {
                const auto& classes = school->getClasses();
                if (classes.empty()) {
                    fmt::print("No classes available. Please create a new class.\n");
                    fmt::print("Press Enter to continue...");
                    std::cin.get();
                    break;
                }
                printHeader("Select a Class to Copy");
                for (size_t i = 0; i < classes.size(); ++i) {
                    fmt::print("{}. Class {} by {}\n", i + 1, classes[i]->getClassNumber(), classes[i]->getClassTeacher());
                }
                fmt::print("{}\n", std::string(50, '-'));
                fmt::print("Select a class by number: ");
                int classChoice;
                std::cin >> classChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (classChoice > 0 && classChoice <= static_cast<int>(classes.size())) {
                    school->addClass(SchoolFactory::createClass(classes[classChoice - 1]));
                    fmt::print("New class created and added successfully. Press Enter to continue...");
                    std::cin.get();
                } else {
                    fmt::print("Invalid choice. Press Enter to continue...");
                    std::cin.get();
                }
                break;
            }
            case 3: {
                const auto& classes = school->getClasses();
                if (classes.empty()) {
                    fmt::print("No classes available. Please create a new class.\n");
                    fmt::print("Press Enter to continue...");
                    std::cin.get();
                    break;
                }
                printHeader("Select a Class");
                for (size_t i = 0; i < classes.size(); ++i) {
                    fmt::print("{}. Class {} by {}\n", i + 1, classes[i]->getClassNumber(), classes[i]->getClassTeacher());
                }
                fmt::print("{}\n", std::string(50, '-'));
                fmt::print("Select a class by number: ");
                int classChoice;
                std::cin >> classChoice;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                if (classChoice > 0 && classChoice <= static_cast<int>(classes.size())) {
                    handleClassMenu(classes[classChoice - 1]);
                } else {
                    fmt::print("Invalid choice. Press Enter to continue...");
                    std::cin.get();
                }
                break;
            }
            case 4: {
                int classNumber;
                fmt::print("Enter class number to delete: ");
                std::cin >> classNumber;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                school->deleteClass(classNumber);
                fmt::print("Press Enter to continue...");
                std::cin.get();
                break;
            }
            case 5: {
                school->saveToFile();
                fmt::print("Press Enter to continue...");
                std::cin.get();
                break;
            }
            case 6: {
                return;
            }
            default: {
                fmt::print(fg(fmt::color::red), "Invalid choice. Press Enter to continue...");
                std::cin.get();
            }
        }
    }
}

void displayClassMenu(int classNumber, const std::string& teacherName) {
    printHeader(fmt::format("Class {} by {}", classNumber, teacherName));
    fmt::print("1. Add student to class\n");
    fmt::print("2. Display class info\n");
    fmt::print("3. Go back\n");
    fmt::print("{}\n", std::string(50, '-'));
    fmt::print("Enter your choice: ");
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
                fmt::print("Student added successfully. Press Enter to continue...");
                std::cin.get();
                break;
            }
            case 2: {
                selectedClass->displayClassInfo();
                fmt::print("Press Enter to continue...");
                std::cin.get();
                break;
            }
            case 3: {
                return;
            }
            default: {
                fmt::print(fg(fmt::color::red), "Invalid choice. Press Enter to continue...");
                std::cin.get();
            }
        }
    }
}