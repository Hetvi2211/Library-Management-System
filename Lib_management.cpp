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
// Function to issue a book
void issueBook() {
    vector<Book> books;
    ifstream file("books.txt");
    string line, title;
    bool found = false;

    cin.ignore();
    cout << "Enter book title to issue: ";
    getline(cin, title);

    while (getline(file, line)) {
        stringstream ss(line);
        Book book;
        string status;

        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        getline(ss, status, ',');
        book.isIssued = (status == "1");

        if (book.title == title && !book.isIssued) {
            book.isIssued = true;
            found = true;
        }
        books.push_back(book);
    }
    file.close();

    if (found) {
        ofstream outFile("books.txt");
        for (const auto &book : books) {
            outFile << book.title << "," << book.author << "," << (book.isIssued ? "1" : "0") << "\n";
        }
        outFile.close();
        cout << "Book issued successfully!\n";
    } else {
        cout << "Book not available or already issued.\n";
    }
}

// Function to return a book
void returnBook() {
    vector<Book> books;
    ifstream file("books.txt");
    string line, title;
    bool found = false;

    cin.ignore();
    cout << "Enter book title to return: ";
    getline(cin, title);

    while (getline(file, line)) {
        stringstream ss(line);
        Book book;
        string status;

        getline(ss, book.title, ',');
        getline(ss, book.author, ',');
        getline(ss, status, ',');
        book.isIssued = (status == "1");

        if (book.title == title && book.isIssued) {
            book.isIssued = false;
            found = true;
        }
        books.push_back(book);
    }
    file.close();

    if (found) {
        ofstream outFile("books.txt");
        for (const auto &book : books) {
            outFile << book.title << "," << book.author << "," << (book.isIssued ? "1" : "0") << "\n";
        }
        outFile.close();
        cout << "Book returned successfully!\n";
    } else {
        cout << "Book not found or not issued.\n";
    }
}

#include <iostream>
#include "library.h"

using namespace std;

int main() {
    int choice;
    while (true) {
        cout << "\n=== Library Management System ===\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: issueBook(); break;
            case 5: returnBook(); break;
            case 6: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}



