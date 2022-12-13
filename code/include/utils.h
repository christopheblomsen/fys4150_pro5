#ifndef UTILS_H_
#define UTILS_H_

#include <string>
#include <fstream>
#include <iostream>

// Checks if a file exists in directory
bool exists(const std::string& name);

// Used in src/Box.cpp make_file method
// to get the filename for the different slits
std::string potential_file(int slit);

#endif // UTILS_H_
