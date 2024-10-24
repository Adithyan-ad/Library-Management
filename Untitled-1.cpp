#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Book {
private:
    string title;
    string author;
    int bookID;
    string category;
    bool isBorrowed;
public:
    //initializing constructor 'Book' by assigning it to the private member variables.
    Book(string t, string a, int id, string c) : title(t), author(a), bookID(id), category(c), isBorrowed(false) {}

    //Getter methods.
    string getTitle() { return title; }
    string getAuthor() { return author; }
    int getBookID() { return bookID; }
    string getCategory() { return category; }
    bool getBorrowedStatus() { return isBorrowed; }

    //Setter methods for isBorrowed.
    void borrowBook() { isBorrowed = true; }
    void returnBook() { isBorrowed = false; }
    
    //Displays the book details.
    void displayBook() {
        cout << "ID: " << bookID << ", Title: " << title << ", Author: " << author
             << ", Category: " << category << ", Status: " << (isBorrowed ? "Borrowed" : "Available") << endl;
    }
};

class User {
private:
    string username;
    vector<int> borrowedBooks; // Book IDs
public:
    //initializing constructor 'User' by assigning it to the private member variables.
    User(string name) : username(name) {}

    //Getter method
    string getUsername() { return username; }
    
    bool canBorrowMore() {
        return borrowedBooks.size() < 3; // Limit to 3 books at a time
    }

    void borrowBook(int bookID) {
        if (canBorrowMore()) {
            borrowedBooks.push_back(bookID);
        } else {
            cout << "You cannot borrow more than 3 books." << endl;
        }
    }

    void returnBook(int bookID) {
        auto it = find(borrowedBooks.begin(), borrowedBooks.end(), bookID);
        if (it != borrowedBooks.end()) {
            borrowedBooks.erase(it);
        }
    }

    void showBorrowedBooks() {
        cout << username << "'s Borrowed Books: ";
        for (int id : borrowedBooks) {
            cout << id << " ";
        }
        cout << endl;
    }
};

class Library {
private:
    vector<Book> books;
    vector<User> users;
public:
    void addBook(string title, string author, int id, string category) {
        books.push_back(Book(title, author, id, category));
    }

    void displayBooks() {
        for (Book& book : books) {
            book.displayBook();
        }
    }

    void searchByCategory(string category) {
        cout << "Books in category " << category << ":" << endl;
        for (Book& book : books) {
            if (book.getCategory() == category) {
                book.displayBook();
            }
        }
    }

    void searchByTitle(string title){
        cout << "Books in title" << title << ":" << endl;
        for (Book& book : books){
            if (book.getTitle() == title){
                book.displayBook();
            }
        }
    }

    void registerUser(string username) {
        users.push_back(User(username));
    }


    User* findUser(string username) {
        for (User& user : users) {
            if (user.getUsername() == username) {
                return &user;
            }
        }
        return nullptr;
    }

    void borrowBook(string username, int id) {
        User* user = findUser(username);
        if (!user) {
            cout << "User not found." << endl;
            return;
        }

        for (Book& book : books) {
            if (book.getBookID() == id && !book.getBorrowedStatus()) {
                user->borrowBook(id);
                book.borrowBook();
                cout << "Book borrowed successfully." << endl;
                return;
            }
        }
        cout << "Book not available." << endl;
    }

    void returnBook(string username, int id) {
        User* user = findUser(username);
        if (!user) {
            cout << "User not found." << endl;
            return;
        }

        for (Book& book : books) {
            if (book.getBookID() == id && book.getBorrowedStatus()) {
                user->returnBook(id);
                book.returnBook();
                cout << "Book returned successfully." << endl;
                return;
            }
        }
        cout << "Book not found or not borrowed." << endl;
    }
};

int main() {
    Library library;
    library.addBook("The Catcher in the Rye", "J.D. Salinger", 1, "Fiction");
    library.addBook("A Brief History of Time", "Stephen Hawking", 2, "Science");
    library.addBook("The Roots","Alex",3,"Political");
    
    //registering users 
    library.registerUser("Adithyan");

    cout << "All Books in Library:" << endl;
    library.displayBooks();

    cout << "\nBorrowing Book ID 1 for vijay:" << endl;
    library.borrowBook("vijay", 1);
    cout << "\nBorrowing Book ID 3 for Adithyan:" << endl;
    library.borrowBook("Adithyan",3);
    cout << "\nBorrowing Book ID 2 for Adithyan:" << endl;
    library.borrowBook("Adithyan",2);

     
    User* adithyan = library.findUser("Adithyan");
    if (adithyan) {
        adithyan->showBorrowedBooks();
    }

    cout << "\nSearching for Political Books:" << endl;
    library.searchByCategory("Political");
    
    cout << "\nSearching for books based on title: "
    library.searchByTitle("The Roots");

    

    return 0;
}
