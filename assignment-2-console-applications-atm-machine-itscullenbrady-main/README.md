
# ATM Application Documentation

## Overview
This ATM application simulates basic banking operations such as creating an account, logging in, depositing money, withdrawing money, and checking the balance. The application uses C++ for implementation and includes proper exception handling and separation of declarations and definitions using header files.  

## Files
- **atm.h**: Contains declarations of functions and global variables.
- **atm.cpp**: Contains the implementation of the functions and the definition of global variables.

---

### Header File (atm.h)
The header file is used to declare functions and global variables that are shared across multiple source files. This ensures that the compiler knows about these functions and variables before they are used.

```cpp
#ifndef ATM_H
#define ATM_H

#include <string>
#include <unordered_map>

// Function prototypes
void printIntroMenu();
void printMainMenu();
void start();
void login();
void createAccount();

// Global variables for use across different source files
extern char menuInput;
extern std::unordered_map<std::string, std::string> accounts;
extern double balance;

#endif // ATM_H
```
- **Include Guards**: Prevents multiple inclusions of the same header file.
- **Includes**: Necessary libraries for `string` and `unordered_map`.
- **Function Prototypes**: Declarations of functions used in the application.
- **Global Variables**: Declarations of global variables used across different source files.

---

### Source File (atm.cpp)
The source file contains the implementation of the functions and the definition of global variables.

```cpp
#include "atm.h"
#include <iostream>
#include <limits>
#include <unordered_map>
#include <stdexcept>

// Initialize global variables
char menuInput;
std::unordered_map<std::string, std::string> accounts;
double balance = 0.0;
```

- **Includes**: Includes the header file and necessary libraries for input/output, limits, unordered_map, and exception handling.
- **Global Variables**: Definitions of global variables declared in the header file.

---

### Main Function
The entry point of the application. It initializes the application and handles any exceptions that occur.

```cpp
int main() {
    try {
        std::cout << "Hi! Welcome to the ATM Machine for Scotia Bank \n\n";
        start();
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << '\n';
    }
    return 0;
}
```

- **try-catch Block**: Catches any exceptions thrown during the execution of the `start` function and prints an error message.

---

### Menu Functions
Functions to print the introductory and main menus.

```cpp
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
```

- **printIntroMenu**: Prints the introductory menu with options to login, create an account, or quit.
- **printMainMenu**: Prints the main menu with options to deposit money, withdraw money, request balance, or quit.

---

### Start Function
Handles the main loop of the application, allowing the user to select options from the introductory menu.

```cpp
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
```

- **do-while Loop**: Continuously displays the introductory menu until the user chooses to quit.
- **try-catch Block**: Catches any invalid selections and prompts the user to try again.

---

### Create Account Function
Allows the user to create a new account by entering a user ID and password.

```cpp
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
```

- **try-catch Block**: Catches any invalid inputs (empty user ID or password) and prompts the user to try again.

---

### Login Function
Allows the user to log in by entering a valid user ID and password.

```cpp
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
```

- **try-catch Block**: Catches any invalid inputs (invalid user ID or password) and prompts the user to try again.
- **Nested try-catch Block**: Handles invalid selections and invalid amounts during ATM operations.

---

### ATM Operations
Handles deposit, withdrawal, and balance request operations.

- **Deposit Money**: Prompts the user to enter an amount to deposit. If the amount is valid, it is added to the balance.
- **Withdraw Money**: Prompts the user to enter an amount to withdraw. If the amount is valid and there are sufficient funds, it is subtracted from the balance.
- **Request Balance**: Displays the current balance.
- **Logout**: Logs the user out and returns to the introductory menu.
