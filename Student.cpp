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
    notif = "";
}

void Student::View_all_books(Library *library) const {
    library->show_all_books();
}

void Student::Reserve_book(const std::string &book_id, Library *library) {
    Book *book = library->get_book(book_id);
    if (!book) {
        std::cout << "Book not found in the library." << std::endl;
        return;
    }
    if (book->get_status() == Status::RESERVED) {
        if(book->get_reservedBy_studid() == this->get_user_id()) {
            std::cout << "You have already reserved this book." << std::endl;
            return;
        }
        std::cout << "The book is already reserved." << std::endl;
        return;
    }else if(book->get_status() == Status::AVAILABLE) {
        book->set_reservedBy_studid(this->get_user_id());
        std::cout << "Book reserved successfully." << std::endl;
        book->set_status(Status::RESERVED);
        return;
    }else{
        // If the book is borrowed but is reserved for next usage.
        if(!book->get_reservedBy_facid().empty() || !book->get_reservedBy_studid().empty()) {
            if(book->get_reservedBy_studid() == this->get_user_id()) {
                std::cout << "You have already reserved this book." << std::endl;
                return;
            }
            std::cout << "The book is reserved by another user." << std::endl;
            return;
        }else{
            book->set_reservedBy_studid(this->get_user_id());
            std::cout << "Book reserved successfully." << std::endl;
            // Here we dont change the status to reserved because the book is borrowed.
            return;
        }
    }
}

void Student::Borrow_book(const std::string &book_id, Library *library) {
    // If the student has this book in borrowed list, then he/she cannot borrow it again.
    for(const auto &record : acc.getBorrowedBooks()) {
        if(record.first->get_bookid() == book_id) {
            std::cout << "You have already borrowed this book." << std::endl;
            return;
        }
    }
    int TotalFine = acc.get_Totalfine();
    if (TotalFine) {
        std::cout << "You have a fine of: " << TotalFine << std::endl <<  " Please clear your fine to borrow a book." << std::endl;
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
        std::cout << "The book is currently borrowed." << std::endl;
        std::cout << "You can reserve the book if you want." << std::endl;
        std::cout << "1. Reserve the book" << std::endl;
        std::cout << "2. Cancel" << std::endl;
        std::cout << "Enter your choice: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore();
        if (choice == 1) {
            // Reserve the book.
            Reserve_book(book_id, library);
        }
        return;
    }else if(book->get_status() == Status::RESERVED) {
        if(book->get_reservedBy_studid() == this->get_user_id()) {
            acc.addBorrowedBook(book);
            book->set_reservedBy_studid("");
            book->set_status(Status::BORROWED);
            std::cout << "Book borrowed successfully." << std::endl;
            return;
        }
        std::cout << "The book is reserved by another user." << std::endl;
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
    int daysBorrowed = acc.getDaysBorrowed(book_id);

    if (daysBorrowed == -1) {
        std::cout << "Book not found in your borrowed list." << std::endl;
        return;
    }
    // Remove the book from borrowed list and it is added to the borrowing history.
    acc.removeBorrowedBook(book_id);

    // Overdue check for this specific book.
    int daysOverdue = daysBorrowed - maxBorrowPeriod;
    int overdueFine = daysOverdue * fine_rate;
    if (daysOverdue > 0) {
        std::cout << "You are " << daysOverdue << " day(s) overdue for returning this book." << std::endl;
        std::cout << "Your fine for this overdue is: " << overdueFine << std::endl;

        // After returning, update total fine.
        acc.setFine(acc.getFine() + overdueFine);
    }

    //If it is reserved by someone else notify them.
    if(!book->get_reservedBy_facid().empty() || !book->get_reservedBy_studid().empty()) {
        book->set_status(Status::RESERVED);
        std::string n = "The book you reserved (ID: " + book->get_bookid() + " | Title: " + book->get_Title() + ") is now available.";
        // Notify the user who reserved the book.
        Student* stud = library->get_student(book->get_reservedBy_studid());
        Faculty* fac = library->get_faculty(book->get_reservedBy_facid());
        if(stud != nullptr) {
            stud->set_notif(n);
        }else if(fac != nullptr) {
            fac->set_notif(n);
        }
        std::cout << "Book returned successfully." << std::endl;
        return;
    }
    // Mark the book as available.
    book->set_status(Status::AVAILABLE);
    std::cout << "Book returned successfully." << std::endl;
    return;
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
    std::cout << std::string(85, '-') << std::endl;
    std::cout << std::left << std::setw(15) << "Book ID" 
              << std::setw(30) << "Title" 
              << std::setw(20) << "Borrowed on" 
              << std::setw(20) << "Returned on" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
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
    std::cout << std::string(85, '-') << std::endl;
}

void Student::Total_fine() const {
    std::cout << "Your total fine is: " << acc.get_Totalfine() << std::endl;
}

void Student::Pay_fine(double amount) {
    if (amount <= 0) {
        std::cout << "Invalid amount. Please enter a positive value." << std::endl;
        return;
    }
    double currentFine = acc.get_Totalfine();
    if (amount > currentFine) {
        std::cout << "The amount exceeds your total fine. Please enter an amount less than or equal to your total fine of: " << currentFine << std::endl;
        return;
    }
    acc.setFine(acc.getFine() - amount); // Deduct the amount from the fine.
    std::cout << amount << " paid successfully. Your remaining fine is: " << currentFine-amount << std::endl;
}

void Student::DisplayFines() const {
    acc.displayFines(maxBorrowPeriod, fine_rate);
}
