#include "./BankSystem.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

BankSystem::BankSystem()
{
    loadUsers();
}
void BankSystem::loadUsers()
{
    std::ifstream inFile("users.txt");
    if (inFile.is_open())
    {
        std::string username, password;
        while (inFile >> username >> password)
        {
            users[username] = password;
        }
        inFile.close();
        std::cout << "Users loaded successfully!" << std::endl;
    }
    else
    {
        std::cout << "No user file found, starting fresh." << std::endl;
    }
}

void BankSystem::saveUsers()
{
    std::ofstream outFile("users.txt");
    if (outFile.is_open())
    {
        for (const auto &user : users)
        {
            outFile << user.first << " " << user.second << std::endl;
        }
        outFile.close();
        std::cout << "Users saved successfully!" << std::endl;
    }
    else
    {
        std::cout << "Error saving users to file." << std::endl;
    }
}

bool BankSystem::authenticate(std::string username, std::string password)
{
    std::cout << "Checking credentials for username: " << username << std::endl;

    if (users.find(username) != users.end() && users[username] == password)
    {
        std::cout << "Authentication successful!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Authentication failed!" << std::endl;
        return false;
    }
}

void BankSystem::createUser(std::string username, std::string password)
{
    users[username] = password;
    saveUsers();
}

void BankSystem::createAccount(std::string username, std::string accountType)
{
    int accNumber;
    float initialBalance, interestRate, overdraftLimit;
    std::cout << "Enter initial balance: $";
    std::cin >> initialBalance;
    accNumber = rand() % 100000;

    if (accountType == "Savings")
    {
        std::cout << "Enter interest rate (%): ";
        std::cin >> interestRate;
        BankAccount *newAccount = new SavingsAccount(username, accNumber, initialBalance, interestRate);
        userAccounts[username].push_back(newAccount);
    }
    else if (accountType == "Checking")
    {
        std::cout << "Enter overdraft limit: $";
        std::cin >> overdraftLimit;
        BankAccount *newAccount = new CheckingAccount(username, accNumber, initialBalance, overdraftLimit);
        userAccounts[username].push_back(newAccount);
    }

    std::cout << "Account created successfully with Account Number: " << accNumber << std::endl;
}

BankAccount *BankSystem::selectAccount(std::string username)
{
    if (userAccounts[username].empty())
    {
        std::cout << "No accounts found for user." << std::endl;
        return nullptr;
    }

    std::cout << "Select Account:" << std::endl;
    for (size_t i = 0; i < userAccounts[username].size(); ++i)
    {
        std::cout << i + 1 << ". " << userAccounts[username][i]->getAccountType() << " - Account Number: "
                  << userAccounts[username][i]->getAccountNumber() << std::endl;
    }

    int choice;
    std::cin >> choice;

    if (choice > 0 && choice <= userAccounts[username].size())
    {
        return userAccounts[username][choice - 1];
    }
    else
    {
        std::cout << "Invalid choice!" << std::endl;
        return nullptr;
    }
}

void BankSystem::manageAccount(std::string username)
{
    BankAccount *account = selectAccount(username);
    if (account == nullptr)
        return;

    int choice;
    do
    {
        std::cout << "1. Deposit" << std::endl;
        std::cout << "2. Withdraw" << std::endl;
        std::cout << "3. View Balance" << std::endl;
        std::cout << "4. View Transaction History" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            float amount;
            std::cout << "Enter deposit amount: $";
            std::cin >> amount;
            account->deposit(amount);
            break;
        }
        case 2:
        {
            float amount;
            std::cout << "Enter withdrawal amount: $";
            std::cin >> amount;
            account->withdraw(amount);
            break;
        }
        case 3:
            std::cout << "Current Balance: $" << account->getBalance() << std::endl;
            break;
        case 4:
            account->showTransactionHistory();
            break;
        case 5:
            std::cout << "Exiting account management." << std::endl;
            break;
        default:
            std::cout << "Invalid option!" << std::endl;
        }
    } while (choice != 5);
}
