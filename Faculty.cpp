#include "Faculty.hpp"
#include "Library.hpp" // Full definition of Library is required here

Faculty::Faculty(const string &name, const string &id, const string &pwd) {
    this->Name = name;
    this->borrowlimit = 5;
    this->maxBorrowPeriod = 30;
    this->fine_rate = 0;
    this->user_id = id;
    this->password = pwd;
}


void Faculty::View_all_books(Library *library) const {
    library->show_all_books();
}


void Faculty::Borrow_book(const string &book_id, Library *library) {
    bool hasOverdue = acc.hasOverdueBooks(maxBorrowPeriod);

    // If user is faculty but has overdue books, block.
    if (hasOverdue) {
        cout << "You cannot borrow a book because you have overdue books." << endl;
        cout << "Please return all overdue books before borrowing a new one." << endl;
        return;
    }

    // Check borrowing limit.
    if (acc.getBorrowedBookCount() >= static_cast<size_t>(borrowlimit)) {
        cout << "Alert: Your borrowing limit (" << borrowlimit << " books) has been reached." << endl;
        cout << "Kindly return a book to free up a slot for a new one." << endl;
        return;
    }

    // Retrieve the book from the library.
    Book *book = library->get_book(book_id);
    if (!book) {
        cout << "Book not found in the library." << endl;
        return;
    }
    // Check if the book is available.
    if (book->get_status() == Status::BORROWED) {
        cout << "The book is currently unavailable." << endl;
        return;
    }

    // Borrow the book.
    acc.addBorrowedBook(book);
    book->set_status(Status::BORROWED);
    cout << "Book borrowed successfully." << endl;
}

void Faculty::Return_book(const string &book_id, Library *library) {
    Book *book = library->get_book(book_id);
    if (!book) {
        cout << "Book not found in the library." << endl;
        return;
    }
    // Ask Account how many days the book was borrowed.
    int daysBorrowed = acc.removeBorrowedBookAndReturnDaysBorrowed(book_id);
    if (daysBorrowed == -1) {
        cout << "Book not found in your borrowed list." << endl;
        return;
    }

    // Mark the book as available.
    book->set_status(Status::AVAILABLE);

    // Show success message.
    cout << "Book returned successfully." << endl;

    // Overdue check for this specific book.
    int daysOverdue = daysBorrowed - maxBorrowPeriod;
    if (daysOverdue > 0) {
        cout << "You are " << daysOverdue << " day(s) overdue for returning this book." << endl;
    }

    // After returning, check total overdue books.
    bool hasOverdue = acc.hasOverdueBooks(maxBorrowPeriod);

    // If user is faculty but still has overdue books, show a reminder.
    if (hasOverdue) {
        cout << "You still have overdue books. Please return them before borrowing new books." << endl;
    }
}

void Faculty::View_borrowed_books() const {
    if(acc.getBorrowedBooks().empty()) {
        std::cout << "You have not borrowed any books yet." << std::endl;
        return;
    }
    std::cout << "You have borrowed the following books: " << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    std::cout << std::left << std::setw(15) << "Book ID" 
              << std::setw(30) << "Title" 
              << std::setw(20) << "Borrowed on" 
              << std::endl;
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

void Faculty::View_borrowing_history() const {
    if(acc.getBorrowingHistory().empty()) {
        std::cout << "You have not borrowed any books in the past." << std::endl;
        return;
    }
    std::cout << "Your borrowing history: " << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    std::cout << std::left << std::setw(15) << "Book ID" 
              << std::setw(30) << "Title" 
              << std::setw(20) << "Returned on" 
              << std::endl;
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
