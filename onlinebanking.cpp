#include <iostream>
#include <vector>
#include <string>
#include <ctime>

class Transaction {
public:
    enum Type {
        DEPOSIT,
        WITHDRAWAL
    };

    double amount;
    Type type;
    time_t timestamp;

    Transaction(double amount, Type type) : amount(amount), type(type), timestamp(time(nullptr)) {}
};

class User {
private:
    std::string userId;
    std::string password;
    double balance;
    double interestRate;
    std::vector<Transaction> transactionHistory;

public:
    User(std::string userId, std::string password, double initialBalance, double interestRate)
        : userId(userId), password(password), balance(initialBalance), interestRate(interestRate) {}

    std::string getUserId() const {
        return userId;
    }

    std::string getPassword() const {
        return password;
    }

    double getBalance() const {
        return balance;
    }

    void displayInfo() const {
        std::cout << "User ID: " << userId << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }

    void showInterest() const {
        double interest = balance * (interestRate / 100);
        std::cout << "Interest on deposit: $" << interest << std::endl;
    }

    void showTransactionHistory() const {
        std::cout << "Transaction History:" << std::endl;
        for (const auto& transaction : transactionHistory) {
            std::cout << "Amount: $" << transaction.amount << " | Type: "
                      << (transaction.type == Transaction::DEPOSIT ? "Deposit" : "Withdrawal")
                      << " | Timestamp: " << std::asctime(std::localtime(&transaction.timestamp));
        }
    }

    void processTransaction(double amount, Transaction::Type type) {
        if (type == Transaction::WITHDRAWAL && amount > balance) {
            std::cout << "Insufficient funds for withdrawal." << std::endl;
            return;
        }

        if (type == Transaction::WITHDRAWAL) {
            balance -= amount;
        } else {
            balance += amount;
        }

        transactionHistory.emplace_back(amount, type);
        std::cout << (type == Transaction::DEPOSIT ? "Deposit" : "Withdrawal") << " of $" << amount
                  << " processed successfully." << std::endl;
    }

    // Other member functions for changing ID, modifying ID, etc.

    friend class Admin;
};

class Admin {
public:
    void showAllDetails(const std::vector<User>& users) const {
        std::cout << "User Details:" << std::endl;
        for (const auto& user : users) {
            std::cout << "User ID: " << user.userId << std::endl;
            std::cout << "Balance: $" << user.balance << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
};

class OnlineBanking {
private:
    std::vector<User> users;

public:
    User* login() {
        std::string userId, password;
        std::cout << "Enter user ID: ";
        std::cin >> userId;
        std::cout << "Enter password: ";
        std::cin >> password;

        for (auto& user : users) {
            if (user.getUserId() == userId && user.getPassword() == password) {
                return &user;
            }
        }

        std::cout << "Login failed. Invalid user ID or password." << std::endl;
        return nullptr;
    }

    void addUser() {
        std::string userId, password;
        double initialBalance, interestRate;

        std::cout << "Enter user ID: ";
        std::cin >> userId;
        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Enter initial balance: $";
        std::cin >> initialBalance;
        std::cout << "Enter interest rate: ";
        std::cin >> interestRate;

        users.emplace_back(userId, password, initialBalance, interestRate);
        std::cout << "\nUser added successfully." << std::endl;
    }

    void run() {
        while (true) {
            std::cout << "\n1. Login" << std::endl;
            std::cout << "2. Add User" << std::endl;
            std::cout << "3. Admin Protocol" << std::endl;
            std::cout << "4. Exit" << std::endl;
            int choice;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 1) {
                User* loggedInUser = login();
                if (loggedInUser != nullptr) {
                    while (true) {
                        std::cout << "\n1. Display Profile" << std::endl;
                        std::cout << "2. Show Interest" << std::endl;
                        std::cout << "3. Show Withdraw Details" << std::endl;
                        std::cout << "4. Deposit Money" << std::endl;
                        std::cout << "5. Withdraw Money" << std::endl;
                        std::cout << "6. Show Transaction History" << std::endl;
                        std::cout << "7. Logout" << std::endl;
                        std::cout << "Enter your choice: ";
                        std::cin >> choice;

                        if (choice == 1) {
                            loggedInUser->displayInfo();
                        } else if (choice == 2) {
                            loggedInUser->showInterest();
                        } else if (choice == 3) {
                            double withdrawAmount;
                            std::cout << "Enter withdrawal amount: $";
                            std::cin >> withdrawAmount;
                            loggedInUser->processTransaction(withdrawAmount, Transaction::WITHDRAWAL);
                        } else if (choice == 4) {
                            double depositAmount;
                            std::cout << "Enter deposit amount: $";
                            std::cin >> depositAmount;
                            loggedInUser->processTransaction(depositAmount, Transaction::DEPOSIT);
                        } else if (choice == 5) {
                            double withdrawAmount;
                            std::cout << "Enter withdrawal amount: $";
                            std::cin >> withdrawAmount;
                            loggedInUser->processTransaction(withdrawAmount, Transaction::WITHDRAWAL);
                        } else if (choice == 6) {
                            loggedInUser->showTransactionHistory();
                        } else if (choice == 7) {
                            break;
                        } else {
                            std::cout << "Invalid choice. Please try again." << std::endl;
                        }
                    }
                }
            } else if (choice == 2) {
                addUser();
            } else if (choice == 3) {
                Admin admin;
                admin.showAllDetails(users);
            } else if (choice == 4) {
                break;
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    OnlineBanking onlineBanking;
    onlineBanking.run();

    return 0;
}
