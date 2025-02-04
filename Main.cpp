#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    string status;
    string issuedTo;

    Book(int id, string title, string author) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->status = "available";
        this->issuedTo = "";
    }

    void display() {
        cout << "ID: " << id << endl << "Title: " << title << endl << "Author: " << author << endl << "Status: " << status;
        if (status == "issued") {
            cout << ", Issued to: " << issuedTo;
        }
        cout << endl;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
    }

    void searchBookByID(int id) {
        for (auto &book : books) {
            if (book.id == id) {
                book.display();
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void searchBookByTitle(string title) {
        for (auto &book : books) {
            if (book.title == title) {
                book.display();
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void issueBook(int id, string studentName) {
        for (auto &book : books) {
            if (book.id == id && book.status == "available") {
                book.status = "issued";
                book.issuedTo = studentName;
                cout << "Book issued to " << studentName << "." << endl;
                return;
            }
        }
        cout << "Book not available or not found." << endl;
    }

    void returnBook(int id) {
        for (auto &book : books) {
            if (book.id == id && book.status == "issued") {
                book.status = "available";
                book.issuedTo = "";
                cout << "Book returned." << endl;
                return;
            }
        }
        cout << "Book not found or not issued." << endl;
    }

    void listAllBooks() {
        sort(books.begin(), books.end(), [](Book a, Book b) {
            return a.id < b.id;
        });

        for (auto &book : books) {
            book.display();
        }
    }

    void deleteBook(int id) {
        auto it = remove_if(books.begin(), books.end(), [id](Book &book) {
            return book.id == id;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book deleted." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }
};

int main() {
    Library lib;
    int choice, id;
    string title, author, studentName;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add New Book\n";
        cout << "2. Search for a Book by ID\n";
        cout << "3. Search for a Book by Title\n";
        cout << "4. Issue a Book\n";
        cout << "5. Return a Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete a Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: ";
            cin >> id;
            cout << "Enter Book Title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter Book Author: ";
            getline(cin, author);
            lib.addBook(id, title, author);
            break;

        case 2:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.searchBookByID(id);
            break;

        case 3:
            cout << "Enter Book Title: ";
            cin.ignore();
            getline(cin, title);
            lib.searchBookByTitle(title);
            break;

        case 4:
            cout << "Enter Book ID: ";
            cin >> id;
            cout << "Enter Student Name: ";
            cin.ignore();
            getline(cin, studentName);
            lib.issueBook(id, studentName);
            break;

        case 5:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.returnBook(id);
            break;

        case 6:
            lib.listAllBooks();
            break;

        case 7:
            cout << "Enter Book ID: ";
            cin >> id;
            lib.deleteBook(id);
            break;

        case 8:
            exit(0);

        default:
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
