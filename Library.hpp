#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <iostream>
#include "Book.hpp"
#include "Student.hpp"
#include "Faculty.hpp"
#include "Librarian.hpp"
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Library {
private:
    // Attributes:
    vector<Book*> books;
    vector<Student*> students;
    vector<Faculty*> faculties;
    vector<Librarian*> librarians;
public:
    // Operations:
    Book* get_book(const string &book_id);
    void add_Book(Book *book);
    void remove_Book(const string &book_id);
    void updateBook(const string &book_id, const string &newTitle, const string &newAuthor, const string &newPublisher, int newYear, const string &newISBN);
    void show_all_books();

    // User operations
    // Helper to add a user to a container.
    template <typename T>
    void addUser(vector<T*>& users, T* user) {
        users.push_back(user);
    }
    // Add functions:
    void add_student(Student *stud);
    void add_faculty(Faculty *fac);
    void add_librarian(Librarian *lib);

    // Helper to get a user pointer by user_id.
    template <typename T>
    T* getUserById(const vector<T*>& users, const string &user_id, const string &typeName) {
        for (T* user : users) {
            if (user->get_user_id() == user_id) {
                return user;
            }
        }
        cout << typeName << " Doesn't Exist!" << endl;
        return nullptr;
    }
    // Get functions:
    Librarian* get_librarian(const string &user_id);
    Student* get_student(const string &user_id);
    Faculty* get_faculty(const string &user_id);

    // Helper to remove a user from a container.
    template <typename T>
    void removeUser(vector<T*>& users, const string &user_id, const string &typeName) {
        for (auto it = users.begin(); it != users.end(); ++it) {
            if ((*it)->get_user_id() == user_id) {
                cout << "Removed " << typeName << " " << (*it)->get_Name() << endl;
                users.erase(it);
                return;
            }
        }
        cout << typeName << " doesn't exist" << endl;
    }
    // Remove functions:
    void remove_student(const string &user_id);
    void remove_faculty(const string &user_id);
    void remove_librarian(const string &user_id);

    template <typename T>
    int verifyUser(const vector<T*>& users, const string &user_id, const string &password, const string &userType) {
        for (T* user : users) {
            if (user->get_user_id() == user_id) {
                if (user->get_password() == password) {
                    cout << userType << " Successfully Logged In" << endl;
                    return 1;
                } else {
                    cout << "Entered Wrong Password for " << userType << "!" << endl;
                    return 0;
                }
            }
        }
        cout << "Entered Wrong User_ID for " << userType << "!" << endl;
        return 0;
    }

    int verify_student(const string &name, const string &password);
    int verify_faculty(const string &name, const string &password);
    int verify_librarian(const string &name, const string &password);

    // Loading and Saving Data:

    // Helper: Convert Book::Status to an integer for saving
    static int statusToInt(Status st);
    // Helper: Convert integer back to Book::Status
    static Status intToStatus(int st);

    void save_data();
    void load_data();
};

#endif // LIBRARY_H
