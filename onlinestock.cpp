#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>

class Trade {
public:
    enum Type {
        BUY,
        SELL
    };

    std::string stockSymbol;
    int quantity;
    double price;
    Type type;
    time_t timestamp;

    Trade(std::string stockSymbol, int quantity, double price, Type type)
        : stockSymbol(stockSymbol), quantity(quantity), price(price), type(type), timestamp(time(nullptr)) {}
};

class User {
private:
    std::string userId;
    std::string password;
    double balance;
    std::vector<Trade> tradeHistory;

public:
    User(std::string userId, std::string password, double initialBalance)
        : userId(userId), password(password), balance(initialBalance) {}

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

    void showTradeHistory() const {
        std::cout << "Trade History:" << std::endl;
        for (const auto& trade : tradeHistory) {
            std::cout << "Stock: " << trade.stockSymbol << " | Quantity: " << trade.quantity
                      << " | Price: $" << trade.price << " | Type: " << (trade.type == Trade::BUY ? "Buy" : "Sell")
                      << " | Timestamp: " << std::asctime(std::localtime(&trade.timestamp));
        }
    }

    void processTrade(std::string stockSymbol, int quantity, double price, Trade::Type type) {
        double tradeAmount = quantity * price;

        if (type == Trade::SELL && quantity > getStockQuantity(stockSymbol)) {
            std::cout << "Insufficient stocks for selling." << std::endl;
            return;
        }

        if (type == Trade::BUY && tradeAmount > balance) {
            std::cout << "Insufficient funds for buying." << std::endl;
            return;
        }

        if (type == Trade::SELL) {
            balance += tradeAmount;
        } else {
            balance -= tradeAmount;
        }

        tradeHistory.emplace_back(stockSymbol, quantity, price, type);
        std::cout << (type == Trade::BUY ? "Buy" : "Sell") << " of " << quantity << " stocks of " << stockSymbol
                  << " processed successfully." << std::endl;
    }

    int getStockQuantity(std::string stockSymbol) const {
        int stockQuantity = 0;
        for (const auto& trade : tradeHistory) {
            if (trade.stockSymbol == stockSymbol) {
                stockQuantity += (trade.type == Trade::BUY ? trade.quantity : -trade.quantity);
            }
        }
        return stockQuantity;
    }

    // Other member functions for changing ID, modifying ID, etc.
};

class OnlineTradeManagement {
private:
    std::vector<User> users;
    std::vector<std::string> availableStocks = {"AAPL", "GOOGL", "AMZN", "MSFT", "TSLA"};

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
        double initialBalance;

        std::cout << "Enter user ID: ";
        std::cin >> userId;
        std::cout << "Enter password: ";
        std::cin >> password;
        std::cout << "Enter initial balance: $";
        std::cin >> initialBalance;

        users.emplace_back(userId, password, initialBalance);
        std::cout << "\nUser added successfully." << std::endl;
    }

    void run() {
        while (true) {
            std::cout << "\n1. Login" << std::endl;
            std::cout << "2. Add User" << std::endl;
            std::cout << "3. Stock Trading" << std::endl;
            std::cout << "4. Exit" << std::endl;
            int choice;
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 1) {
                User* loggedInUser = login();
                if (loggedInUser != nullptr) {
                    while (true) {
                        std::cout << "\n1. Display Profile" << std::endl;
                        std::cout << "2. Show Trade History" << std::endl;
                        std::cout << "3. Buy Stocks" << std::endl;
                        std::cout << "4. Sell Stocks" << std::endl;
                        std::cout << "5. Logout" << std::endl;
                        std::cout << "Enter your choice: ";
                        std::cin >> choice;

                        if (choice == 1) {
                            loggedInUser->displayInfo();
                        } else if (choice == 2) {
                            loggedInUser->showTradeHistory();
                        } else if (choice == 3 || choice == 4) {
                            std::string stockSymbol;
                            int quantity;
                            double price;

                            std::cout << "Enter stock symbol (e.g., AAPL): ";
                            std::cin >> stockSymbol;
                            if (std::find(availableStocks.begin(), availableStocks.end(), stockSymbol) ==
                                availableStocks.end()) {
                                std::cout << "Invalid stock symbol." << std::endl;
                                continue;
                            }

                            std::cout << "Enter quantity: ";
                            std::cin >> quantity;

                            if (choice == 3) {
                                std::cout << "Enter buy price per stock: $";
                                std::cin >> price;
                            } else {
                                std::cout << "Enter sell price per stock: $";
                                std::cin >> price;
                            }

                            loggedInUser->processTrade(stockSymbol, quantity, price,
                                                       (choice == 3 ? Trade::BUY : Trade::SELL));
                        } else if (choice == 5) {
                            break;
                        } else {
                            std::cout << "Invalid choice. Please try again." << std::endl;
                        }
                    }
                }
            } else if (choice == 2) {
                addUser();
            } else if (choice == 3) {
                // Implement stock trading features
                std::cout << "Stock trading features coming soon!" << std::endl;
            } else if (choice == 4) {
                break;
            } else {
                std::cout << "Invalid choice. Please try again." << std::endl;
            }
        }
    }
};

int main() {
    OnlineTradeManagement onlineTradeManagement;
    onlineTradeManagement.run();

    return 0;
}
