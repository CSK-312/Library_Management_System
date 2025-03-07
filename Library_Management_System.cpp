#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "Book.hpp"
#include "Student.hpp"
#include "Faculty.hpp"
#include "Librarian.hpp"
#include "User.hpp"
#include "Account.hpp"
#include "Library.hpp"

// Helper: Convert Book::Status to an integer for saving
static int statusToInt(Status st) {
    switch (st) {
        case Status::AVAILABLE: return 0;
        case Status::BORROWED:  return 1;
        case Status::RESERVED:  return 2;
    }
    return 0; // default
}

// Helper: Convert integer back to Book::Status
static Status intToStatus(int st) {
    switch (st) {
        case 0: return Status::AVAILABLE;
        case 1: return Status::BORROWED;
        case 2: return Status::RESERVED;
    }
    return Status::AVAILABLE; // default
}

void studentApp(Student *stud, Library *lib) {

        std::cout << "\n\nHome:" << std::endl;
        std::cout << "1.View all books" << std::endl;
        std::cout << "2. Borrow a book" << std::endl;
        std::cout << "3. Return a book" << std::endl;
        std::cout << "4. View borrowed books" << std::endl;
        std::cout << "5. View borrowing history" << std::endl;
        std::cout << "6. View fines" << std::endl;
        std::cout << "7. Pay fine" << std::endl;
        std::cout << "8. View Profile" << std::endl;
        std::cout << "9. Update Profile" << std::endl;
        std::cout << "10. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                stud->View_all_books(lib);
                break;
            case 2: {
                std::string book_id;
                std::cout << "Enter the book ID: ";
                std::getline(std::cin, book_id);
                stud->Borrow_book(book_id, lib);
                break;
            }
            case 3: {
                std::string book_id;
                std::cout << "Enter the book ID: ";
                std::getline(std::cin, book_id);
                stud->Return_book(book_id, lib);
                break;
            }
            case 4:
                stud->View_borrowed_books();
                break;
            case 5:
                stud->View_borrowing_history();
                break;
            case 6:
                stud->DisplayFines();
                break;
            case 7:
                stud->Pay_fine();
                break;
            case 8:
                stud->viewProfile();
                break;
            case 9: {
                std::string newName, newPassword;
                std::cout << "Enter your new name: ";
                std::getline(std::cin, newName);
                std::cout << "Enter your new password: ";
                std::getline(std::cin, newPassword);
                stud->updateProfile(newName, newPassword);
                break;
            }
            case 10:
                std::cout << "Exiting..." << std::endl;
                std::cout << "Thank you for using the Library Management System!" << std::endl;
                return; // Exit the student loop
            default:
                std::cout << "Invalid choice!" << std::endl;
                studentApp(stud, lib); // <-- Jump to the student menu
        }
        std::cout << "\n\nChoose your next operation:" << std::endl;
        std::cout << "1.Home" << std::endl;
        std::cout << "2.Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice2;
        std::cin >> choice2;
        switch(choice2){
            case 1:
                studentApp(stud, lib);
                break;
            case 2:
                std::cout << "Exiting..." << std::endl;
                std::cout << "Thank you for using the Library Management System!" << std::endl;
                return; // Exit the student loop
            default:
                std::cout << "Invalid choice!" << std::endl;
                studentApp(stud, lib); // <-- Jump to the student menu
        }
}

void facultyApp(Faculty *fac, Library *lib) {

        std::cout << "\n\nHome:" << std::endl;
        std::cout << "1. View all books " << std::endl;
        std::cout << "2. Borrow a book" << std::endl;
        std::cout << "3. Return a book" << std::endl;
        std::cout << "4. View Borrowed Books" << std::endl;
        std::cout << "5. View Borrowing History" << std::endl;
        std::cout << "6. View Profile" << std::endl;
        std::cout << "7. Update Profile" << std::endl;
        std::cout << "8. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                fac->View_all_books(lib);
                break;
            case 2: {
                std::string book_id;
                std::cout << "Enter the book ID: ";
                std::getline(std::cin, book_id);
                fac->Borrow_book(book_id, lib);
                break;
            }
            case 3: {
                std::string book_id;
                std::cout << "Enter the book ID: ";
                std::getline(std::cin, book_id);
                fac->Return_book(book_id, lib);
                break;
            }
            case 4:
                fac->View_borrowed_books();
                break;
            case 5:
                fac->View_borrowing_history();
                break;
            case 6:
                fac->viewProfile();
                break;
            case 7: {
                std::string newName, newPassword;
                std::cout << "Enter your new name: ";
                std::getline(std::cin, newName);
                std::cout << "Enter your new password: ";
                std::getline(std::cin, newPassword);
                fac->updateProfile(newName, newPassword);
                break;
            }
            case 8:
                std::cout << "Exiting..." << std::endl;
                std::cout << "Thank you for using the Library Management System!" << std::endl;
                return; // Exit the faculty loop
            default:
                std::cout << "Invalid choice!" << std::endl;
                facultyApp(fac, lib); // <-- Jump to the faculty menu
        }
        std::cout << "\n\nChoose your next operation:" << std::endl;
        cout << "1.Home" << std::endl;
        cout << "2.Exit" << std::endl;
        cout << "Enter your choice: ";
        int choice2;
        std::cin >> choice2;
        switch(choice2){
            case 1:
                facultyApp(fac, lib);
                break;
            case 2:
                std::cout << "Exiting..." << std::endl;
                std::cout << "Thank you for using the Library Management System!" << std::endl;
                return; // Exit the faculty loop
            default:
                std::cout << "Invalid choice!" << std::endl;
                facultyApp(fac, lib); // <-- Jump to the faculty menu 
        }
}

