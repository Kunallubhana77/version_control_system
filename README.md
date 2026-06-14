# 2.1 Project Title
Custom Version Control System (VCS)

# 2.2 Problem Statement
Managing code changes across different versions of software development can be challenging. Without a robust tracking mechanism, developers can lose code, find it difficult to revert to previous stable versions after a breaking change, and struggle to coordinate or track contributions from multiple developers. A reliable version control mechanism is required to maintain a history of all modifications and facilitate safe rollbacks.

# 2.3 Objectives
- To implement a basic version control system that records code commits with unique IDs, author names, timestamps, and commit messages.
- To allow developers to easily push new commits to the version history.
- To provide a rollback engine that allows reverting the state to previous stable commits if errors are introduced.
- To maintain a recovery log for rolled-back commits to prevent accidental loss of data.
- To offer an intuitive terminal-based user interface (TUI) with a dashboard displaying recent activity, developer analytics, and version history.
- To optionally generate detailed reports for code recovery using a Python script.

# 2.4 System Overview / Architecture
The system is built as a command-line application in C++11, with reporting features in Python. The architecture consists of the following key components:
- **Main App Loop (`main.cpp`)**: Drives the interactive Terminal UI, handling user inputs and menu navigation.
- **VersionControl Class (`VersionControl.h/.cpp`)**: The core engine of the system. Manages the active commit history, the recovery log, and renders the TUI.
- **Commit Class (`Commit.h/.cpp`)**: Represents an individual snapshot of code. Stores metadata such as ID, message, timestamp, and author.
- **Stack Data Structure (`Stack.h`)**: A custom generic linked-list-based Stack implementation used to store the sequence of commits.

**Architecture Flowchart:**
![Flowchart](assets/flowchart.png)

# 2.5 Data Structures and Algorithms Used
- **Linked-List Based Stack (`Stack<T>`)**: Used as the primary data structure to store `Commit` objects. This choice allows $O(1)$ time complexity for both adding a new commit (`push`) and reverting a commit (`pop`). It strictly enforces LIFO (Last-In-First-Out) operations essential for chronological versioning and rollbacks.
- **Standard Vector (`std::vector<Commit>`)**: Used to maintain the `recoveryLog`. It stores commits that have been rolled back, allowing for dynamic resizing and $O(1)$ amortized insertion at the end.
- **Hash Map / Dictionary (`std::map<std::string, int>`)**: Used in the analytics dashboard to calculate the number of commits per developer efficiently.
- **Traversal Algorithm**: A simple linked-list traversal is used to display the commit history from the stack without modifying its contents.

# 2.6 Implementation Approach
- The project is implemented using Object-Oriented Programming (OOP) principles in C++.
- A generic `Stack` template class handles core LIFO operations safely (throwing exceptions on underflow).
- The `VersionControl` class encapsulates the application's state, keeping the `commitStack` and `recoveryLog` private.
- The TUI uses ANSI escape codes for rich text formatting (colors, bold text) and basic animations using `std::this_thread::sleep_for`.
- The user interacts via a simple menu loop that validates numeric input to prevent application crashes on invalid input.
- A `Makefile` is used to build the C++ application easily.

# 2.7 Time and Space Complexity Analysis
- **Pushing a Commit (`addCommit`)**:
  - Time Complexity: $O(1)$ (Stack push operation).
  - Space Complexity: $O(1)$ extra space per commit node.
- **Rolling Back (`rollback`)**:
  - Time Complexity: $O(1)$ for Stack pop and Vector push_back (amortized).
  - Space Complexity: $O(1)$ extra space for moving the commit reference.
- **Viewing History (`showHistory`)**:
  - Time Complexity: $O(N)$ where $N$ is the number of active commits (requires traversing the stack).
  - Space Complexity: $O(N)$ to temporarily store commits in a vector to print them chronologically (bottom-up).
- **Viewing Analytics (`showAnalytics`)**:
  - Time Complexity: $O(N \log K)$ where $N$ is the number of commits and $K$ is the number of unique authors (due to `std::map` insertions).
  - Space Complexity: $O(K)$ to store author statistics.
- **Overall Space Complexity**: $O(N + M)$ where $N$ is the number of active commits in the stack and $M$ is the number of rolled-back commits in the recovery log.

# 2.8 Execution Steps
1. Ensure you have a `g++` compiler (with C++11 support), `make` build utility, and `python3` (for report generation) installed.
2. Clone the repository:
   ```bash
   git clone <your-repository-url>
   cd svc
   ```
3. Build the C++ application using `make`:
   ```bash
   make
   ```
4. Run the application:
   ```bash
   ./vcs_app
   ```
5. To clean the compiled files, you can run:
   ```bash
   make clean
   ```

6. (Optional) Run the report generation script:
   ```bash
   python3 generate_report.py
   ```

# 2.9 Sample Inputs and Outputs
**Input:**
```
1
Alice
Initial Setup
1
Bob
Added authentication
```
**Output:**
```
[+] Processing Commit...
✅ Commit successfully added! [ID: 1]
[+] Processing Commit...
✅ Commit successfully added! [ID: 2]
```

**Input (Rollback):**
```
2
```
**Output:**
```
[-] Reverting changes...
⚠️  Rollback successful! Removed Commit [ID: 2]
➜ Restored to previous stable version [ID: 1]
```

# 2.10 Screenshots
- **Dashboard:**
  ![Dashboard](assets/first.png)
- **Commit History:**
  ![Commit History](assets/second.png)
- **Analytics:**
  ![Analytics](assets/third.png)

# 2.11 Results and Observations
- The application successfully mimics the fundamental operations of a version control system like Git (specifically `git commit` and `git reset`).
- The use of a linked-list stack ensures that memory is allocated dynamically and operations remain highly efficient ($O(1)$) compared to using a dynamic array.
- The TUI with color formatting makes the application engaging and easy to use.
- Validation logic properly handles invalid alphanumeric inputs from users without crashing.

# 2.12 Conclusion
This Custom Version Control system successfully demonstrates the practical application of the Stack data structure and basic Object-Oriented design in C++. It provides a sturdy, lightweight framework for managing version history, complete with a recovery mechanism and developer analytics. Future enhancements could include branching capabilities (using tree or graph data structures) and persistent file-system storage for commits.

