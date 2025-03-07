#include "Librarian.hpp"
#include "Library.hpp"  // Full definition required for Library management functions.
#include "Book.hpp"
#include "Student.hpp"
#include "Faculty.hpp"
#include <iostream>

using namespace std;

Librarian::Librarian(const std::string &name, const std::string &id, const std::string &pwd) {
    this->Name = name;
    this->user_id = id;
    this->password = pwd;
    this->borrowlimit = 0;       
    this->maxBorrowPeriod = 0;   
    this->fine_rate = 0;         
}

void Librarian::Borrow_book(const std::string &book_id, Library *library) {
    cout << "Librarians cannot borrow books." << endl;
}

void Librarian::Return_book(const std::string &book_id, Library *library) {
    cout << "Librarians cannot return books." << endl;
}

// -------------- Book Management --------------

void Librarian::addBook(Library *lib, const string &Title, const string &Author, const string &Publisher,
                        int Year, const string &ISBN, const string &book_id) {
    Book *book = new Book(Title, Author, Publisher, Year, book_id, ISBN);
    lib->add_Book(book);
}

void Librarian::removeBook(Library *lib, const string &book_id) {
    lib->remove_Book(book_id);
}

void Librarian::updateBook(Library *lib, const string &book_id, const string &newTitle,
                           const string &newAuthor, const string &newPublisher, int newYear, const string &newISBN) {
    lib->updateBook(book_id, newTitle, newAuthor, newPublisher, newYear, newISBN);
}

// -------------- User Management --------------

void Librarian::addStudent(Library *lib, const string &Name , const string &id , const string &pwd) {
    if(lib->get_student(id) != nullptr) {
        cout << "Student ID already exists!" << endl;
        return;
    }
    Student *stud = new Student(Name, id, pwd);
    lib->add_student(stud);
}

void Librarian::addFaculty(Library *lib, const string &Name , const string &id , const string &pwd) {
    if(lib->get_faculty(id) != nullptr) {
        cout << "Faculty ID already exists!" << endl;
        return;
    }
    Faculty *fac = new Faculty(Name, id, pwd);
    lib->add_faculty(fac);
}

void Librarian::addLibrarian(Library *lib, const string &Name , const string &id , const string &pwd) {
    if(lib->get_librarian(id) != nullptr) {
        cout << "Librarian ID already exists!" << endl;
        return;
    }
    Librarian *libra = new Librarian(Name, id, pwd);
    lib->add_librarian(libra);
}

void Librarian::removeStudent(Library *lib, const std::string &user_id) {
    if(user_id == this->user_id) {
        cout << "Librarians cannot remove themselves." << endl;
        return;
    }
    Student *stud = lib->get_student(user_id);
    if(stud == nullptr) {
        cout << "Student not found!" << endl;
        return;
    }
    if(stud->get_acc().getBorrowedBookCount() > 0) {
        cout << "Student has borrowed books. Cannot remove." << endl;
        return;
    }
    lib->remove_student(user_id);
}

void Librarian::removeFaculty(Library *lib, const std::string &user_id) {
    if(user_id == this->user_id) {
        cout << "Librarians cannot remove themselves." << endl;
        return;
    }
    Faculty *fac = lib->get_faculty(user_id);
    if(fac == nullptr) {
        cout << "Faculty not found!" << endl;
        return;
    }
    if(fac->get_acc().getBorrowedBookCount() > 0) {
        cout << "Faculty has borrowed books. Cannot remove." << endl;
        return;
    }
    lib->remove_faculty(user_id);
}

void Librarian::removeLibrarian(Library *lib, const std::string &user_id) {
    if(user_id == this->user_id) {
        cout << "Librarians cannot remove themselves." << endl;
        return;
    }
    lib->remove_librarian(user_id);
}
