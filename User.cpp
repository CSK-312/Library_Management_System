#include "User.hpp"

string User::get_Name() const {
    return Name;
}

string User::get_user_id() const {
    return user_id;
}

string User::get_password() const {
    return password;
}

int User::get_borrowlimit() const {
    return borrowlimit;
}

int User::get_maxBorrowPeriod() const {
    return maxBorrowPeriod;
}

double User::get_fine_rate() const {
    return fine_rate;
}

void User::set_Name(const string &name) {
    Name = name;
}

void User::set_user_id(const string &id) {
    user_id = id;
}

void User::set_password(const string &pwd) {
    password = pwd;
}

void User::set_borrowlimit(int limit) {
    borrowlimit = limit;
}

void User::set_maxBorrowPeriod(int period) {
    maxBorrowPeriod = period;
}

void User::set_fine_rate(double rate) {
    fine_rate = rate;
}

void User::set_acc(const Account &account) {
    acc = account;
}

void User::viewProfile() const {
    cout << "Name: " << Name << endl;
    cout << "User ID: " << user_id << endl;
    cout << "Password: " << password << endl;
}

void User::updateProfile(const string &newName, const string &newPassword) {
    Name = newName;
    password = newPassword;
    cout << "Profile updated successfully." << endl;
}
