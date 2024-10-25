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

#endif