void librarianApp(Librarian *libra, Library *lib) {

        std::cout << "\n\nHome:" << std::endl;
        std::cout << "1. Add a book" << std::endl;
        std::cout << "2. Remove a book" << std::endl;
        std::cout << "3. Update a book" << std::endl;
        std::cout << "4. Add a student" << std::endl;
        std::cout << "5. Add a faculty" << std::endl;
        std::cout << "6. Add a librarian" << std::endl;
        std::cout << "7. Remove a student" << std::endl;
        std::cout << "8. Remove a faculty" << std::endl;
        std::cout << "9. Remove a librarian" << std::endl;
        std::cout << "10. View Profile" << std::endl;
        std::cout << "11. Update Profile" << std::endl;
        std::cout << "12. Exit" << std::endl;
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string Title, Author, Publisher, ISBN, book_id;
                int Year;
                std::cout << "Enter the book title: ";
                std::getline(std::cin, Title);
                std::cout << "Enter the author: ";
                std::getline(std::cin, Author);
                std::cout << "Enter the publisher: ";
                std::getline(std::cin, Publisher);
                std::cout << "Enter the year of publication: ";
                std::cin >> Year;
                std::cin.ignore();
                std::cout << "Enter the ISBN: ";
                std::getline(std::cin, ISBN);
                std::cout << "Enter the book ID: ";
                std::getline(std::cin, book_id);
                libra->addBook(lib, Title, Author, Publisher, Year, ISBN, book_id);

                cout << "Book added successfully!" << endl;
                break;
            }
            case 2: {
                std::string book_id;
                std::cout << "Enter the book ID: ";
                std::getline(std::cin, book_id);
                libra->removeBook(lib, book_id);
                break;
            }
            case 3: {
                std::string book_id, newTitle, newAuthor, newPublisher, newISBN;
                int newYear;
                std::cout << "Enter the book ID: ";
                std::getline(std::cin, book_id);
                std::cout << "Enter the new title: ";
                std::getline(std::cin, newTitle);
                std::cout << "Enter the new author: ";
                std::getline(std::cin, newAuthor);
                std::cout << "Enter the new publisher: ";
                std::getline(std::cin, newPublisher);
                std::cout << "Enter the new year of publication: ";
                std::cin >> newYear;
                std::cin.ignore();
                std::cout << "Enter the new ISBN: ";
                std::getline(std::cin, newISBN);
                libra->updateBook(lib, book_id, newTitle, newAuthor, newPublisher, newYear, newISBN);
                break;
            }
            case 4: {
                std::string Title, Author, Publisher;
                std::cout << "Enter the student's name: ";
                std::getline(std::cin, Title);
                std::cout << "Enter the user ID: ";
                std::getline(std::cin, Author);
                std::cout << "Enter the password: ";
                std::getline(std::cin, Publisher);
                libra->addStudent(lib, Title, Author, Publisher);
                std::cout << "Student added successfully!" << std::endl;
                break;
            }
            case 5: {
                std::string Title, Author, Publisher;
                std::cout << "Enter the faculty's name: ";
                std::getline(std::cin, Title);
                std::cout << "Enter the user ID: ";
                std::getline(std::cin, Author);
                std::cout << "Enter the password: ";
                std::getline(std::cin, Publisher);
                libra->addFaculty(lib, Title, Author, Publisher);
                std::cout << "Faculty added successfully!" << std::endl;
                break;
            }
            case 6: {
                std::string Title, Author, Publisher;
                std::cout << "Enter the librarian's name: ";
                std::getline(std::cin, Title);
                std::cout << "Enter the user ID: ";
                std::getline(std::cin, Author);
                std::cout << "Enter the password: ";
                std::getline(std::cin, Publisher);
                libra->addLibrarian(lib, Title, Author, Publisher);
                std::cout << "Librarian added successfully!" << std::endl;
                break;
            }
            case 7: {
                std::string Title;
                std::cout << "Enter the student's user ID: ";
                std::getline(std::cin, Title);
                libra->removeStudent(lib, Title);
                break;
            }
            case 8: {
                std::string Title;
                std::cout << "Enter the faculty's user ID: ";
                std::getline(std::cin, Title);
                libra->removeFaculty(lib, Title);
                break;
            }
            case 9: {
                std::string Title;
                std::cout << "Enter the librarian's user ID: ";
                std::getline(std::cin, Title);
                libra->removeLibrarian(lib, Title);
                break;
            }
            case 10:
                libra->viewProfile();
                break;
            case 11: {
                std::string newName, newPassword;
                std::cout << "Enter your new name: ";
                std::getline(std::cin, newName);
                std::cout << "Enter your new password: ";
                std::getline(std::cin, newPassword);
                libra->updateProfile(newName, newPassword);
                break;
            }
            case 12:
                std::cout << "Exiting..." << std::endl;
                std::cout << "Thank you for using the Library Management System!" << std::endl;
                return; // Exit the librarian loop
            default:
                std::cout << "Invalid choice!" << std::endl;
                librarianApp(libra, lib); // <-- Jump to the librarian menu
        }
        std::cout << "\n\nChoose your next operation:" << std::endl;
        std::cout << "1.Home" << std::endl;
        std::cout << "2.Exit" << std::endl;
        std::cout << "Enter your choice: ";
        int choice2;
        std::cin >> choice2;
        switch(choice2){
            case 1:
                librarianApp(libra, lib);
                break;
            case 2:
                std::cout << "Exiting..." << std::endl;
                std::cout << "Thank you for using the Library Management System!" << std::endl;
                return; // Exit the librarian loop
            default:
                std::cout << "Invalid choice!" << std::endl; 
                librarianApp(libra, lib); // <-- Jump to the librarian menu
        }
}

