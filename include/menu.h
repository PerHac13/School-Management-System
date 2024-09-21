#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "school.h"

// Function prototypes
void displayMainMenu();
void handleMainMenu(std::vector<std::shared_ptr<School>>& schools);
void displaySchoolMenu(const std::string& schoolName);
void handleSchoolMenu(std::shared_ptr<School> school);
void displayClassMenu();
void handleClassMenu(std::shared_ptr<Class> selectedClass);
