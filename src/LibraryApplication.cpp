#include "LibraryApplication.h"

#include "Book.h"
#include "LibraryException.h"
#include "StatisticsService.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <ctime>

LibraryApplication::LibraryApplication(
    LibraryService& service
)
    : service(service)
{
    initializeData();
}

std::string LibraryApplication::readLine(
    const std::string& prompt
)
{
    std::cout << prompt;

    std::string value;

    std::getline(
        std::cin,
        value
    );

    return value;
}

int LibraryApplication::readInt(
    const std::string& prompt
)
{
    while (true)
    {
        std::cout << prompt;

        int value;

        if (std::cin >> value)
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            return value;
        }

        std::cout
            << "Invalid input. Enter a number.\n";

        std::cin.clear();

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );
    }
}

void LibraryApplication::waitForEnter()
{
    std::cout
        << "\nPress Enter to continue...";

    std::cin.get();
}

bool LibraryApplication::login()
{
    std::cout
        << "\n========================================\n"
        << "          SMART LIBRARY LOGIN\n"
        << "========================================\n";

    std::string memberId =
        readLine("Enter Member ID: ");

    try
    {
        Member& member =
            service.getMember(memberId);

        currentUser = &member;

        std::cout
            << "\nLogin successful!\n";

        std::cout
            << "Welcome, "
            << member.getName()
            << "!\n";

        return true;
    }
    catch (const std::exception& e)
    {
        std::cout
            << "\nLogin failed: "
            << e.what()
            << '\n';

        return false;
    }
}

void LibraryApplication::run()
{
    std::cout
        << "\n========================================\n"
        << "       SMART LIBRARY MANAGEMENT SYSTEM\n"
        << "========================================\n";

    while (running)
    {
        currentUser = nullptr;

        if (!login())
        {
            int choice =
                readInt(
                    "\n1. Try Again\n"
                    "0. Exit\n"
                    "Choice: "
                );

            if (choice == 0)
            {
                break;
            }

            continue;
        }

        if (
            currentUser->getRole()
            == MemberRole::Librarian
        )
        {
            displayLibrarianMenu();
        }
        else
        {
            displayMemberMenu();
        }
    }

    std::cout
        << "\nThank you for using Smart Library!\n";
}

