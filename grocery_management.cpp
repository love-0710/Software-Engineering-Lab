#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

// Define the structure for user information
struct User {
    string username;
    string password;
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
int authenticateUser(string username, string password) {
    User user;
    ifstream file("users.txt");

    while (file >> user.username >> user.password) {
        if (username == user.username && password == user.password) {
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

int main() {
    int option;
    string username, password;

    while (true) {
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
                    if (username == "admin") {
                        displayAllUserData();
                    } else {
                        // Proceed to Grocery Management System

                        struct Date {
                            int day;
                            int month;
                            int year;
                        };

                        struct Details {
                            string name;
                            int price;
                            int total_price;
                            int code;
                            int qty;
                            Date mfg;
                        };

                        const int MAX_ITEMS = 50;
                        Details item[MAX_ITEMS];
                        int n, i;

                        cout << "Enter number of items:";
                        cin >> n;

                        for (i = 0; i < n; i++) {
                            cout << "Item name: ";
                            cin >> item[i].name;
                            cout << "Item code: ";
                            cin >> item[i].code;
                            cout << "Quantity: ";
                            cin >> item[i].qty;
                            cout << "Price: ";
                            cin >> item[i].price;
                            cout << "Manufacturing date (dd-mm-yyyy): ";
                            cin >> item[i].mfg.day >> item[i].mfg.month >> item[i].mfg.year;
                        }

                        // ... (rest of the code)

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
