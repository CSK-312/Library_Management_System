# Library Management System

A C++ project implementing a Library Management System that supports multiple user roles: **Student**, **Faculty**, and **Librarian**.

## Overview

This project simulates a library system where:
- **Students** can borrow/return books, reserve books, view their borrowing history and fines, and update their profiles.
- **Faculty** have similar borrowing functions with different rules (e.g., no fines but overdue restrictions) and can also reserve books.
- **Librarians** manage the library’s book collection and user records (adding, removing, updating).

The system saves and loads data from a text file (`data.txt`) so that all records (books, user data, borrowed records, reservations, and borrowing history) persist across sessions.

## Features

- **Multi-Role System:**  
  - **Student:** Borrow/return books, reserve books, view borrowed books, view fines, update profile, and view borrowing history.
  - **Faculty:** Borrow/return books with overdue restrictions (even without fines), reserve books, and update profile.
  - **Librarian:** Manage books and user accounts.

- **Reservations & Notifications:**  
  - **Reservation:** Users (Students or Faculty) can reserve a book if it is already borrowed.  
  - **Notification:** When a reserved book is returned, the system automatically updates the reserved user's notification field. The notification (stored as a string in the user record) is displayed at login if it is not empty.

- **Data Persistence:**  
  - The system saves all data to a text file in sections: `#BOOKS`, `#STUDENTS`, `#FACULTY`, and `#LIBRARIANS`.  
  - For each Student/Faculty, both current borrowed records, reservations (embedded within the book records), and borrowing history (with timestamps) are stored.
  
- **Fine Calculation & Date Formatting:**  
  - Overdue fines are calculated based on the number of days a book is borrowed.
  - Dates are stored as Unix timestamps and can be formatted for display (e.g., YYYY-MM-DD).

## File Structure

- **Book.hpp / Book.cpp:**  
  Defines the `Book` class with attributes (title, author, publisher, etc.) and operations (getters, setters, viewDetails). The book records now include reservation information (`reservedBy_studid` and `reservedBy_facid`).

- **Account.hpp / Account.cpp:**  
  Manages the user's currently borrowed books and borrowing history.  
  *Borrowing history* is stored as a vector of pairs (or triplets if needed), with timestamps representing the borrow and return times.

- **User.hpp / User.cpp:**  
  The base class for all user types. Contains common attributes and pure virtual functions for borrowing, returning, and reserving books.

- **Student.hpp / Student.cpp:**  
  Inherits from `User` and implements student-specific operations including reservation functionality and notification updates.

- **Faculty.hpp / Faculty.cpp:**  
  Inherits from `User` and implements faculty-specific operations including reservation functionality and notification updates.

- **Librarian.hpp / Librarian.cpp:**  
  Inherits from `User` and implements management functions for books and users.

- **Library.hpp / Library.cpp:**  
  The main class that maintains collections of books and user objects. It includes functions for saving and loading data to/from `data.txt`, with updated sections for reservations and notifications.

- **Library_Management_System.cpp:**  
  Contains the `main()` function and the main application loop (with separate sub‑menus for Student, Faculty, and Librarian).

## Compilation

Ensure you have a C++ compiler that supports C++11 (or later). Open your terminal in the project directory and compile all source files together. For example:

```bash
g++ -std=c++11 -o LibraryManagementSystem Library_Management_System.cpp Library.cpp Book.cpp Account.cpp User.cpp Student.cpp Faculty.cpp Librarian.cpp

