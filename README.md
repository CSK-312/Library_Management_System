# Library Management System

A C++ project implementing a Library Management System that supports multiple user roles: **Student**, **Faculty**, and **Librarian**.

## Overview

This project simulates a library system where:
- **Students** can borrow/return books, reserve books, view their borrowing history and fines, and update their profiles.
- **Faculty** have similar borrowing functions with different rules (e.g., no fines but overdue restrictions) and can also reserve books.
- **Librarians** manage the library’s book collection and user records (adding, removing, updating).  
*Note: Only a Librarian can create user accounts.*

The system saves and loads data from a text file (`data.txt`), ensuring that all records (books, user data, borrowed records, reservations, and borrowing history) persist across sessions.

## Features

- **Multi-Role System:**  
  - **Student:** Borrow/return books, reserve books, view borrowed books, view fines, update profile, and view borrowing history.
  - **Faculty:** Borrow/return books with overdue restrictions (even without fines), reserve books, and update profile.
  - **Librarian:** Manage books and user accounts.

- **Reservations & Notifications:**  
  Users (Students or Faculty) can reserve a book if it is already borrowed. When a reserved book is returned, the system automatically updates the reserved user's notification field, which is displayed at login.

- **Fine Calculation:**  
  Overdue fines are calculated dynamically based on the number of days a book is borrowed. When a book is returned, any overdue fine is added to the user's accumulated fine.

- **Data Persistence:**  
  Data is stored in a text file (`data.txt`) in clearly defined sections.

## Data Storage

Data is stored in the `data.txt` file in four main sections:

- **BOOKS:**  
  Each record is stored on one line as:  
  `Title, Author, Publisher, Year, ISBN, Status (0=AVAILABLE, 1=BORROWED, 2=RESERVED), Book_ID, Student_ID who reserved it (or empty), Faculty_ID who reserved it (or empty)`

- **STUDENTS:**  
  Each record is stored on one line as:  
  `Name, user_id, password, borrowlimit, maxBorrowPeriod, fine_rate, Fine, borrowedCount, [for each borrowed book: Book_ID, BorrowTime], historyCount, [for each history record: Book_ID, BorrowTime, ReturnTime]`

- **FACULTY:**  
  Each record follows the same format as STUDENTS.

- **LIBRARIANS:**  
  Each record is stored on one line as:  
  `Name, user_id, password`

## File Structure

- **Book.hpp / Book.cpp:**  
  Defines the `Book` class with attributes (title, author, publisher, etc.) and operations (getters, setters, viewDetails). Book records now include reservation information (`reservedBy_studid` and `reservedBy_facid`).

- **Account.hpp / Account.cpp:**  
  Manages the user's currently borrowed books and borrowing history. Borrowing history is stored as a vector of pairs in the format:  
  `vector<pair<Book*, pair<time_t, time_t>>>`  
  where the inner pair holds the borrow time and the return time. It also tracks the accumulated fine for returned overdue books.

- **User.hpp / User.cpp:**  
  The base class for all user types. Contains common attributes and pure virtual functions for borrowing, returning, and reserving books.

- **Student.hpp / Student.cpp:**  
  Inherits from `User` and implements student-specific operations including reservation functionality and notification updates.

- **Faculty.hpp / Faculty.cpp:**  
  Inherits from `User` and implements faculty-specific operations including reservation functionality and notification updates.

- **Librarian.hpp / Librarian.cpp:**  
  Inherits from `User` and implements management functions for books and user accounts.

- **Library.hpp / Library.cpp:**  
  Maintains collections of books and user objects, and includes functions for saving and loading data to/from `data.txt`.

- **Library_Management_System.cpp:**  
  Contains the `main()` function and the main application loop (with separate sub‑menus for Student, Faculty, and Librarian).

## System Constraints

- Each user_id is created by the user and is ensured to be unique.
- Only a Librarian can create a user account.
- Fines are calculated dynamically for currently borrowed books and updated upon return.
- Users receive only one notification at a time.

## Compilation and Running

Ensure you have a C++ compiler that supports C++11 (or later). Open your terminal in the project directory and compile all source files together. For example:

```bash
g++ -std=c++11 -o LibraryManagementSystem Library_Management_System.cpp Library.cpp Book.cpp Account.cpp User.cpp Student.cpp Faculty.cpp Librarian.cpp
```

Then run the following command:
On Linux/macOS
```bash
./LibraryManagementSystem
```
On Windows (CMD or PowerShell):
```bash
.\LibraryManagementSystem

