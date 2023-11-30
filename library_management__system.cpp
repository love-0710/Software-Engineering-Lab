#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// Define the structure for user information
struct User {
    char username[30];
    char password[20];
};

// Create Structure of Library
struct Library {
    char book_name[20];
    char author[20];
    int pages;
    float price;
};

// Function to register a new user
void registerUser() {
    User newUser;
    ofstream file("users.txt", ios::app);

    cout << "\nEnter Username: ";
    cin >> newUser.username;
    cout << "Enter Password: ";
    cin >> newUser.password;

    // Write the new user information to the file
    file << newUser.username << " " << newUser.password << endl;

    file.close();
    cout << "\nRegistration Successful!\n";
}

// Function to authenticate a user
int authenticateUser(char *username, char *password) {
    User user;
    ifstream file("users.txt");

    while (file >> user.username >> user.password) {
        if (strcmp(username, user.username) == 0 && strcmp(password, user.password) == 0) {
            file.close();
            return 1; // Authentication successful
        }
    }

    file.close();
    return 0; // Authentication failed
}

// Function to display all user data (for admin)
void displayAllUserData() {
    User user;
    ifstream file("users.txt");

    cout << "\nAll User Data:\n";
    while (file >> user.username >> user.password) {
        cout << "Username: " << user.username << ", Password: " << user.password << endl;
    }

    file.close();
}

// Driver Code for E-library Management System
int main() {
    int option;
    char username[30], password[20];

    while (1) {
        cout << "\nPress '1' to Register\nPress '2' to Login\nPress '3' to Exit\n";
        cin >> option;

        switch (option) {
        case 1:
            registerUser();
            break;
        case 2:
            cout << "\nEnter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            if (authenticateUser(username, password)) {
                cout << "\nLogin Successful!\n";

                // Check if the logged-in user is an admin
                if (strcmp(username, "admin") == 0) {
                    displayAllUserData();
                } else {
                    // Proceed to E-library Management System
                    Library lib[100];
                    char ar_nm[30];
                    int i, input, count;

                    i = input = count = 0;

                    while (input != 5) {
                        cout << "\n\n********######"
                             "WELCOME TO E-LIBRARY "
                             "#####********\n";
                        cout << "\n\n1. Add book infor"
                             "mation\n2. Display "
                             "book information\n";
                        cout << "3. List all books of "
                             "given author\n";
                        cout << "4. List the count of book"
                             "s in the library\n";
                        cout << "5. Exit";

                        cout << "\n\nEnter one of "
                             "the above: ";
                        cin >> input;

                        switch (input) {
                        case 1:
                            cout << "Enter book name = ";
                            cin >> lib[i].book_name;

                            cout << "Enter author name = ";
                            cin >> lib[i].author;

                            cout << "Enter pages = ";
                            cin >> lib[i].pages;

                            cout << "Enter price = ";
                            cin >> lib[i].price;
                            count++;
                            break;

                        case 2:
                            cout << "You have entered"
                                 " the following "
                                 "information\n";
                            for (i = 0; i < count; i++) {
                                cout << "book name = " << lib[i].book_name;
                                cout << "\t author name = " << lib[i].author;
                                cout << "\t pages = " << lib[i].pages;
                                cout << "\t price = " << lib[i].price;
                            }
                            break;

                        case 3:
                            cout << "Enter author name : ";
                            cin >> ar_nm;
                            for (i = 0; i < count; i++) {
                                if (strcmp(ar_nm, lib[i].author) == 0)
                                    cout << lib[i].book_name << " " << lib[i].author << " " << lib[i].pages << " " << lib[i].price;
                            }
                            break;

                        case 4:
                            cout << "\n No of books in "
                                 "brary : " << count;
                            break;
                        case 5:
                            exit(0);
                        }
                    }
                }
            } else {
                cout << "\nIncorrect Login Details\n";
            }
            break;
        case 3:
            cout << "\nExiting the program.\n";
            exit(0);
        default:
            cout << "\nInvalid option. Please try again.\n";
        }
    }

    return 0;
}
