#include "atm.h"
#include <iostream>
#include <limits>
#include <unordered_map>
#include <stdexcept>

// Initialize global variables
char menuInput;
std::unordered_map<std::string, std::string> accounts;
double balance = 0.0;

int main() {
    try {
        std::cout << "Hi! Welcome to the ATM Machine for Scotia Bank \n\n";
        start();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << '\n';
    }
    return 0;
}

void printIntroMenu() {
    std::cout << "Please select an option from the menu below:\n";
    std::cout << "l -> Login\n";
    std::cout << "c -> Create New Account\n";
    std::cout << "q -> Quit\n";
    std::cout << "> ";
}

void printMainMenu() {
    std::cout << "d -> Deposit Money\n";
    std::cout << "w -> Withdraw Money\n";
    std::cout << "r -> Request Balance\n";
    std::cout << "q -> Quit\n";
    std::cout << "> ";
}

void start() {
    do {
        printIntroMenu();
        std::cin >> menuInput;

        try {
            switch (menuInput) {
                case 'l':
                    login();
                    break;
                case 'c':
                    createAccount();
                    break;
                case 'q':
                    std::cout << "Thanks for stopping by!\n";
                    exit(0);
                default:
                    throw std::invalid_argument("Invalid selection. Please try again.");
            }
        } catch (const std::exception& e) {
            std::cerr << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (menuInput != 'q');
}

void createAccount() {
    try {
        std::string userId, password;
        std::cout << "Please enter your user ID: ";
        std::cin >> userId;
        std::cout << "Please enter your password: ";
        std::cin >> password;

        if (userId.empty() || password.empty()) {
            throw std::invalid_argument("User ID and password cannot be empty.");
        }

        accounts[userId] = password;
        std::cout << "Thank you! Your account has been created!\n";
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void login() {
    try {
        std::string userId, password;
        std::cout << "Please enter your user ID: ";
        std::cin >> userId;
        std::cout << "Please enter your password: ";
        std::cin >> password;

        if (accounts.find(userId) != accounts.end() && accounts[userId] == password) {
            std::cout << "Access Granted!\n";
            char atmChoice;
            do {
                printMainMenu();
                std::cin >> atmChoice;
                try {
                    switch (atmChoice) {
                        case 'd': {
                            double amount;
                            std::cout << "Amount to deposit: $";
                            while (!(std::cin >> amount) || amount <= 0) {
                                throw std::invalid_argument("Invalid amount. Please enter a positive number.");
                            }
                            balance += amount;
                            std::cout << "Deposited successfully.\n";
                            break;
                        }
                        case 'w': {
                            double amount;
                            std::cout << "Amount to withdraw: $";
                            while (!(std::cin >> amount) || amount <= 0) {
                                throw std::invalid_argument("Invalid amount. Please enter a positive number.");
                            }
                            if (amount > balance) {
                                std::cout << "Insufficient funds. Your current balance is: $" << balance << "\n";
                            } else {
                                balance -= amount;
                                std::cout << "Withdrawn successfully.\n";
                            }
                            break;
                        }
                        case 'r':
                            std::cout << "Your current balance is: $" << balance << "\n";
                            break;
                        case 'q':
                            std::cout << "Logging out...\n";
                            break;
                        default:
                            throw std::invalid_argument("Invalid selection. Please try again.");
                    }
                } catch (const std::exception& e) {
                    std::cerr << e.what() << '\n';
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while (atmChoice != 'q');
        } else {
            throw std::invalid_argument("Invalid user ID or password. Please try again.");
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}