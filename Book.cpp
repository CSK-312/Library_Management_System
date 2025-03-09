#include "Book.hpp"

// Constructor definition.
Book::Book(string title, string author, string publisher, int Year, string b_id, string isbn) {
    Title = title;
    Author = author;
    Publisher = publisher;
    year = Year;
    ISBN = isbn;
    status = Status::AVAILABLE;
    book_id = b_id;
    reservedBy_studid = "";
    reservedBy_facid = "";
}

// Getter definitions.
string Book::get_Title() const { return Title; }
string Book::get_Author() const { return Author; }
string Book::get_Publisher() const { return Publisher; }
int Book::get_year() const { return year; }
string Book::get_ISBN() const { return ISBN; }
Status Book::get_status() const { return status; }
string Book::get_bookid() const { return book_id; }
string Book::get_reservedBy_studid() const { return reservedBy_studid; }
string Book::get_reservedBy_facid() const { return reservedBy_facid; }

// Setter definitions.
void Book::set_Title(const string &title) { Title = title; }
void Book::set_Author(const string &author) { Author = author; }
void Book::set_Publisher(const string &publisher) { Publisher = publisher; }
void Book::set_year(int y) { year = y; }
void Book::set_ISBN(const string &isbn) { ISBN = isbn; }
void Book::set_status(Status newStatus) { status = newStatus; }
void Book::set_bookid(const string &id) { book_id = id; }
void Book::set_reservedBy_studid(string studid) { reservedBy_studid = studid; }
void Book::set_reservedBy_facid(string facid) { reservedBy_facid = facid; }

// viewDetails implementation.
void Book::viewDetails() const {
    cout << "Title: " << Title << ", Author: " << Author
         << ", Publisher: " << Publisher << ", Year: " << year
         << ", ISBN: " << ISBN << ", Status: ";
    if (status == Status::AVAILABLE)
        cout << "AVAILABLE";
    else if (status == Status::BORROWED)
        cout << "BORROWED";
    else
        cout << "RESERVED";
    cout << endl;
}
