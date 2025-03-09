#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <iostream>
#include "User.hpp"
#include "Book.hpp"

// Forward declaration to avoid circular dependency.
class Library;

class Student : public User {
private:
    // Attributes:
    string notif;
public:
    // Constructor.
    Student(const std::string &name, const std::string &id, const std::string &pwd);

    // Getter for notif.
    string get_notif() const { return notif; }

    // Setter for notif.
    void set_notif(const string &n) { notif = n; }

    //View all books in the library
    void View_all_books(Library *library) const;

    // Borrow a book from the library.
    virtual void Borrow_book(const std::string &book_id, Library *library) override;

    // Return a book to the library.
    virtual void Return_book(const std::string &book_id, Library *library) override;

    // Reserve a book from the library.
    void Reserve_book(const std::string &book_id, Library *library);

    //View all borrowed books
    void View_borrowed_books() const;

    //View Borrowing history
    void View_borrowing_history() const;

    // Display the total fine for all overdue books.
    void Total_fine() const;

    // Simulate paying the fine.
    void Pay_fine(double amount);

    // Display fine details for each currently borrowed book.
    void DisplayFines() const;
};

#endif // STUDENT_HPP


