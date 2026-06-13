#ifndef COMMIT_H
#define COMMIT_H

#include <string>

class Commit {
public:
    int id;
    std::string message;
    std::string timestamp;
    std::string author;

    Commit(int id, const std::string& msg, const std::string& time, const std::string& auth);
    Commit(); // Default constructor

    void display() const;
};

#endif // COMMIT_H
