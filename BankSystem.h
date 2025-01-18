#ifndef BANKSYSTEM_H
#define BANKSYSTEM_H

#include <map>
#include <vector>
#include <string>
#include "./BankAccount.h"

class BankSystem
{
    std::map<std::string, std::string> users; // Username-Password pairs
    std::map<std::string, std::vector<BankAccount *>> userAccounts;

public:
    BankSystem();
    void loadUsers();
    void saveUsers();
    bool authenticate(std::string username, std::string password);
    void createUser(std::string username, std::string password);
    void createAccount(std::string username, std::string accountType);
    BankAccount *selectAccount(std::string username);
    void manageAccount(std::string username);
};

#endif
