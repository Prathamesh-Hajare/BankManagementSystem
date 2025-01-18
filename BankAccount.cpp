// BankAccount class implementation

#include "BankAccount.h"
#include <fstream>
#include <ctime>

BankAccount::BankAccount(std::string name, int accNumber, float initialBalance)
    : accountHolder(name), accountNumber(accNumber), balance(initialBalance)
{
    transactionHistory.push_back("Account created.");
}

void BankAccount::displayDetails()
{
    std::cout << "Account Holder: " << accountHolder << std::endl;
    std::cout << "Account Number: " << accountNumber << std::endl;
    std::cout << "Balance: $" << balance << std::endl;
}

void BankAccount::showTransactionHistory()
{
    std::cout << "Transaction History for Account Number " << accountNumber << ":" << std::endl;
    for (const std::string &transaction : transactionHistory)
    {
        std::cout << transaction << std::endl;
    }
}

void BankAccount::logTransaction(const std::string &message)
{
    time_t now = time(0);
    std::string dt = ctime(&now);
    dt.pop_back();
    transactionHistory.push_back(dt + " - " + message);
}

float BankAccount::getBalance() const
{
    return balance;
}

void BankAccount::saveToFile()
{
    std::ofstream outFile(std::to_string(accountNumber) + "_account.txt");
    outFile << "Account Holder: " << accountHolder << std::endl;
    outFile << "Account Number: " << accountNumber << std::endl;
    outFile << "Balance: $" << balance << std::endl;
    outFile << "Transaction History: " << std::endl;
    for (const std::string &transaction : transactionHistory)
    {
        outFile << transaction << std::endl;
    }
    outFile.close();
}

// SavingsAccount class implementations
SavingsAccount::SavingsAccount(std::string name, int accNumber, float initialBalance, float rate)
    : BankAccount(name, accNumber, initialBalance), interestRate(rate) {}

void SavingsAccount::deposit(float amount)
{
    balance += amount;
    balance += (balance * interestRate / 100);
    logTransaction("Deposited $" + std::to_string(amount) + " with interest.");
}

void SavingsAccount::withdraw(float amount)
{
    if (amount > balance)
    {
        std::cout << "Insufficient balance!" << std::endl;
        logTransaction("Failed withdrawal of $" + std::to_string(amount));
    }
    else
    {
        balance -= amount;
        logTransaction("Withdrew $" + std::to_string(amount));
    }
}

std::string SavingsAccount::getAccountType()
{
    return "Savings";
}

// CheckingAccount class implementations
CheckingAccount::CheckingAccount(std::string name, int accNumber, float initialBalance, float overdraft)
    : BankAccount(name, accNumber, initialBalance), overdraftLimit(overdraft) {}

void CheckingAccount::deposit(float amount)
{
    balance += amount;
    logTransaction("Deposited $" + std::to_string(amount));
}

void CheckingAccount::withdraw(float amount)
{
    if (amount > (balance + overdraftLimit))
    {
        std::cout << "Overdraft limit exceeded!" << std::endl;
        logTransaction("Failed withdrawal of $" + std::to_string(amount));
    }
    else
    {
        balance -= amount;
        logTransaction("Withdrew $" + std::to_string(amount));
    }
}

std::string CheckingAccount::getAccountType()
{
    return "Checking";
}
