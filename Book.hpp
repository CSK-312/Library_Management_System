#ifndef BOOK_HPP
#define BOOK_HPP

#include <iostream>
#include <string>

using namespace std;

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

    // Setters.
    void set_Title(const string &title);
    void set_Author(const string &author);
    void set_Publisher(const string &publisher);
    void set_year(int y);
    void set_ISBN(const string &isbn);
    void set_status(Status newStatus);
    void set_bookid(const string &id);

    // Other operations.
    void viewDetails() const;
};

#endif // BOOK_HPP

