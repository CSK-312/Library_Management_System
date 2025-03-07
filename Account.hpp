#ifndef ACCOUNT_HPP
#define ACCOUNT_HPP

#include <ctime>
#include <vector>
#include <iostream>
#include <iomanip>
#include <utility>
#include "Book.hpp"

using namespace std;

class Account {
private:
    // Each pair stores a pointer to a borrowed book and the time it was borrowed.
    vector<pair<Book*, time_t>> borrowedBooks;
    vector<pair<Book*, time_t>> borrowingHistory; // History of returned books.
public:
    // Get the list of borrowed books.
    vector<pair<Book*, time_t>>& getBorrowedBooks() { return borrowedBooks; }
    const vector<pair<Book*, time_t>>& getBorrowedBooks() const { return borrowedBooks; }


    // Add a borrowed book record with the current time.
    void addBorrowedBook(Book* book);

    //Add to Borrowing history
    void addToBorrowingHistory(Book* book, time_t returnTime);

    // Remove a borrowed book record by book_id, return how many days it was borrowed.
    int removeBorrowedBookAndReturnDaysBorrowed(const string &book_id);

    // Return the number of currently borrowed books.
    size_t getBorrowedBookCount() const;

    //Return Borrowing history
    vector<pair<Book*, time_t>>& getBorrowingHistory() { return borrowingHistory; }
    const vector<pair<Book*, time_t>>& getBorrowingHistory() const { return borrowingHistory; }



    // Calculate the total fine for all overdue books.
    double calculateTotalFine(int maxBorrowPeriod, double fine_rate) const;

    // Check if there is any overdue book regardless of fine rate.
    bool hasOverdueBooks(int maxBorrowPeriod) const;

    // Display fine details for each currently borrowed book.
    void displayFines(int maxBorrowPeriod, double fine_rate) const;
};

#endif // ACCOUNT_HPP
