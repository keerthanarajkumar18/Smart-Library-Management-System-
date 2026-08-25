#ifndef LIBRARY_APPLICATION_H
#define LIBRARY_APPLICATION_H

#include "LibraryService.h"
#include "Member.h"

#include <string>
#include <vector>

class LibraryApplication
{
private:

    LibraryService& service;

    Member* currentUser = nullptr;

    bool running = true;

    // Data initialization
    void initializeData();

    // Login
    bool login();

    // Menus
    void displayMainMenu();
    void displayLibrarianMenu();
    void displayMemberMenu();

    // Librarian operations
    void addBook();
    void removeBook();
    void registerMember();
    void removeMember();

    // General operations
    void searchBooks();
    void borrowBook();
    void returnBook();
    void reserveBook();

    // Display
    void showStatistics();
    void showAllBooks();
    void showAllMembers();

    // Borrowing records
    void showAllBorrowRecords();
    void showMyBorrowingHistory();

    // Helpers
    void waitForEnter();
    int readInt(const std::string& prompt);
    std::string readLine(const std::string& prompt);

public:

    explicit LibraryApplication(
        LibraryService& service
    );

    void run();
    
};

#endif

