#include "VersionControl.h"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>

// ANSI Escape Codes for Styling
const std::string RESET = "\033[0m";
const std::string CYAN = "\033[36m";
const std::string YELLOW = "\033[33m";
const std::string GREEN = "\033[32m";
const std::string RED = "\033[31m";
const std::string MAGENTA = "\033[35m";
const std::string BOLD = "\033[1m";

VersionControl::VersionControl() : nextCommitId(1) {}

std::string VersionControl::getCurrentTime() const {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void VersionControl::addCommit(const std::string& message, const std::string& author) {
    std::cout << "\n" << GREEN << "[+] Processing Commit..." << RESET << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Animation delay

    Commit newCommit(nextCommitId++, message, getCurrentTime(), author);
    commitStack.push(newCommit);
    
    std::cout << "\r" << BOLD << GREEN << "✅ Commit successfully added! [ID: " << newCommit.id << "]" << RESET << "     \n";
}

void VersionControl::rollback() {
    if (commitStack.isEmpty()) {
        std::cout << "\n" << BOLD << RED << "❌ No commits to rollback!" << RESET << "\n";
        return;
    }
    
    std::cout << "\n" << RED << "[-] Reverting changes..." << RESET << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(800)); // Animation delay
    
    Commit faultyCommit = commitStack.peek();
    recoveryLog.push_back(faultyCommit);
    commitStack.pop();
    
    std::cout << "\r" << BOLD << RED << "⚠️  Rollback successful! Removed Commit [ID: " << faultyCommit.id << "]" << RESET << "     \n";
    if (!commitStack.isEmpty()) {
        std::cout << BOLD << GREEN << "➜ Restored to previous stable version [ID: " << commitStack.peek().id << "]" << RESET << "\n";
    } else {
        std::cout << BOLD << YELLOW << "➜ System is now at the initial state (no commits)." << RESET << "\n";
    }
}

void VersionControl::showHistory() const {
    if (commitStack.isEmpty()) {
        std::cout << "\033[2J\033[H"; // Clear screen
        std::cout << "\n" << BOLD << CYAN << "=================================================" << RESET << "\n";
        std::cout << BOLD << CYAN << "         🚀 LIVE VERSION HISTORY DASHBOARD 🚀     " << RESET << "\n";
        std::cout << BOLD << CYAN << "=================================================" << RESET << "\n\n";
        std::cout << BOLD << YELLOW << "  [ Stack is Empty - No Commits Found ]" << RESET << "\n\n";
        return;
    }

    // Extract to vector to draw from bottom up
    std::vector<Commit> temp;
    StackNode<Commit>* current = commitStack.getTopNode();
    while (current != nullptr) {
        temp.push_back(current->data);
        current = current->next;
    }

    std::cout << "\033[?25l"; // Hide cursor

    // Loop from bottom (last element) up to top (first element)
    for (int i = temp.size() - 1; i >= 0; --i) {
        std::cout << "\033[2J\033[H"; // Clear screen
        
        std::cout << "\n" << BOLD << CYAN << "=================================================" << RESET << "\n";
        std::cout << BOLD << CYAN << "         🚀 LIVE VERSION HISTORY DASHBOARD 🚀     " << RESET << "\n";
        std::cout << BOLD << CYAN << "=================================================" << RESET << "\n\n";

        // Draw commits from i down to the bottom
        for (int j = i; j < (int)temp.size(); ++j) {
            bool isTop = (j == i);
            
            std::cout << "       " << MAGENTA << "-----------------------------------" << RESET << "\n";
            std::cout << "       | " << YELLOW << "Commit ID: " << BOLD << temp[j].id << RESET;
            if (isTop && i == 0) {
                std::cout << BOLD << GREEN << " [HEAD -> TOP]" << RESET;
            } else if (isTop) {
                std::cout << BOLD << YELLOW << " [NEW...]" << RESET;
            }
            std::cout << "\n";
            
            std::cout << "       | " << CYAN << "Author: " << temp[j].author << RESET << "\n";
            std::cout << "       | " << CYAN << "Time:   " << temp[j].timestamp << RESET << "\n";
            
            std::string msg = temp[j].message;
            if (msg.length() > 22) msg = msg.substr(0, 19) + "...";
            std::cout << "       | " << CYAN << "Message: " << msg << RESET << "\n";
            std::cout << "       " << MAGENTA << "-----------------------------------" << RESET << "\n";

            if (j < (int)temp.size() - 1) {
                std::cout << "                       " << BOLD << MAGENTA << "||" << RESET << "\n";
                std::cout << "                       " << BOLD << MAGENTA << "\\/" << RESET << "\n";
            }
        }
        std::cout << "\n" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(600)); // Delay between frames
    }
    std::cout << "\033[?25h"; // Show cursor
}

void VersionControl::showAnalytics() const {
    std::cout << "\n" << BOLD << MAGENTA << "=================================================" << RESET << "\n";
    std::cout << BOLD << MAGENTA << "              📊 DEVELOPER ANALYTICS 📊           " << RESET << "\n";
    std::cout << BOLD << MAGENTA << "=================================================" << RESET << "\n";
    
    std::map<std::string, int> authorCommits;
    StackNode<Commit>* current = commitStack.getTopNode();
    
    while (current != nullptr) {
        authorCommits[current->data.author]++;
        current = current->next;
    }
    
    std::cout << YELLOW << "\n► Total Active Commits: " << BOLD << commitStack.getSize() << RESET << "\n";
    std::cout << RED << "► Total Rolled-back Commits: " << BOLD << recoveryLog.size() << RESET << "\n\n";
    
    std::cout << BOLD << CYAN << "Commits per Developer (Active):\n" << RESET;
    if (authorCommits.empty()) {
        std::cout << "  No data available.\n";
    } else {
        for (const auto& pair : authorCommits) {
            std::cout << "  - " << GREEN << pair.first << RESET << ": " << pair.second << " commit(s)\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Small animation
        }
    }
    std::cout << "\n";
}