void App(Library *lib){
    std::cout << "Please select your role:" << std::endl;
    std::cout << "1. Student" << std::endl;
    std::cout << "2. Faculty" << std::endl;
    std::cout << "3. Librarian" << std::endl;
    std::cout << "4. Exit" << std::endl;
    std::cout << "Enter your choice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    std::string user_id, password;

    switch (choice) {
        case 1: { // Student
            std::cout << "Enter your user ID: ";
            std::getline(std::cin, user_id);
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);
            if (lib->verify_student(user_id, password) == 1) {
                Student *stud = lib->get_student(user_id);
                std::cout << "Welcome, " << stud->get_Name() << "!" << std::endl;
                studentApp(stud, lib); // <-- Jump to the student menu loop
            } else {
                std::cout << "Invalid user ID or password!" << std::endl;
                App(lib);
            }
            break;
        }
        case 2: { // Faculty
            std::cout << "Enter your user ID: ";
            std::getline(std::cin, user_id);
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);
            if (lib->verify_faculty(user_id, password) == 1) {
                Faculty *fac = lib->get_faculty(user_id);
                std::cout << "Welcome, " << fac->get_Name() << "!" << std::endl;
                facultyApp(fac, lib); // <-- Jump to the faculty menu loop
            } else {
                std::cout << "Invalid user ID or password!" << std::endl;
                App(lib);
            }
            break;
        }
        case 3: { // Librarian
            std::cout << "Enter your user ID: ";
            std::getline(std::cin, user_id);
            std::cout << "Enter your password: ";
            std::getline(std::cin, password);
            if (lib->verify_librarian(user_id, password) == 1) {
                Librarian *libra = lib->get_librarian(user_id);
                std::cout << "Welcome, " << libra->get_Name() << "!" << std::endl;
                librarianApp(libra, lib); // <-- Jump to the librarian menu loop
            } else {
                std::cout << "Invalid user ID or password!" << std::endl;
                App(lib);
            }
            break;
        }
        case 4:
            std::cout << "Exiting..." << std::endl;
            std::cout << "Thank you for using the Library Management System!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
    }
}

int main(){
    Library *lib = new Library();
    lib->load_data();
    std::cout << "Welcome to the Library Management System!" << std::endl;
    App(lib);
    lib->save_data();
    return 0;
}


