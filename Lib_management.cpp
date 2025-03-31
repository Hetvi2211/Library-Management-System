#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "library.h"

using namespace std;

struct Book {
    string title;
    string author;
    bool isIssued;
};

// Function to add a book
void addBook() {
    ofstream file("books.txt", ios::app);
    string title, author;

    cin.ignore();
    cout << "Enter book title: ";
    getline(cin, title);
    cout << "Enter author name: ";
    getline(cin, author);

    file << title << "," << author << ",0\n";  // 0 means not issued
    file.close();
    cout << "Book added successfully!\n";
}

// Function to view all books
void viewBooks() {
    ifstream file("books.txt");
    string line;

    cout << "\n=== Book List ===\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, status;
        getline(ss, title, ',');
        getline(ss, author, ',');
        getline(ss, status, ',');
        cout << "Title: " << title << " | Author: " << author
             << " | Status: " << (status == "0" ? "Available" : "Issued") << endl;
    }
    file.close();
}

// Function to search for a book
void searchBook() {
    ifstream file("books.txt");
    string line, keyword;
    bool found = false;

    cin.ignore();
    cout << "Enter book title to search: ";
    getline(cin, keyword);

    while (getline(file, line)) {
        if (line.find(keyword) != string::npos) {
            cout << "Book Found: " << line << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "Book not found.\n";
    file.close();
}


