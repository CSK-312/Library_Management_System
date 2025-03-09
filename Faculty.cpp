#include "Faculty.hpp"
#include "Library.hpp"

Faculty::Faculty(const string &name, const string &id, const string &pwd) {
    this->Name = name;
    this->borrowlimit = 5;
    this->maxBorrowPeriod = 30;
    this->fine_rate = 0;
    this->user_id = id;
    this->password = pwd;
    notif = "";
}


void Faculty::View_all_books(Library *library) const {
    library->show_all_books();
}

void Faculty::Reserve_book(const string &book_id, Library *library) {
    Book *book = library->get_book(book_id);
    if (!book) {
        cout << "Book not found in the library." << endl;
        return;
    }
    if (book->get_status() == Status::RESERVED) {
        if(book->get_reservedBy_facid() == this->get_user_id()) {
            cout << "You have already reserved this book." << endl;
            return;
        }
        cout << "The book is already reserved." << endl;
        return;
    }else if(book->get_status() == Status::AVAILABLE) {
        book->set_reservedBy_facid(this->get_user_id());
        cout << "Book reserved successfully." << endl;
        book->set_status(Status::RESERVED);
        return;
    }else{
        // If the book is borrowed but is reserved for next usage.
        if(!book->get_reservedBy_facid().empty() || !book->get_reservedBy_studid().empty()) {
            if(book->get_reservedBy_facid() == this->get_user_id()) {
                cout << "You have already reserved this book." << endl;
                return;
            }
            cout << "The book is reserved by another user." << endl;
            return;
        }else{
            book->set_reservedBy_facid(this->get_user_id());
            cout << "Book reserved successfully." << endl;
            // Here we dont change the status to reserved because the book is borrowed.
            return;
        }
    }
}

void Faculty::Borrow_book(const string &book_id, Library *library) {
    // If the faculty has this book in borrowed list, then he/she cannot borrow it again.
    for(const auto &record : acc.getBorrowedBooks()) {
        if(record.first->get_bookid() == book_id) {
            cout << "You have already borrowed this book." << endl;
            return;
        }
    }
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
        // If the book is borrowed, ask if the user wants to reserve it for next usage.
        cout << "The book is currently borrowed." << endl;
        cout << "You can reserve the book if you want." << endl;
        cout << "1. Reserve the book" << endl;
        cout << "2. Cancel" << endl;
        int choice;
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            // Reserve the book.
            Reserve_book(book_id, library);
        }
        return;
    }else if(book->get_status() == Status::RESERVED) {
        if(book->get_reservedBy_facid() == this->get_user_id()) {
            acc.addBorrowedBook(book);
            book->set_reservedBy_facid("");
            book->set_status(Status::BORROWED);
            cout << "Book borrowed successfully." << endl;
            return;
        }
        cout << "The book is reserved by another user." << endl;
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
    int daysBorrowed = acc.getDaysBorrowed(book_id);
    if (daysBorrowed == -1) {
        cout << "Book not found in your borrowed list." << endl;
        return;
    }

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
    
    // If the book is reserved by someone else notify them.
    if(!book->get_reservedBy_facid().empty() || !book->get_reservedBy_studid().empty()) {
        book->set_status(Status::RESERVED);
        string n = "The book you reserved (ID: " + book->get_bookid() + ", Title: " + book->get_Title() + ") is now available.";
        // Notify the user who reserved the book.
        Student* stud = library->get_student(book->get_reservedBy_studid());
        Faculty* fac = library->get_faculty(book->get_reservedBy_facid());
        if(stud != nullptr) {
            stud->set_notif(n);
            book->set_reservedBy_studid("");
        }else if(fac != nullptr) {
            fac->set_notif(n);
            book->set_reservedBy_facid("");
        }
        cout << "Book returned successfully." << endl;
        return;
    }

    // Mark the book as available.
    book->set_status(Status::AVAILABLE);
    cout << "Book returned successfully." << endl;
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
        std::cout << "You have no borrowing history." << std::endl;
        return;
    }
    std::cout << "Your borrowing history: " << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    std::cout << std::left << std::setw(15) << "Book ID" 
              << std::setw(30) << "Title" 
              << std::setw(20) << "Borrowed on" 
              << std::setw(20) << "Returned on" 
              << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    for (const auto &record : acc.getBorrowingHistory()) {
        Book* book = record.first;
        time_t borrowTime = record.second.first;
        time_t returnTime = record.second.second;
        tm* localBorrowTime = localtime(&borrowTime);
        tm* localReturnTime = localtime(&returnTime);
        std::cout << std::left << std::setw(15) << book->get_bookid()
                  << std::setw(30) << book->get_Title()
                  << std::setw(20) << std::put_time(localBorrowTime, "%Y-%m-%d")
                  << std::setw(20) << std::put_time(localReturnTime, "%Y-%m-%d")
                  << std::endl;
    }
}
