#ifndef FACULTY_HPP
#define FACULTY_HPP

#include <iostream>
#include "User.hpp"
#include "Book.hpp"

// Forward declaration of Library to avoid circular dependency.
class Library;

using namespace std;

class Faculty : public User {
private:
    // Attributes.
    string notif;
public:
    // Constructor
    Faculty(const string &name, const string &id, const string &pwd);

    // Getter for notif.
    string get_notif() const { return notif; }

    // Setter for notif.
    void set_notif(const string &n) { notif = n; }

    //View all available books.
    void View_all_books(Library *library) const;

    // Borrow a book from the library.
    virtual void Borrow_book(const string &book_id, Library *library) override;

    // Return a book to the library (overdue check included).
    virtual void Return_book(const string &book_id, Library *library) override;

    // Reserve a book in the library.
    void Reserve_book(const string &book_id, Library *library);

    // View borrowed books.
    void View_borrowed_books() const;

    // View Borrowing History.
    void View_borrowing_history() const;
};

#endif // FACULTY_HPP


