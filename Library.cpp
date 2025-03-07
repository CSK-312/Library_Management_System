#include "Library.hpp"

// get_book
Book* Library::get_book(const string &book_id) {
    for (Book* book : books) {
        if (book->get_bookid() == book_id) {
            return book;
        }
    }
    cout << "Book Doesn't Exist!" << endl;
    return nullptr;
}

// add_Book
void Library::add_Book(Book *book) {
    books.push_back(book);
}

// remove_Book
void Library::remove_Book(const string &book_id) {
    for (int i = 0; i < books.size(); i++) {
        if (books[i]->get_bookid() == book_id) {
            books.erase(books.begin() + i);
            cout << "Book removed successfully!" << endl;
            return;
        }
    }
    cout << "Book not found!" << endl;
}

// updateBook
void Library::updateBook(const string &book_id, const string &newTitle, const string &newAuthor, const string &newPublisher, int newYear, const string &newISBN) {
    Book* book = get_book(book_id);
    if (!book) {
        cout << "Book not found!" << endl;
        return;
    }
    book->set_Title(newTitle);
    book->set_Author(newAuthor);
    book->set_Publisher(newPublisher);
    book->set_year(newYear);
    book->set_ISBN(newISBN);
    cout << "Book updated successfully!" << endl;
}

// Show all books
void Library::show_all_books() {
    cout << "Books in the library:" << endl;
    cout << string(91, '-') << endl;
    cout << left << setw(10) << "Book ID" 
         << setw(20) << "Title" 
         << setw(20) << "Author" 
         << setw(20) << "Publisher" 
         << setw(6) << "Year" 
         << setw(15) << "ISBN" 
         << "Status" << endl;
    cout << string(91, '-') << endl;
    for (auto book : books) {
        cout << left << setw(10) << book->get_bookid() 
             << setw(20) << book->get_Title() 
             << setw(20) << book->get_Author() 
             << setw(20) << book->get_Publisher() 
             << setw(6) << book->get_year() 
             << setw(15) << book->get_ISBN() 
             << setw(10);
        switch (book->get_status()) {
            case Status::AVAILABLE:
                cout << "AVAILABLE";
                break;
            case Status::BORROWED:
                cout << "BORROWED";
                break;
            case Status::RESERVED:
                cout << "RESERVED";
                break;
        }
        cout << endl;
    }
    cout << string(91, '-') << endl;
}

// Add functions:
void Library::add_student(Student *stud) {
    addUser(students, stud);
}

void Library::add_faculty(Faculty *fac) {
    addUser(faculties, fac);
}

void Library::add_librarian(Librarian *lib) {
    addUser(librarians, lib);
}

// Get functions:
Librarian* Library::get_librarian(const string &user_id) {
    return getUserById(librarians, user_id, "Librarian");
}

Student* Library::get_student(const string &user_id) {
    return getUserById(students, user_id, "Student");
}

Faculty* Library::get_faculty(const string &user_id) {
    return getUserById(faculties, user_id, "Faculty");
}

// Remove functions:
void Library::remove_student(const string &user_id) {
    removeUser(students, user_id, "Student");
}

void Library::remove_faculty(const string &user_id) {
    removeUser(faculties, user_id, "Faculty");
}

void Library::remove_librarian(const string &user_id) {
    removeUser(librarians, user_id, "Librarian");
}

// Verify functions:
int Library::verify_student(const string &name, const string &password) {
    return verifyUser(students, name, password, "Student");
}

int Library::verify_faculty(const string &name, const string &password) {
    return verifyUser(faculties, name, password, "Faculty");
}

int Library::verify_librarian(const string &name, const string &password) {
    return verifyUser(librarians, name, password, "Librarian");
}

// ---------------- Static Helper Functions ----------------
int Library::statusToInt(Status st) {
    switch (st) {
        case Status::AVAILABLE: return 0;
        case Status::BORROWED:  return 1;
        case Status::RESERVED:  return 2;
    }
    return 0; // default
}

Status Library::intToStatus(int st) {
    switch (st) {
        case 0: return Status::AVAILABLE;
        case 1: return Status::BORROWED;
        case 2: return Status::RESERVED;
    }
    return Status::AVAILABLE; // default
}

