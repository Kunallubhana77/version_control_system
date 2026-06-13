#include "Commit.h"
#include <iostream>

Commit::Commit(int id, const std::string& msg, const std::string& time, const std::string& auth)
    : id(id), message(msg), timestamp(time), author(auth) {}

Commit::Commit() : id(0), message(""), timestamp(""), author("") {}

void Commit::display() const {
    std::cout << "Commit ID: " << id << "\n"
              << "Author: " << author << "\n"
              << "Time: " << timestamp << "\n"
              << "Message: " << message << "\n"
              << "-------------------------\n";
}
