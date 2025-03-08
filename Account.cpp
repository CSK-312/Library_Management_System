#include "Account.hpp"

void Account::addBorrowedBook(Book* book) {
    borrowedBooks.push_back(make_pair(book, time(nullptr)));
}

void Account::addToBorrowingHistory(Book* book, time_t t1, time_t t2) {
    borrowingHistory.push_back(make_pair(book, make_pair(t1, t2)));
}

void Account::removeBorrowedBook(const string &book_id) {
    time_t currentTime = time(nullptr);
    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
        if (it->first->get_bookid() == book_id) {
            // It is also added to borrowing history.
            borrowingHistory.push_back(make_pair(it->first, make_pair(it->second, currentTime)));
            borrowedBooks.erase(it);
            return;
        }
    }
}

double Account::calculateFine(int maxBorrowPeriod, double fine_rate) const {
    time_t currentTime = time(nullptr);
    double totalFine = 0.0;
    for (const auto &record : borrowedBooks) {
        double daysBorrowed = difftime(currentTime, record.second) / (60 * 60 * 24);
        int daysOverdue = static_cast<int>(daysBorrowed) - maxBorrowPeriod;
        if (daysOverdue > 0) {
            totalFine += daysOverdue * fine_rate;
        }
    }
    return totalFine;
}

double Account::get_Totalfine() const {
    return Fine + calculateFine(5, 10);
}


int Account::getDaysBorrowed(const string &book_id) const {
    time_t currentTime = time(nullptr);
    for (const auto &record : borrowedBooks) {
        if (record.first->get_bookid() == book_id) {
            // Calculate the number of full days elapsed since the book was borrowed.
            int daysBorrowed = static_cast<int>(difftime(currentTime, record.second) / (60 * 60 * 24));
            return daysBorrowed;
        }
    }
    return -1; // Indicates the book was not found in borrowedBooks.
}



size_t Account::getBorrowedBookCount() const {
    return borrowedBooks.size();
}

bool Account::hasOverdueBooks(int maxBorrowPeriod) const {
    time_t currentTime = time(nullptr);
    for (const auto &record : borrowedBooks) {
        int daysBorrowed = getDaysBorrowed(record.first->get_bookid());
        if (daysBorrowed > maxBorrowPeriod) {
            return true;
        }
    }
    return false;
}

void Account::displayFines(int maxBorrowPeriod, double fine_rate) const {
    time_t currentTime = time(nullptr);
    for (const auto &record : borrowedBooks) {
        int daysBorrowed = getDaysBorrowed(record.first->get_bookid());
        int daysOverdue = daysBorrowed - maxBorrowPeriod;
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
