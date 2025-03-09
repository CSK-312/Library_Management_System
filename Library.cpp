#include "Library.hpp"

// get_book
Book* Library::get_book(const string &book_id) {
    for (Book* book : books) {
        if (book->get_bookid() == book_id) {
            return book;
        }
    }
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
    if(books.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }
    cout << "Books in the library:" << endl;
    cout << string(110, '-') << endl;
    cout << left << setw(10) << "Book ID" 
         << setw(20) << "Title" 
         << setw(20) << "Author" 
         << setw(20) << "Publisher" 
         << setw(6) << "Year" 
         << setw(20) << "ISBN" 
         << "Status" << endl;
    cout << string(110, '-') << endl;
    for (auto book : books) {
        cout << left << setw(10) << book->get_bookid() 
             << setw(20) << book->get_Title() 
             << setw(20) << book->get_Author() 
             << setw(20) << book->get_Publisher() 
             << setw(6) << book->get_year() 
             << setw(20) << book->get_ISBN() 
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
    cout << string(110, '-') << endl;
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
                << b->get_bookid() << ","
                << b->get_reservedBy_studid() << ","
                << b->get_reservedBy_facid() << "\n";
    }
    outFile << "\n";

    // --- STUDENTS ---
    outFile << "#STUDENTS\n";
    outFile << students.size() << "\n";
    for (auto* s : students) {
        // Save basic user info including accumulated fine and notif.
        outFile << s->get_Name() << ","
                << s->get_user_id() << ","
                << s->get_password() << ","
                << s->get_borrowlimit() << ","
                << s->get_maxBorrowPeriod() << ","
                << s->get_fine_rate() << ","
                << s->get_acc().getFine() << ","
                << s->get_notif();
        
        // Save borrowed records.
        auto& borrowedRecords = s->get_acc().getBorrowedBooks();
        outFile << "," << borrowedRecords.size();
        for (auto &rec : borrowedRecords) {
            Book* bookPtr = rec.first;
            time_t borrowTime = rec.second;
            outFile << "," << bookPtr->get_bookid() << "," << borrowTime;
        }
        
        // Save borrowing history (each record: book_id, borrowTime, returnTime).
        auto& history = s->get_acc().getBorrowingHistory();
        outFile << "," << history.size();
        for (auto &rec : history) {
            Book* bookPtr = rec.first;
            time_t borrowTime = rec.second.first;
            time_t returnTime = rec.second.second;
            outFile << "," << bookPtr->get_bookid() << "," << borrowTime << "," << returnTime;
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
                << f->get_fine_rate() << ","
                << f->get_acc().getFine() << ","
                << f->get_notif();
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
            time_t borrowTime = rec.second.first;
            time_t returnTime = rec.second.second;
            outFile << "," << bookPtr->get_bookid() << "," << borrowTime << "," << returnTime;
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

        // Check for a section header.
        if (line[0] == '#') {
            section = line.substr(1); // Remove '#' to get section name.
            readingCount = true;
            continue;
        }

        // Read the number of items in the section.
        if (readingCount) {
            try {
                itemsToRead = stoi(line);
            } catch (const std::exception &e) {
                cerr << "Error converting item count: " << line << ". Exception: " << e.what() << "\n";
                continue;
            }
            readingCount = false;
            continue;
        }

        // Tokenize the current line.
        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // --- BOOKS Section ---
        if (section == "BOOKS") {
            const size_t expected_tokens = 9;
            while (tokens.size() < expected_tokens)
                tokens.push_back("");

            if (tokens.size() < 7) { // At least 7 mandatory fields needed.
                cerr << "Malformed book record: " << line << "\n";
                continue;
            }
            string title = tokens[0];
            string author = tokens[1];
            string publisher = tokens[2];
            int year = 0;
            try {
                year = stoi(tokens[3]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for year in record: " << line << "\n";
                continue;
            }
            string isbn = tokens[4];
            int statusVal = 0;
            try {
                statusVal = stoi(tokens[5]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for status in record: " << line << "\n";
                continue;
            }
            string book_id = tokens[6];
            string reservedBy_studid = tokens[7];
            string reservedBy_facid = tokens[8];

            Book* newBook = new Book(title, author, publisher, year, book_id, isbn);
            newBook->set_ISBN(isbn);
            newBook->set_status(intToStatus(statusVal));
            newBook->set_reservedBy_studid(reservedBy_studid);
            newBook->set_reservedBy_facid(reservedBy_facid);
            add_Book(newBook);
        }
        // --- STUDENTS Section ---
        else if (section == "STUDENTS") {
            // Expected tokens now:
            // [Name, user_id, password, borrowlimit, maxBorrowPeriod, fine_rate, Fine, notif, borrowedCount, ... borrowed records ..., historyCount, ... history records ...]
            if (tokens.size() < 9) {
                cerr << "Malformed student record: " << line << "\n";
                continue;
            }
            string name = tokens[0];
            string uid = tokens[1];
            string pwd = tokens[2];
            int blimit = 0;
            try {
                blimit = stoi(tokens[3]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for borrowlimit in record: " << line << "\n";
                continue;
            }
            int maxPeriod = 0;
            try {
                maxPeriod = stoi(tokens[4]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for maxBorrowPeriod in record: " << line << "\n";
                continue;
            }
            double frate = 0;
            try {
                frate = stod(tokens[5]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for fine_rate in record: " << line << "\n";
                continue;
            }
            double fineAcc = 0;
            try {
                fineAcc = stod(tokens[6]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for fineAcc in record: " << line << "\n";
                continue;
            }
            string notif = tokens[7];  // Notification field
            int borrowedCount = 0;
            try {
                borrowedCount = stoi(tokens[8]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for borrowedCount in record: " << line << "\n";
                continue;
            }

            Student* stud = new Student(name, uid, pwd);
            stud->set_borrowlimit(blimit);
            stud->set_maxBorrowPeriod(maxPeriod);
            stud->set_fine_rate(frate);
            stud->get_acc().setFine(fineAcc);
            stud->set_notif(notif);

            int idx = 9;
            // Process borrowed records.
            for (int i = 0; i < borrowedCount; i++) {
                if (idx + 1 >= tokens.size()){
                    cerr << "Insufficient tokens for borrowed records in student: " << line << "\n";
                    break;
                }
                string b_id = tokens[idx++];
                time_t borrowTime = 0;
                try {
                    borrowTime = static_cast<time_t>(stoll(tokens[idx++]));
                } catch (const std::exception &e) {
                    cerr << "Conversion error for borrowed record time in student: " << line << "\n";
                    break;
                }
                Book* bptr = get_book(b_id);
                if (bptr) {
                    stud->get_acc().addBorrowedBook(bptr);
                }
            }
            // Process borrowing history.
            if (idx < tokens.size()) {
                int historyCount = 0;
                try {
                    historyCount = stoi(tokens[idx++]);
                } catch (const std::exception &e) {
                    cerr << "Conversion error for historyCount in student: " << line << "\n";
                    continue;
                }
                for (int i = 0; i < historyCount; i++) {
                    if (idx + 2 >= tokens.size()){
                        cerr << "Insufficient tokens for history records in student: " << line << "\n";
                        break;
                    }
                    string b_id = tokens[idx++];
                    time_t borrowTime = 0;
                    time_t returnTime = 0;
                    try {
                        borrowTime = static_cast<time_t>(stoll(tokens[idx++]));
                        returnTime = static_cast<time_t>(stoll(tokens[idx++]));
                    } catch (const std::exception &e) {
                        cerr << "Conversion error for history record times in student: " << line << "\n";
                        break;
                    }
                    Book* bptr = get_book(b_id);
                    if (bptr) {
                        stud->get_acc().addToBorrowingHistory(bptr, borrowTime, returnTime);
                    }
                }
            }
            add_student(stud);
        }
        // --- FACULTY Section ---
        else if (section == "FACULTY") {
            // Expected tokens:
            // [Name, user_id, password, borrowlimit, maxBorrowPeriod, fine_rate, Fine, notif, borrowedCount, ... borrowed records ..., historyCount, ... history records ...]
            if (tokens.size() < 9) {
                cerr << "Malformed faculty record: " << line << "\n";
                continue;
            }
            string name = tokens[0];
            string uid = tokens[1];
            string pwd = tokens[2];
            int blimit = 0;
            try {
                blimit = stoi(tokens[3]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for borrowlimit in faculty record: " << line << "\n";
                continue;
            }
            int maxPeriod = 0;
            try {
                maxPeriod = stoi(tokens[4]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for maxBorrowPeriod in faculty record: " << line << "\n";
                continue;
            }
            double frate = 0;
            try {
                frate = stod(tokens[5]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for fine_rate in faculty record: " << line << "\n";
                continue;
            }
            double fineAcc = 0;
            try {
                fineAcc = stod(tokens[6]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for fineAcc in faculty record: " << line << "\n";
                continue;
            }
            string notif = tokens[7];  // Notification field
            int borrowedCount = 0;
            try {
                borrowedCount = stoi(tokens[8]);
            } catch (const std::exception &e) {
                cerr << "Conversion error for borrowedCount in faculty record: " << line << "\n";
                continue;
            }

            Faculty* fac = new Faculty(name, uid, pwd);
            fac->set_borrowlimit(blimit);
            fac->set_maxBorrowPeriod(maxPeriod);
            fac->set_fine_rate(frate);
            fac->get_acc().setFine(fineAcc);
            fac->set_notif(notif);

            int idx = 9;
            for (int i = 0; i < borrowedCount; i++){
                if (idx + 1 >= tokens.size()){
                    cerr << "Insufficient tokens for borrowed records in faculty: " << line << "\n";
                    break;
                }
                string b_id = tokens[idx++];
                time_t borrowTime = 0;
                try {
                    borrowTime = static_cast<time_t>(stoll(tokens[idx++]));
                } catch (const std::exception &e) {
                    cerr << "Conversion error for borrowed record time in faculty: " << line << "\n";
                    break;
                }
                Book* bptr = get_book(b_id);
                if (bptr) {
                    fac->get_acc().addBorrowedBook(bptr);
                }
            }
            
            if (idx < tokens.size()){
                int historyCount = 0;
                try {
                    historyCount = stoi(tokens[idx++]);
                } catch (const std::exception &e) {
                    cerr << "Conversion error for historyCount in faculty record: " << line << "\n";
                    continue;
                }
                for (int i = 0; i < historyCount; i++){
                    if (idx + 2 >= tokens.size()){
                        cerr << "Insufficient tokens for history records in faculty: " << line << "\n";
                        break;
                    }
                    string b_id = tokens[idx++];
                    time_t borrowTime = 0;
                    time_t returnTime = 0;
                    try {
                        borrowTime = static_cast<time_t>(stoll(tokens[idx++]));
                        returnTime = static_cast<time_t>(stoll(tokens[idx++]));
                    } catch (const std::exception &e) {
                        cerr << "Conversion error for history record times in faculty: " << line << "\n";
                        break;
                    }
                    Book* bptr = get_book(b_id);
                    if (bptr) {
                        fac->get_acc().addToBorrowingHistory(bptr, borrowTime, returnTime);
                    }
                }
            }
            add_faculty(fac);
        }
        // --- LIBRARIANS Section ---
        else if (section == "LIBRARIANS") {
            if (tokens.size() < 3) {
                cerr << "Malformed librarian record: " << line << "\n";
                continue;
            }
            string name = tokens[0];
            string uid = tokens[1];
            string pwd = tokens[2];
            Librarian* libUser = new Librarian(name, uid, pwd);
            add_librarian(libUser);
        }

        itemsToRead--;
        if (itemsToRead == 0) {
            readingCount = true;
        }
    }

    inFile.close();
    cout << "Data loaded successfully.\n";
}
