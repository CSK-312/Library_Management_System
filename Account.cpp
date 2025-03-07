#include "Account.hpp"

void Account::addBorrowedBook(Book* book) {
    borrowedBooks.push_back(make_pair(book, time(nullptr)));
}

void Account::addToBorrowingHistory(Book* book, time_t returnTime) {
    borrowingHistory.push_back(make_pair(book, returnTime));
}


int Account::removeBorrowedBookAndReturnDaysBorrowed(const string &book_id) {
    time_t currentTime = time(nullptr);
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
        if (it->first->get_bookid() == book_id) {
            // Calculate how many days the book was borrowed.
            double days = difftime(currentTime, it->second) / (60 * 60 * 24);
            int daysBorrowed = static_cast<int>(days);

            // Add the book and its return time to the borrowing history (now a pair).
            borrowingHistory.push_back(make_pair(it->first, currentTime));
            // Remove the book from the currently borrowed books.
            borrowedBooks.erase(it);
            return daysBorrowed;
        }
    }
    return -1; // Indicates not found.
}


size_t Account::getBorrowedBookCount() const {
    return borrowedBooks.size();
}

double Account::calculateTotalFine(int maxBorrowPeriod, double fine_rate) const {
    double totalFine = 0.0;
    time_t currentTime = time(nullptr);
    for (const auto &record : borrowedBooks) {
        double daysBorrowed = difftime(currentTime, record.second) / (60 * 60 * 24);
        int daysOverdue = static_cast<int>(daysBorrowed) - maxBorrowPeriod;
        if (daysOverdue > 0) {
            totalFine += daysOverdue * fine_rate;
        }
    }
    return totalFine;
}

bool Account::hasOverdueBooks(int maxBorrowPeriod) const {
    time_t currentTime = time(nullptr);
    for (const auto &record : borrowedBooks) {
        double daysBorrowed = difftime(currentTime, record.second) / (60 * 60 * 24);
        if (static_cast<int>(daysBorrowed) > maxBorrowPeriod) {
            return true;
        }
    }
    return false;
}

void Account::displayFines(int maxBorrowPeriod, double fine_rate) const {
    time_t currentTime = time(nullptr);
    for (const auto &record : borrowedBooks) {
        double daysBorrowed = difftime(currentTime, record.second) / (60 * 60 * 24);
        int daysOverdue = static_cast<int>(daysBorrowed) - maxBorrowPeriod;
        if (daysOverdue > 0) {
            cout << "Book \"" << record.first->get_Title() 
                 << "\" is overdue by " << daysOverdue 
                 << " days. Fine: " << daysOverdue * fine_rate << endl;
        } else {
            cout << "Book \"" << record.first->get_Title() 
                 << "\" is not overdue." << endl;
        }
    }
}