// ---------------- Save Data ----------------
void Library::save_data() {
    ofstream outFile("data.txt");
    if (!outFile) {
        cerr << "Error opening file for writing!" << endl;
        return;
    }

    // --- BOOKS ---
    outFile << "#BOOKS\n";
    outFile << books.size() << "\n";
    for (auto* b : books) {
        outFile << b->get_Title() << ","
                << b->get_Author() << ","
                << b->get_Publisher() << ","
                << b->get_year() << ","
                << b->get_ISBN() << ","
                << statusToInt(b->get_status()) << ","
                << b->get_bookid() << "\n";
    }
    outFile << "\n";

    // --- STUDENTS ---
    outFile << "#STUDENTS\n";
    outFile << students.size() << "\n";
    for (auto* s : students) {
        // Save basic user info.
        outFile << s->get_Name() << ","
                << s->get_user_id() << ","
                << s->get_password() << ","
                << s->get_borrowlimit() << ","
                << s->get_maxBorrowPeriod() << ","
                << s->get_fine_rate();

        // Save borrowed records.
        auto& borrowedRecords = s->get_acc().getBorrowedBooks();
        outFile << "," << borrowedRecords.size();
        for (auto &rec : borrowedRecords) {
            Book* bookPtr = rec.first;
            time_t borrowTime = rec.second;
            outFile << "," << bookPtr->get_bookid() << "," << borrowTime;
        }
        // Save borrowing history.
        auto& history = s->get_acc().getBorrowingHistory();
        outFile << "," << history.size();
        for (auto &rec : history) {
            Book* bookPtr = rec.first;
            time_t returnTime = rec.second;
            outFile << "," << bookPtr->get_bookid() << "," << returnTime;
        }
        outFile << "\n";
    }
    outFile << "\n";

    // --- FACULTY ---
    outFile << "#FACULTY\n";
    outFile << faculties.size() << "\n";
    for (auto* f : faculties) {
        outFile << f->get_Name() << ","
                << f->get_user_id() << ","
                << f->get_password() << ","
                << f->get_borrowlimit() << ","
                << f->get_maxBorrowPeriod() << ","
                << f->get_fine_rate();
        auto& borrowedRecords = f->get_acc().getBorrowedBooks();
        outFile << "," << borrowedRecords.size();
        for (auto &rec : borrowedRecords) {
            Book* bookPtr = rec.first;
            time_t borrowTime = rec.second;
            outFile << "," << bookPtr->get_bookid() << "," << borrowTime;
        }
        auto& history = f->get_acc().getBorrowingHistory();
        outFile << "," << history.size();
        for (auto &rec : history) {
            Book* bookPtr = rec.first;
            time_t returnTime = rec.second;
            outFile << "," << bookPtr->get_bookid() << "," << returnTime;
        }
        outFile << "\n";
    }
    outFile << "\n";

    // --- LIBRARIANS ---
    outFile << "#LIBRARIANS\n";
    outFile << librarians.size() << "\n";
    for (auto* l : librarians) {
        outFile << l->get_Name() << ","
                << l->get_user_id() << ","
                << l->get_password() << "\n";
    }
    outFile << "\n";

    outFile.close();
    cout << "Data saved successfully." << endl;
}

