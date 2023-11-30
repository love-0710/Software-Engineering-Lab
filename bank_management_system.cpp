#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

// Structure to represent user account
struct Account {
    string username;
    string password;
    double balance;
};

// Function to load account data from file
vector<Account> loadAccounts() {
    vector<Account> accounts;
    ifstream file("accounts.txt");

    if (!file.is_open()) {
        cerr << "Error opening accounts file.\n";
        exit(EXIT_FAILURE);
    }

    Account acc;
    while (file >> acc.username >> acc.password >> acc.balance) {
        accounts.push_back(acc);
    }

    file.close();
    return accounts;
}

// Function to save account data to file
void saveAccounts(const vector<Account>& accounts) {
    ofstream file("accounts.txt");

    if (!file.is_open()) {
        cerr << "Error opening accounts file.\n";
        exit(EXIT_FAILURE);
    }

    for (const auto& acc : accounts) {
        file << acc.username << " " << acc.password << " " << fixed << setprecision(2) << acc.balance << endl;
    }

    file.close();
}

// Function to authenticate a user
int authenticateUser(const vector<Account>& accounts, const string& username, const string& password) {
    for (const auto& acc : accounts) {
        if (acc.username == username && acc.password == password) {
            return 1; // Authentication successful
        }
    }

    return 0; // Authentication failed
}

// Function to display account balance
void displayBalance(const Account& acc) {
    cout << "Account Balance for " << acc.username << ": $" << fixed << setprecision(2) << acc.balance << endl;
}

// Function to perform a withdrawal
void withdraw(vector<Account>& accounts, const string& username, double amount) {
    for (auto& acc : accounts) {
        if (acc.username == username) {
            if (amount > 0 && amount <= acc.balance) {
                acc.balance -= amount;
                cout << "Withdrawal successful. Remaining balance: $" << fixed << setprecision(2) << acc.balance << endl;
                saveAccounts(accounts);
            } else {
                cout << "Invalid withdrawal amount or insufficient funds.\n";
            }
            return;
        }
    }
    cout << "Account not found.\n";
}

// Function to perform a deposit
void deposit(vector<Account>& accounts, const string& username, double amount) {
    for (auto& acc : accounts) {
        if (acc.username == username) {
            if (amount > 0) {
                acc.balance += amount;
                cout << "Deposit successful. New balance: $" << fixed << setprecision(2) << acc.balance << endl;
                saveAccounts(accounts);
            } else {
                cout << "Invalid deposit amount.\n";
            }
            return;
        }
    }
    cout << "Account not found.\n";
}

int main() {
    vector<Account> accounts = loadAccounts();

    int option;
    string username, password;
    double amount;

    cout << "Welcome to the Simple Banking System!\n";

    while (1) {
        cout << "\nPress '1' to Login\nPress '2' to Exit\n";
        cin >> option;

        switch (option) {
        case 1:
            cout << "Enter Username: ";
            cin >> username;
            cout << "Enter Password: ";
            cin >> password;

            if (authenticateUser(accounts, username, password)) {
                cout << "Login Successful!\n";

                while (1) {
                    cout << "\nPress '1' to Check Balance\nPress '2' to Withdraw\nPress '3' to Deposit\nPress '4' to Logout\n";
                    cin >> option;

                    switch (option) {
                    case 1:
                        displayBalance(accounts[0]); // Assuming a single user for simplicity
                        break;
                    case 2:
                        cout << "Enter withdrawal amount: $";
                        cin >> amount;
                        withdraw(accounts, username, amount);
                        break;
                    case 3:
                        cout << "Enter deposit amount: $";
                        cin >> amount;
                        deposit(accounts, username, amount);
                        break;
                    case 4:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid option. Please try again.\n";
                    }

                    if (option == 4) {
                        break;
                    }
                }
            } else {
                cout << "Incorrect Login Details\n";
            }
            break;
        case 2:
            cout << "Exiting the program.\n";
            return 0;
        default:
            cout << "Invalid option. Please try again.\n";
        }
    }

    return 0;
}
