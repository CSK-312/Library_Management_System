#ifndef LIBRARIAN_HPP
#define LIBRARIAN_HPP

#include "User.hpp"

// Forward declaration of Library to avoid circular dependencies.
class Library;

class Librarian : public User {
public:
    // Constructor.
    Librarian(const std::string &name, const std::string &id, const std::string &pwd);

    // Overridden functions: Librarians cannot borrow or return books.
    virtual void Borrow_book(const std::string &book_id, Library *library) override;
    virtual void Return_book(const std::string &book_id, Library *library) override;

    // -------------- Book Management --------------
    void addBook(Library *lib, const std::string &Title, const std::string &Author, const std::string &Publisher,
                 int Year, const std::string &ISBN, const std::string &book_id);
    void removeBook(Library *lib, const std::string &book_id);
    void updateBook(Library *lib, const std::string &book_id, const std::string &newTitle,
                    const std::string &newAuthor, const std::string &newPublisher,
                    int newYear, const std::string &newISBN);

    // -------------- User Management --------------
    void addStudent(Library *lib, const std::string &Name ,const std::string &id, const std::string &pwd);
    void addFaculty(Library *lib, const std::string &Name ,const std::string &id, const std::string &pwd);
    void addLibrarian(Library *lib, const std::string &Name ,const std::string &id, const std::string &pwd);
    void removeStudent(Library *lib, const std::string &user_id);
    void removeFaculty(Library *lib, const std::string &user_id);
    void removeLibrarian(Library *lib, const std::string &user_id);
};

#endif // LIBRARIAN_HPP


