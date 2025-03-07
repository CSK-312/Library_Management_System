#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include "Account.hpp"
#include "Book.hpp"

// Forward declaration to avoid circular dependency.
class Library;

using namespace std;

class User {
protected:
    string Name;
    string user_id;
    string password;
    int borrowlimit;      // Maximum number of books that can be borrowed.
    int maxBorrowPeriod;  // Allowed borrow period (in days) before fines apply.
    double fine_rate;     // Fine rate per overdue day for each book.
    Account acc;          // Account holds records of borrowed books and history.
public:
    // Getters:
    string get_Name() const;
    string get_user_id() const;
    string get_password() const;
    int get_borrowlimit() const;
    int get_maxBorrowPeriod() const;
    double get_fine_rate() const;
    Account& get_acc() { return acc; }
    const Account& get_acc() const { return acc; }

    // Setters:
    void set_Name(const string &name);
    void set_user_id(const string &id);
    void set_password(const string &pwd);
    void set_borrowlimit(int limit);
    void set_maxBorrowPeriod(int period);
    void set_fine_rate(double rate);
    void set_acc(const Account &account);

    // Pure virtual functions for borrowing and returning books.
    virtual void Borrow_book(const string &book_id, Library *library) = 0;
    virtual void Return_book(const string &book_id, Library *library) = 0;

    // Other operations:
    void viewProfile() const;
    void updateProfile(const string &newName, const string &newPassword);

    // Virtual destructor.
    virtual ~User() {}
};

#endif // USER_HPP