void VersionControl::showRecoveryReports() const {
    std::cout << "\n" << BOLD << RED << "=================================================" << RESET << "\n";
    std::cout << BOLD << RED << "          ⚠️ CODE RECOVERY REPORTS ⚠️           " << RESET << "\n";
    std::cout << BOLD << RED << "=================================================" << RESET << "\n";
    if (recoveryLog.empty()) {
        std::cout << "\n" << BOLD << GREEN << "  [ No rollbacks have occurred. System is stable. ]" << RESET << "\n\n";
        return;
    }
    
    for (const auto& commit : recoveryLog) {
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        std::cout << "\n" << BOLD << YELLOW << "Rolled-back Commit ID: " << commit.id << RESET << "\n";
        std::cout << RED << "Author: " << commit.author << "\n";
        std::cout << "Time: " << commit.timestamp << "\n";
        std::cout << "Message: " << commit.message << RESET << "\n";
        std::cout << RED << "---------------------------------" << RESET << "\n";
    }
    std::cout << "\n";
}

void VersionControl::renderAdvancedDashboard() const {
    int leftWidth = 46;
    int rightWidth = 38;

    std::vector<std::string> leftPane = {
        "",
        "      Welcome back Developer!",
        "",
        "           ▀▄   ▄▀",
        "          ▄█▀███▀█▄",
        "         █▀███████▀█",
        "         █ █▀▀▀▀▀█ █",
        "            ▀▀ ▀▀",
        "",
        "    1. Add New Commit (Push)",
        "    2. Rollback to Previous (Pop)",
        "    3. View Version History Dashboard",
        "    4. View Developer Analytics",
        "    5. View Code Recovery Reports",
        "    6. Exit"
    };

    std::vector<std::string> rightPane(15, "");
    rightPane[0] = " Recent Activity";
    
    // Get top 3 commits
    std::vector<Commit> recentCommits;
    StackNode<Commit>* curr = commitStack.getTopNode();
    for(int i=0; i<3 && curr != nullptr; ++i) {
        recentCommits.push_back(curr->data);
        curr = curr->next;
    }

    for (size_t i = 0; i < recentCommits.size(); ++i) {
        std::string timeStr = recentCommits[i].timestamp.substr(11, 5); // get HH:MM
        std::string msg = recentCommits[i].message;
        if(msg.length() > 15) msg = msg.substr(0, 15) + "...";
        std::string line = " " + timeStr + "  " + msg;
        rightPane[1 + i] = line;
    }
    
    rightPane[4] = " .../view history for more";
    rightPane[5] = "SEPARATOR"; // Special marker
    rightPane[6] = " System Analytics";
    rightPane[7] = " Total Commits: " + std::to_string(commitStack.getSize());
    rightPane[8] = " Rollbacks: " + std::to_string(recoveryLog.size());
    
    std::map<std::string, int> authors;
    curr = commitStack.getTopNode();
    while(curr) { authors[curr->data.author]++; curr = curr->next; }
    rightPane[9] = " Active Devs: " + std::to_string(authors.size());

    // Helper lambda to pad strings ignoring UTF-8 continuation bytes
    auto pad = [](std::string s, int width) {
        int len = 0;
        for(unsigned char c : s) {
            if ((c & 0xC0) != 0x80) len++;
        }
        if(len < width) s.append(width - len, ' ');
        return s;
    };

    std::cout << "\n"; // Just add a newline instead of clearing the screen
    
    // Draw Top Border
    std::cout << RED << "╭── Software Version Control ";
    for(int i=0; i < leftWidth - 29; i++) std::cout << "─";
    std::cout << "┬";
    for(int i=0; i < rightWidth; i++) std::cout << "─";
    std::cout << "╮\n" << RESET;

    for (int i = 0; i < 15; ++i) {
        std::cout << RED << "│" << RESET;
        
        // Left Pane with colors
        std::string lText = " " + leftPane[i];
        std::string paddedLText = pad(lText, leftWidth);
        if (i >= 9 && i <= 14) {
            std::cout << CYAN << paddedLText << RESET;
        } else if (i >= 3 && i <= 7) {
            std::cout << YELLOW << paddedLText << RESET; 
        } else if (i == 1) {
            std::cout << BOLD << paddedLText << RESET;
        } else {
            std::cout << paddedLText;
        }

        if (rightPane[i] == "SEPARATOR") {
            std::cout << RED << "├";
            for(int j=0; j < rightWidth; j++) std::cout << "┈";
            std::cout << "┤\n" << RESET;
        } else {
            std::cout << RED << "│" << RESET;
            // Right Pane with colors
            std::string paddedRText = pad(rightPane[i], rightWidth);
            if (i == 0 || i == 6) {
                std::cout << RED << paddedRText << RESET;
            } else if (i >= 1 && i <= 3) {
                std::cout << GREEN << paddedRText << RESET;
            } else if (i == 4) {
                std::cout << "\033[90m" << paddedRText << RESET; // Gray
            } else {
                std::cout << paddedRText;
            }
            std::cout << RED << "│\n" << RESET;
        }
    }

    // Draw Bottom Border
    std::cout << RED << "╰";
    for(int i=0; i < leftWidth; i++) std::cout << "─";
    std::cout << "┴";
    for(int i=0; i < rightWidth; i++) std::cout << "─";
    std::cout << "╯\n" << RESET;
    
    std::cout << "> ";
}
