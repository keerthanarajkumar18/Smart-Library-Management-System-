#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book
{
    private:
        std::string title;
        std::string author;
        std::string isbn;
        std::string category;

        int totalCopies;
        int availableCopies;

    public:
        Book(const std::string &title, const std::string &author, const std::string &isbn, const std::string &category, int totalCopies);
        const std::string &getTitle() const;
        const std::string& getAuthor() const;
        const std::string& getISBN() const;
        const std::string& getCategory() const;

        int getTotalCopies() const;
        int getAvailableCopies() const;

        void borrowCopy();
        void returnCopy();
};

#endif // BOOK_H