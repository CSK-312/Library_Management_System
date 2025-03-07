#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include "User.hpp"
#include "Book.hpp"

// Forward declaration to avoid circular dependency.
class Library;

class Student : public User {
public:
    // Constructor.
    Student(const std::string &name, const std::string &id, const std::string &pwd);

    //View all books in the library
    void View_all_books(Library *library) const;

    // Borrow a book from the library.
    virtual void Borrow_book(const std::string &book_id, Library *library) override;

    // Return a book to the library.
    virtual void Return_book(const std::string &book_id, Library *library) override;

    //View all borrowed books
    void View_borrowed_books() const;

    //View Borrowing history
    void View_borrowing_history() const;

    // Display the total fine for all overdue books.
    void Total_fine() const;

    // Simulate paying the fine.
    void Pay_fine();

    // Display fine details for each currently borrowed book.
    void DisplayFines() const;
};

#endif // STUDENT_HPP


