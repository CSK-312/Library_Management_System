# Library Management System

A C++ project implementing a Library Management System that supports multiple user roles: **Student**, **Faculty**, and **Librarian**.

## Overview

This project simulates a library system where:
- **Students** can borrow/return books, view their borrowing history and fines, and update their profiles.
- **Faculty** have similar borrowing functions with different rules (e.g., no fines but overdue restrictions).
- **Librarians** manage the library’s book collection and user records (adding, removing, updating).

The system saves and loads data from a text file (`data.txt`) so that all records (books, user data, borrowed records, and borrowing history) persist across sessions.

## Features

- **Multi-Role System:**  
  - **Student:** Borrow/return books, view borrowed books, view fines, update profile, view borrowing history.
  - **Faculty:** Borrow/return books with overdue restrictions (even without fines), update profile.
  - **Librarian:** Manage books and user accounts.

- **Data Persistence:**  
  - The system saves all data to a text file in sections: `#BOOKS`, `#STUDENTS`, `#FACULTY`, and `#LIBRARIANS`.
  - For each Student/Faculty, both current borrowed records and borrowing history (each with a timestamp) are stored.

- **Fine Calculation & Date Formatting:**  
  - Overdue fines are calculated based on the number of days a book is borrowed.
  - Dates are stored as Unix timestamps and can be formatted for display (e.g., YYYY-MM-DD).

## File Structure

- **Book.hpp / Book.cpp:**  
  Defines the `Book` class with attributes (title, author, publisher, etc.) and operations (getters, setters, viewDetails).

- **Account.hpp / Account.cpp:**  
  Manages the user's currently borrowed books and borrowing history.  
  *Borrowing history* is now stored as a vector of pairs (`pair<Book*, time_t>`), where the `time_t` represents the return time.

- **User.hpp / User.cpp:**  
  The base class for all user types. Contains common attributes and pure virtual functions for borrowing and returning books.

- **Student.hpp / Student.cpp:**  
  Inherits from `User` and implements student-specific operations.

- **Faculty.hpp / Faculty.cpp:**  
  Inherits from `User` and implements faculty-specific operations.

- **Librarian.hpp / Librarian.cpp:**  
  Inherits from `User` and implements management functions for books and users.

- **Library.hpp / Library.cpp:**  
  The main class that maintains collections of books and user objects. It includes functions for saving and loading data to/from `data.txt`.

- **Library_Management_System.cpp:**  
  Contains the `main()` function and the main application loop (with separate sub‑menus for Student, Faculty, and Librarian).

## Compilation

Ensure you have a C++ compiler that supports C++11 (or later). Open your terminal in the project directory and compile all source files together. For example:

```bash
g++ -std=c++11 -o LibraryManagementSystem Library_Management_System.cpp Library.cpp Book.cpp Account.cpp User.cpp Student.cpp Faculty.cpp Librarian.cpp
