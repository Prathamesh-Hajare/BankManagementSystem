#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <iostream>
#include <string>
#include <vector>

class BankAccount
{
protected:
    std::string accountHolder;
    int accountNumber;
    float balance;
    std::vector<std::string> transactionHistory;

public:
    BankAccount(std::string name, int accNumber, float initialBalance);
    virtual void deposit(float amount) = 0;
    virtual void withdraw(float amount) = 0;
    void displayDetails();
    void showTransactionHistory();
    void logTransaction(const std::string &message);
    float getBalance() const;
    virtual std::string getAccountType() = 0;
    int getAccountNumber() const { return accountNumber; }
    virtual void saveToFile();
};

// Derived classes
class SavingsAccount : public BankAccount
{
    float interestRate;

public:
    SavingsAccount(std::string name, int accNumber, float initialBalance, float rate);
    void deposit(float amount) override;
    void withdraw(float amount) override;
    std::string getAccountType() override;
};

class CheckingAccount : public BankAccount
{
    float overdraftLimit;

public:
    CheckingAccount(std::string name, int accNumber, float initialBalance, float overdraft);
    void deposit(float amount) override;
    void withdraw(float amount) override;
    std::string getAccountType() override;
};

#endif
