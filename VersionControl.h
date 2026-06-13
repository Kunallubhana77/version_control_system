#ifndef VERSION_CONTROL_H
#define VERSION_CONTROL_H

#include "Stack.h"
#include "Commit.h"
#include <vector>
#include <map>
#include <string>

class VersionControl {
private:
    Stack<Commit> commitStack;
    std::vector<Commit> recoveryLog;
    int nextCommitId;

    std::string getCurrentTime() const;

public:
    VersionControl();

    // Commit Tracking System
    void addCommit(const std::string& message, const std::string& author);

    // Rollback Engine
    void rollback();

    // Version History Dashboard
    void showHistory() const;

    // Developer Analytics
    void showAnalytics() const;

    // Code Recovery Reports
    void showRecoveryReports() const;

    // Advanced Terminal UI Dashboard
    void renderAdvancedDashboard() const;
};

#endif // VERSION_CONTROL_H
