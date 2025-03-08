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
    vector<pair<Book*, pair<time_t, time_t>>> borrowingHistory;
    double Fine; // *It stores the total fine for overdue books that were returned and is updated accordingly when the user pays an amount.*
    // Fine for currently borrowed books is calculated dynamically.
    // Total fine is the sum of the fine for overdue returned books and the fine for currently borrowed books.
public:
    // Constructor.
    Account() : Fine(0.0) {}

    // Get the list of borrowed books.
    vector<pair<Book*, time_t>>& getBorrowedBooks() { return borrowedBooks; }
    const vector<pair<Book*, time_t>>& getBorrowedBooks() const { return borrowedBooks; }

    // Get the value of "attribute" fine.
    int getFine() const { return Fine; }

    // Set the value of "attribute" fine.
    void setFine(int fine) { Fine = fine; }

    // Get the "Total" fine.(Here the total fine includes the fine for overdue books which were returned and the fine for currently borrowed books)
    // This is a dynamic calculation.
    double get_Totalfine() const;

    // Add a borrowed book record with the current time.
    void addBorrowedBook(Book* book);

    // Remove a borrowed book record.
    void removeBorrowedBook(const string &book_id);

    //Add to Borrowing history
    void addToBorrowingHistory(Book* book, time_t t1, time_t t2);

    //Return how many days it was borrowed.
    int getDaysBorrowed(const string &book_id) const;

    // Return the number of currently borrowed books.
    size_t getBorrowedBookCount() const;

    //Return Borrowing history
    vector<pair<Book*, pair<time_t, time_t>>>& getBorrowingHistory() { return borrowingHistory; }
    const vector<pair<Book*, pair<time_t, time_t>>>& getBorrowingHistory() const { return borrowingHistory; }

    // Check if there is any overdue book regardless of fine rate.
    bool hasOverdueBooks(int maxBorrowPeriod) const;

    //Calculate the fine only for overdue borrowed books.(This is dynamicallly calculated)
    double calculateFine(int maxBorrowPeriod, double fine_rate) const;

    // Display fine details for each currently borrowed book.
    void displayFines(int maxBorrowPeriod, double fine_rate) const;
};

#endif // ACCOUNT_HPP
