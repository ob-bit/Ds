#include <iostream>
#include <string>
using namespace std;

// Structure for a Book Node
struct Book {
    int id;
    string title;
    string author;
    Book* next;
};

class Library {
private:
    Book* head; // Start of the linked list

public:
    Library() : head(nullptr) {}

    // 1. Add a Book to the end of the list
    void addBook(int id, string title, string author) {
        Book* newBook = new Book{id, title, author, nullptr};
        if (!head) {
            head = newBook;
        } else {
            Book* temp = head;
            while (temp->next) temp = temp->next;
            temp->next = newBook;
        }
        cout << "Book added successfully!\n";
    }

    // 2. Delete a Book by ID
    void deleteBook(int id) {
        if (!head) {
            cout << "Library is empty.\n";
            return;
        }
        if (head->id == id) {
            Book* temp = head;
            head = head->next;
            delete temp;
            cout << "Book with ID " << id << " deleted.\n";
            return;
        }
        Book* curr = head;
        Book* prev = nullptr;
        while (curr && curr->id != id) {
            prev = curr;
            curr = curr->next;
        }
        if (!curr) {
            cout << "Book not found.\n";
        } else {
            prev->next = curr->next;
            delete curr;
            cout << "Book deleted.\n";
        }
    }

    // 3. Search for a Book by ID
    void searchBook(int id) {
        Book* temp = head;
        while (temp) {
            if (temp->id == id) {
                cout << "Found: " << temp->title << " by " << temp->author << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Book with ID " << id << " not found.\n";
    }

    // 4. Display all Books
    void displayBooks() {
        if (!head) {
            cout << "No books in the library.\n";
            return;
        }
        Book* temp = head;
        cout << "\n--- Library Inventory ---\n";
        while (temp) {
            cout << "ID: " << temp->id << " | Title: " << temp->title << " | Author: " << temp->author << "\n";
            temp = temp->next;
        }
    }
};

int main() {
    Library myLibrary;
    int choice, id;
    string title, author;

    while (true) {
        cout << "\n--- Library Management System ---";
        cout << "\n1. Add Book\n2. Delete Book\n3. Search Book\n4. Display All\n5. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter ID: "; cin >> id;
                cin.ignore(); // Clear buffer
                cout << "Enter Title: "; getline(cin, title);
                cout << "Enter Author: "; getline(cin, author);
                myLibrary.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter ID to delete: "; cin >> id;
                myLibrary.deleteBook(id);
                break;
            case 3:
                cout << "Enter ID to search: "; cin >> id;
                myLibrary.searchBook(id);
                break;
            case 4:
                myLibrary.displayBooks();
                break;
            case 5:
                cout << "Exiting system...";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
