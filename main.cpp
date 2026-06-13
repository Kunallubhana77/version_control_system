#include <iostream>
#include <string>
#include <limits>
#include "VersionControl.h"

int main() {
    VersionControl vcs;
    int choice;

    while (true) {
        vcs.renderAdvancedDashboard();
        
        if (!(std::cin >> choice)) {
            std::cin.clear(); // clear error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard invalid input
            std::cout << "\033[1;31mInvalid input. Please enter a number.\033[0m\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume newline character

        if (choice == 1) {
            std::string author, message;
            std::cout << "\033[1mEnter developer name:\033[0m ";
            std::getline(std::cin, author);
            std::cout << "\033[1mEnter commit message:\033[0m ";
            std::getline(std::cin, message);
            vcs.addCommit(message, author);
        } else if (choice == 2) {
            vcs.rollback();
        } else if (choice == 3) {
            vcs.showHistory();
        } else if (choice == 4) {
            vcs.showAnalytics();
        } else if (choice == 5) {
            vcs.showRecoveryReports();
        } else if (choice == 6) {
            std::cout << "\n\033[1;32mExiting Version Control System. Goodbye!\033[0m\n\n";
            break;
        } else {
            std::cout << "\033[1;31mInvalid choice. Try again.\033[0m\n";
        }
    }

    return 0;
}
