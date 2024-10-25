//
// Created by Cullen Murphy-Brady on 10/25/24.
//
#include "atm.h"
#include <iostream>
#include <limits>
#include <unordered_map>

// Initialize global variables
char menuInput;
std::unordered_map<std::string, std::string> accounts;
double balance = 0.0;

int main() {
    std::cout << "Hi! Welcome to the ATM Machine for Scotia Bank \n\n";
    start();
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
                std::cout << "Invalid selection. Please try again.\n";
        }
    } while (menuInput != 'q');
}

void createAccount() {
    std::string userId, password;
    std::cout << "Please enter your user ID: ";
    std::cin >> userId;
    std::cout << "Please enter your password: ";
    std::cin >> password;
    accounts[userId] = password;
    std::cout << "Thank you! Your account has been created!\n";
}

void login() {
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
            switch (atmChoice) {
                case 'd': {
                    double amount;
                    std::cout << "Amount to deposit: $";
                    while (!(std::cin >> amount) || amount <= 0) {
                        std::cout << "Invalid amount. Please enter a positive number: $";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    balance += amount;
                    std::cout << "Deposited successfully.\n";
                    break;
                }
                case 'w': {
                    double amount;
                    std::cout << "Amount to withdraw: $";
                    while (!(std::cin >> amount) || amount <= 0) {
                        std::cout << "Invalid amount. Please enter a positive number: $";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    balance -= amount;
                    std::cout << "Withdrawn successfully.\n";
                    break;
                }
                case 'r':
                    std::cout << "Your current balance is: $" << balance << "\n";
                    break;
                case 'q':
                    std::cout << "Logging out...\n";
                    break;
                default:
                    std::cout << "Invalid selection. Please try again.\n";
            }
        } while (atmChoice != 'q');
    } else {
        std::cout << "Invalid user ID or password. Please try again.\n";
    }
}