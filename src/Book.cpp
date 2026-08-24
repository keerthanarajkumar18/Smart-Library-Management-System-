#include "Book.h"
#include <stdexcept>

Book::Book(const std::string& title,
           const std::string& author,
           const std::string& isbn,
           const std::string& category,
           int totalCopies)        
    : title(title),
      author(author),
      isbn(isbn),
      category(category),
      totalCopies(totalCopies),
      availableCopies(totalCopies)
{
}

const std::string& Book::getTitle() const {
    return title;
}

const std::string& Book::getAuthor() const {
    return author;
}

const std::string& Book::getISBN() const {
    return isbn;
}

const std::string& Book::getCategory() const {
    return category;
}

int Book::getTotalCopies() const {
    return totalCopies;
}

int Book::getAvailableCopies() const {
    return availableCopies;
}

void Book::borrowCopy() {
    if (availableCopies > 0) {
        --availableCopies;
    } else {
        throw std::runtime_error("No available copies to borrow.");
    }
}

void Book::returnCopy() {
    if (availableCopies < totalCopies) {
        ++availableCopies;
    } else {
        throw std::runtime_error("All copies are already returned.");
    }
}