// ---------------- Load Data ----------------
void Library::load_data() {
    ifstream inFile("data.txt");
    if (!inFile) {
        cerr << "No previous data found. Starting fresh.\n";
        return;
    }

    string line;
    string section;   // Section name: BOOKS, STUDENTS, FACULTY, LIBRARIANS.
    int itemsToRead = 0;
    bool readingCount = true;

    while (getline(inFile, line)) {
        if (line.empty()) continue;
        if (line == "#BOOKS" || line == "#STUDENTS" ||
            line == "#FACULTY" || line == "#LIBRARIANS") {
            section = line.substr(1); // Remove '#' to get section name.
            readingCount = true;
            continue;
        }
        if (readingCount) {
            itemsToRead = stoi(line);
            readingCount = false;
            continue;
        }
        // Tokenize the current line (fields separated by commas).
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }
        itemsToRead--;

        if (section == "BOOKS") {
            // Expected tokens: [Title, Author, Publisher, Year, ISBN, statusInt, book_id]
            string title = tokens[0];
            string author = tokens[1];
            string publisher = tokens[2];
            int year = stoi(tokens[3]);
            string isbn = tokens[4];
            int statusVal = stoi(tokens[5]);
            string book_id = tokens[6];

            Book* newBook = new Book(title, author, publisher, year, book_id, isbn);
            newBook->set_ISBN(isbn);
            newBook->set_status(intToStatus(statusVal));
            add_Book(newBook);
        }
        else if (section == "STUDENTS") {
            // Expected tokens: [Name, user_id, password, borrowlimit, maxBorrowPeriod, fine_rate, borrowedCount, ... borrowed records ..., historyCount, ... history records ...]
            string name = tokens[0];
            string uid = tokens[1];
            string pwd = tokens[2];
            int blimit = stoi(tokens[3]);
            int maxPeriod = stoi(tokens[4]);
            double frate = stod(tokens[5]);
            int borrowedCount = stoi(tokens[6]);

            Student* stud = new Student(name, uid, pwd);
            stud->set_borrowlimit(blimit);
            stud->set_maxBorrowPeriod(maxPeriod);
            stud->set_fine_rate(frate);

            int idx = 7;
            // Load borrowed records.
            for (int i = 0; i < borrowedCount; i++) {
                string b_id = tokens[idx++];
                time_t borrowTime = static_cast<time_t>(stoll(tokens[idx++]));
                Book* bptr = get_book(b_id);
                if (bptr) {
                    stud->get_acc().addBorrowedBook(bptr);
                    // Optionally, adjust the borrow time if you have a setter.
                }
            }
            // Load borrowing history (now as pairs: book_id and time returned).
            int historyCount = 0;
            if (idx < tokens.size()) {
                historyCount = stoi(tokens[idx++]);
                for (int i = 0; i < historyCount; i++) {
                    string b_id = tokens[idx++];
                    time_t returnTime = static_cast<time_t>(stoll(tokens[idx++]));
                    Book* bptr = get_book(b_id);
                    if (bptr) {
                        stud->get_acc().addToBorrowingHistory(bptr, returnTime);
                    }
                }
            }
            add_student(stud);
        }
        else if (section == "FACULTY") {
            // Expected tokens: [Name, user_id, password, borrowlimit, maxBorrowPeriod, fine_rate, borrowedCount, ... borrowed records ..., historyCount, ... history records ...]
            string name = tokens[0];
            string uid = tokens[1];
            string pwd = tokens[2];
            int blimit = stoi(tokens[3]);
            int maxPeriod = stoi(tokens[4]);
            double frate = stod(tokens[5]);
            int borrowedCount = stoi(tokens[6]);

            Faculty* fac = new Faculty(name, uid, pwd);
            fac->set_borrowlimit(blimit);
            fac->set_maxBorrowPeriod(maxPeriod);
            fac->set_fine_rate(frate);

            int idx = 7;
            for (int i = 0; i < borrowedCount; i++) {
                string b_id = tokens[idx++];
                time_t borrowTime = static_cast<time_t>(stoll(tokens[idx++]));
                Book* bptr = get_book(b_id);
                if (bptr) {
                    fac->get_acc().addBorrowedBook(bptr);
                }
            }
            int historyCount = 0;
            if (idx < tokens.size()) {
                historyCount = stoi(tokens[idx++]);
                for (int i = 0; i < historyCount; i++) {
                    string b_id = tokens[idx++];
                    time_t returnTime = static_cast<time_t>(stoll(tokens[idx++]));
                    Book* bptr = get_book(b_id);
                    if (bptr) {
                        fac->get_acc().addToBorrowingHistory(bptr, returnTime);
                    }
                }
            }
            add_faculty(fac);
        }
        else if (section == "LIBRARIANS") {
            // Expected tokens: [Name, user_id, password]
            string name = tokens[0];
            string uid = tokens[1];
            string pwd = tokens[2];

            Librarian* libUser = new Librarian(name, uid, pwd);
            add_librarian(libUser);
        }

        if (itemsToRead == 0) {
            readingCount = true;
        }
    }

    inFile.close();
    cout << "Data loaded successfully.\n";
}