void LibraryApplication::displayLibrarianMenu()
{
    bool loggedIn = true;

    while (loggedIn)
    {
        std::cout
            << "\n========================================\n"
            << "          LIBRARIAN MENU\n"
            << "========================================\n";

        std::cout
            << "Welcome, "
            << currentUser->getName()
            << "\n\n";

        std::cout << "1. Add Book\n";
        std::cout << "2. Remove Book\n";
        std::cout << "3. Register Member\n";
        std::cout << "4. Remove Member\n";
        std::cout << "5. Search Books\n";
        std::cout << "6. View All Books\n";
        std::cout << "7. View All Members\n";
        std::cout << "8. View Statistics\n";
        std::cout << "9. View All Borrow Records\n";
        std::cout << "10. Logout\n";

        int choice =
            readInt("\nEnter choice: ");

        try
        {
            switch (choice)
            {
                case 1:
                    addBook();
                    break;

                case 2:
                    removeBook();
                    break;

                case 3:
                    registerMember();
                    break;

                case 4:
                    removeMember();
                    break;

                case 5:
                    searchBooks();
                    break;

                case 6:
                    showAllBooks();
                    break;

                case 7:
                    showAllMembers();
                    break;

                case 8:
                    showStatistics();
                    break;

                case 9: 
                    showAllBorrowRecords();
                    break; 

                case 10:
                    loggedIn = false;
                    break;

                default:
                    std::cout
                        << "Invalid choice.\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout
                << "\nError: "
                << e.what()
                << '\n';
        }

        if (loggedIn)
        {
            waitForEnter();
        }
    }
}

void LibraryApplication::displayMemberMenu()
{
    bool loggedIn = true;

    while (loggedIn)
    {
        std::cout
            << "\n========================================\n"
            << "             MEMBER MENU\n"
            << "========================================\n";

        std::cout
            << "Welcome, "
            << currentUser->getName()
            << "\n";

        std::cout
            << "Role: ";

        switch (currentUser->getRole())
        {
            case MemberRole::Student:
                std::cout << "Student\n";
                break;

            case MemberRole::Faculty:
                std::cout << "Faculty\n";
                break;

            case MemberRole::Librarian:
                std::cout << "Librarian\n";
                break;
        }

        std::cout << "\n";

        std::cout << "1. Available Books\n";
        std::cout << "2. Search Books\n";
        std::cout << "3. Borrow Book\n";
        std::cout << "4. Return Book\n";
        std::cout << "5. Reserve Book\n";
        std::cout << "6. View Statistics\n";
        std::cout << "7. View My Borrowing History\n";
        std::cout << "8. Logout\n";

        int choice =
            readInt("\nEnter choice: ");

        try
        {
            switch (choice)
            {
                case 1:
                    showAllBooks();
                    break;

                case 2:
                    searchBooks();
                    break;

                case 3:
                    borrowBook();
                    break;

                case 4:
                    returnBook();
                    break;

                case 5:
                    reserveBook();
                    break;

                case 6:
                    showStatistics();
                    break;

                case 7:
                    showMyBorrowingHistory();
                    break;
                    
                case 8:
                    loggedIn = false;
                    break;

                default:
                    std::cout
                        << "Invalid choice.\n";
            }
        }
        catch (const std::exception& e)
        {
            std::cout
                << "\nError: "
                << e.what()
                << '\n';
        }

        if (loggedIn)
        {
            waitForEnter();
        }
    }
}

void LibraryApplication::addBook()
{
    std::cout
        << "\n========== ADD BOOK ==========\n";

    std::string title =
        readLine("Title: ");

    std::string author =
        readLine("Author: ");

    std::string isbn =
        readLine("ISBN: ");

    std::string category =
        readLine("Category: ");

    int copies =
        readInt("Number of copies: ");

    Book book(
        title,
        author,
        isbn,
        category,
        copies
    );

    service.addBook(book);

    std::cout
        << "\nBook added successfully.\n";
}

void LibraryApplication::removeBook()
{
    std::cout
        << "\n========== REMOVE BOOK ==========\n";

    std::string isbn =
        readLine("Enter ISBN: ");

    service.removeBook(isbn);

    std::cout
        << "\nBook removed successfully.\n";
}

void LibraryApplication::registerMember()
{
    std::cout
        << "\n========== REGISTER MEMBER ==========\n";

    std::string id =
        readLine("Member ID: ");

    std::string name =
        readLine("Name: ");

    std::cout
        << "\n1. Student\n"
        << "2. Faculty\n"
        << "3. Librarian\n";

    int choice =
        readInt("Role: ");

    MemberRole role;

    switch (choice)
    {
        case 1:
            role = MemberRole::Student;
            break;

        case 2:
            role = MemberRole::Faculty;
            break;

        case 3:
            role = MemberRole::Librarian;
            break;

        default:
            throw std::runtime_error(
                "Invalid role."
            );
    }

    Member member(
        id,
        name,
        role
    );

    service.addMember(member);

    std::cout
        << "\nMember registered successfully.\n";
}

void LibraryApplication::removeMember()
{
    std::cout
        << "\n========== REMOVE MEMBER ==========\n";

    std::string memberId =
        readLine("Member ID: ");

    service.removeMember(memberId);

    std::cout
        << "\nMember removed successfully.\n";
}

void LibraryApplication::borrowBook()
{
    std::cout
        << "\n========== BORROW BOOK ==========\n";

    std::string isbn =
        readLine("ISBN: ");

    service.borrowBook(
        currentUser->getMemberId(),
        isbn
    );

    std::cout
        << "\nBook borrowed successfully.\n";
}
void LibraryApplication::returnBook()
{
    std::cout
        << "\n========== RETURN BOOK ==========\n";

    std::string isbn =
        readLine("ISBN: ");

    double fine =
        service.returnBook(
            currentUser->getMemberId(),
            isbn
        );

    std::cout
        << "\nBook returned successfully.\n";

    std::cout
        << "Fine: Rs."
        << fine
        << '\n';
}

void LibraryApplication::reserveBook()
{
    std::cout
        << "\n========== RESERVE BOOK ==========\n";

    std::string isbn =
        readLine("ISBN: ");

    service.reserveBook(
        currentUser->getMemberId(),
        isbn
    );

    std::cout
        << "\nBook reserved successfully.\n";
}

void LibraryApplication::searchBooks()
{
    std::cout
        << "\n========== SEARCH BOOKS ==========\n";

    std::cout
        << "1. Search by Title\n"
        << "2. Search by Author\n"
        << "3. Search by Category\n";

    int choice =
        readInt("Choice: ");

    std::string query =
        readLine("Search: ");

    std::vector<Book> results;

    switch (choice)
    {
        case 1:
            results =
                service.searchByTitle(query);
            break;

        case 2:
            results =
                service.searchByAuthor(query);
            break;

        case 3:
            results =
                service.searchByCategory(query);
            break;

        default:
            throw std::runtime_error(
                "Invalid search option."
            );
    }

    if (results.empty())
    {
        std::cout
            << "\nNo books found.\n";

        return;
    }

    std::cout
        << "\n========== RESULTS ==========\n";

    for (const Book& book : results)
    {
        std::cout
            << "\nTitle: "
            << book.getTitle();

        std::cout
            << "\nAuthor: "
            << book.getAuthor();

        std::cout
            << "\nISBN: "
            << book.getISBN();

        std::cout
            << "\nAvailable Copies: "
            << book.getAvailableCopies();

        std::cout
            << "\n-----------------------------\n";
    }
}

void LibraryApplication::showStatistics()
{
    LibraryStatistics statistics =
        service.getStatistics();

    std::cout
        << "\n========== LIBRARY STATISTICS ==========\n";

    std::cout
        << "\nMost Borrowed:\n";

    int rank = 1;

    for (
        const auto& book :
        statistics.mostBorrowedBooks
    )
    {
        std::cout
            << rank
            << ". "
            << book.title
            << " - "
            << book.borrowCount
            << " borrows\n";

        ++rank;
    }

    std::cout
        << "\nActive Members: "
        << statistics.activeMembers
        << '\n';

    std::cout
        << "Total Fines: Rs."
        << statistics.totalFinesCollected
        << '\n';

    std::cout
        << "Overdue Books: "
        << statistics.currentOverdueCount
        << '\n';

    std::cout
        << "\n=========================================\n";
}

void LibraryApplication::showAllBooks()
{
    const auto& books =
        service.getBooks();

    std::cout
        << "\n========== ALL BOOKS ==========\n";

    if (books.empty())
    {
        std::cout
            << "No books available.\n";

        return;
    }

    for (const auto& [isbn, book] : books)
    {
        std::cout
            << "\nTitle: "
            << book.getTitle();

        std::cout
            << "\nAuthor: "
            << book.getAuthor();

        std::cout
            << "\nISBN: "
            << book.getISBN();

        std::cout
            << "\nAvailable: "
            << book.getAvailableCopies();

        std::cout
            << "\n-----------------------------\n";
    }
}

void LibraryApplication::showAllMembers()
{
    const auto& members =
        service.getMembers();

    std::cout
        << "\n========== ALL MEMBERS ==========\n";

    if (members.empty())
    {
        std::cout
            << "No members registered.\n";

        return;
    }

    for (const auto& [id, member] : members)
    {
        std::cout
            << "\nID: "
            << member.getMemberId();

        std::cout
            << "\nName: "
            << member.getName();

        std::cout
            << "\n-----------------------------\n";
    }
}

void LibraryApplication::initializeData()
{
    // ==============================
    // Initial Members
    // ==============================

    if (service.getMembers().empty())
    {
        Member librarian(
            "L001",
            "Library Admin",
            MemberRole::Librarian
        );

        Member student(
            "S001",
            "Keerthana",
            MemberRole::Student
        );

        Member faculty(
            "F001",
            "Faculty User",
            MemberRole::Faculty
        );

        service.addMember(librarian);
        service.addMember(student);
        service.addMember(faculty);
    }

    // ==============================
    // Initial Books
    // ==============================

    if (service.getBooks().empty())
    {
        Book book1(
            "Clean Code",
            "Robert C. Martin",
            "9780132350884",
            "Programming",
            3
        );

        Book book2(
            "C++ Primer",
            "Stanley Lippman",
            "9780321714114",
            "Programming",
            2
        );

        Book book3(
            "Effective C++",
            "Scott Meyers",
            "9780321334879",
            "Programming",
            1
        );

        service.addBook(book1);
        service.addBook(book2);
        service.addBook(book3);
    }
}

std::string formatDate(
    std::chrono::system_clock::time_point time
)
{
    std::time_t t =
        std::chrono::system_clock::to_time_t(time);

    std::tm tm{};

#ifdef _WIN32
    localtime_s(&tm, &t);
#else
    localtime_r(&t, &tm);
#endif

    std::ostringstream oss;

    oss << std::put_time(
        &tm,
        "%d-%m-%Y"
    );

    return oss.str();
}

void LibraryApplication::showAllBorrowRecords()
{
    std::cout
        << "\n========================================\n"
        << "        ALL BORROWING RECORDS\n"
        << "========================================\n";

    const auto& records =
        service.getBorrowRecords();

    if (records.empty())
    {
        std::cout
            << "\nNo borrowing records found.\n";
        return;
    }

    for (const auto& entry : records)
    {
        const BorrowRecord& record = entry.second;

        std::cout
            << "\nRecord ID : "
            << record.getRecordId()
            << "\nMember ID : "
            << record.getMemberId()
            << "\nBook ISBN : "
            << record.getBookISBN()
            << "\nBorrowed  : "
            << formatDate(record.getBorrowDate())
            << "\nDue Date  : "
            << formatDate(record.getDueDate());

        if (record.isReturned())
        {
            std::cout
                << "\nReturned  : "
                << formatDate(record.getReturnDate())
                << "\nStatus    : RETURNED";
        }
        else
        {
            std::cout
                << "\nReturned  : -"
                << "\nStatus    : BORROWED";
        }

        std::cout
            << "\n----------------------------------------\n";
    }
}


void LibraryApplication::showMyBorrowingHistory()
{
    std::cout
        << "\n========================================\n"
        << "          MY BORROWING HISTORY\n"
        << "========================================\n";

    const auto& records =
        service.getBorrowRecords();

    bool found = false;

    for (const auto& entry : records)
    {
        const BorrowRecord& record = entry.second;

        // Show only the logged-in member's records
        if (record.getMemberId() != currentUser->getMemberId())
        {
            continue;
        }

        found = true;

        std::cout
            << "\nRecord ID : "
            << record.getRecordId()
            << "\nBook ISBN : "
            << record.getBookISBN()
            << "\nBorrowed  : "
            << formatDate(record.getBorrowDate())
            << "\nDue Date  : "
            << formatDate(record.getDueDate());

        if (record.isReturned())
        {
            std::cout
                << "\nReturned  : "
                << formatDate(record.getReturnDate())
                << "\nStatus    : RETURNED";
        }
        else
        {
            std::cout
                << "\nReturned  : -"
                << "\nStatus    : BORROWED";
        }

        std::cout
            << "\n----------------------------------------\n";
    }

    if (!found)
    {
        std::cout
            << "\nYou have no borrowing records.\n";
    }
}