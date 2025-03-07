#include "Student.hpp"
#include "Library.hpp"
#include <iomanip> 

Student::Student(const std::string &name, const std::string &id, const std::string &pwd) {
    this->Name = name;
    this->borrowlimit = 3;
    this->maxBorrowPeriod = 15;
    this->fine_rate = 10;
    this->user_id = id;
    this->password = pwd;
}

void Student::View_all_books(Library *library) const {
    library->show_all_books();
}

void Student::Borrow_book(const std::string &book_id, Library *library) {
    double currentFine = acc.calculateTotalFine(maxBorrowPeriod, fine_rate);

    // If user has a fine, block.
    if (currentFine) {
        std::cout << "You cannot borrow a book because you have a fine of: " << currentFine << "." << std::endl;
        std::cout << "Please clear your fine to borrow a new book." << std::endl;
        return;
    }

    // Check borrowing limit.
    if (acc.getBorrowedBookCount() >= static_cast<size_t>(borrowlimit)) {
        std::cout << "Alert: Your borrowing limit (" << borrowlimit << " books) has been reached." << std::endl;
        std::cout << "Kindly return a book to free up a slot for a new one." << std::endl;
        return;
    }

    // Retrieve the book from the library.
    Book *book = library->get_book(book_id);
    if (!book) {
        std::cout << "Book not found in the library." << std::endl;
        return;
    }
    // Check if the book is available.
    if (book->get_status() == Status::BORROWED) {
        std::cout << "The book is currently unavailable." << std::endl;
        return;
    }

    // Borrow the book.
    acc.addBorrowedBook(book);
    book->set_status(Status::BORROWED);
    std::cout << "Book borrowed successfully." << std::endl;
}

void Student::Return_book(const std::string &book_id, Library *library) {
    Book *book = library->get_book(book_id);
    if (!book) {
        std::cout << "Book not found in the library." << std::endl;
        return;
    }
    // Ask Account how many days the book was borrowed.
    int daysBorrowed = acc.removeBorrowedBookAndReturnDaysBorrowed(book_id);
    if (daysBorrowed == -1) {
        std::cout << "Book not found in your borrowed list." << std::endl;
        return;
    }

    // Mark the book as available.
    book->set_status(Status::AVAILABLE);

    //Add it to borrowing history

    std::cout << "Book returned successfully." << std::endl;

    // Overdue check for this specific book.
    int daysOverdue = daysBorrowed - maxBorrowPeriod;
    if (daysOverdue > 0) {
        std::cout << "You are " << daysOverdue << " day(s) overdue for returning this book." << std::endl;
        // For students (fine_rate > 0), display the specific fine for this overdue.
        if (fine_rate > 0) {
            double overdueFine = daysOverdue * fine_rate;
            std::cout << "Your fine for this overdue is: " << overdueFine << std::endl;
        }
    }

    // After returning, check total fines or overdue books.
    double currentFine = acc.calculateTotalFine(maxBorrowPeriod, fine_rate);
    bool hasOverdue = acc.hasOverdueBooks(maxBorrowPeriod);

    // If user is a student and still has a fine, ask to clear it.
    if (fine_rate > 0 && currentFine > 0) {
        std::cout << "You still have an outstanding total fine of: " << currentFine << "." << std::endl;
        std::cout << "Please clear your fine to return books." << std::endl;
    }
}

void Student::View_borrowed_books() const {
    if(acc.getBorrowedBookCount() == 0) {
        std::cout << "You have not borrowed any books." << std::endl;
        return;
    }
    std::cout << std::string(65, '-') << std::endl;
    std::cout << std::left << std::setw(15) << "Book ID" 
              << std::setw(30) << "Title" 
              << std::setw(20) << "Borrowed on" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    for (const auto &record : acc.getBorrowedBooks()) {
        Book* book = record.first;
        time_t borrowTime = record.second;
        tm* localTime = localtime(&borrowTime);
        std::cout << std::left << std::setw(15) << book->get_bookid()
                  << std::setw(30) << book->get_Title()
                  << std::setw(20) << std::put_time(localTime, "%Y-%m-%d")
                  << std::endl;
    }
}

void Student::View_borrowing_history() const {
    if(acc.getBorrowingHistory().empty()) {
        std::cout << "You have no borrowing history." << std::endl;
        return;
    }
    std::cout << std::string(65, '-') << std::endl;
    std::cout << std::left << std::setw(15) << "Book ID" 
              << std::setw(30) << "Title" 
              << std::setw(20) << "Returned on" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    for (const auto &record : acc.getBorrowingHistory()) {
        Book* book = record.first;
        time_t returnTime = record.second;
        tm* localTime = localtime(&returnTime);
        std::cout << std::left << std::setw(15) << book->get_bookid()
                  << std::setw(30) << book->get_Title()
                  << std::setw(20) << std::put_time(localTime, "%Y-%m-%d")
                  << std::endl;
    }
}

void Student::Total_fine() const {
    double totalFine = acc.calculateTotalFine(maxBorrowPeriod, fine_rate);
    std::cout << "The total fine for overdue books is: " << totalFine << std::endl;
}

void Student::Pay_fine() {
    std::cout << "Your fine is cleared successfully." << std::endl;
}

void Student::DisplayFines() const {
    acc.displayFines(maxBorrowPeriod, fine_rate);
}
