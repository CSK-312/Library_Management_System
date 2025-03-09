#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>

using namespace std;

//Forward declaration of Student and Faculty to avoid circular dependency.
class Student;
class Faculty;

// Status enumeration.
enum class Status { AVAILABLE, BORROWED, RESERVED };

class Book {
private:    
    // Attributes.
    string Title;
    string Author;
    string Publisher;
    int year;
    string ISBN;
    Status status;
    string book_id;
    // Extra attributes for reservation.(not displayed anywhere)
    string reservedBy_studid; // *It stores the student ID who reserved the book.*
    string reservedBy_facid;  // *It stores the faculty ID who reserved the book.*

public:
    // Constructor declaration.
    Book(string title, string author, string publisher, int Year, string b_id, string isbn);

    // Getters.
    string get_Title() const;
    string get_Author() const;
    string get_Publisher() const;
    int get_year() const;
    string get_ISBN() const;
    Status get_status() const;
    string get_bookid() const;
    string get_reservedBy_studid() const;
    string get_reservedBy_facid() const;

    // Setters.
    void set_Title(const string &title);
    void set_Author(const string &author);
    void set_Publisher(const string &publisher);
    void set_year(int y);
    void set_ISBN(const string &isbn);
    void set_status(Status newStatus);
    void set_bookid(const string &id);
    void set_reservedBy_studid(string studid);
    void set_reservedBy_facid(string facid);

    // Other operations.
    void viewDetails() const;
};

#endif // BOOK_HPP
