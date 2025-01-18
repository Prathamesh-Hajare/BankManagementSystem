#include <iostream>
#include "./BankSystem.h"

int main()
{
    BankSystem system;

    int choice;
    std::string username, password;

    do
    {
        std::cout << "1. Login" << std::endl;
        std::cout << "2. Register" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1)
        {
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;

            if (system.authenticate(username, password))
            {
                system.manageAccount(username);
            }
            else
            {
                std::cout << "Invalid credentials!" << std::endl;
            }
        }
        else if (choice == 2)
        {
            std::cout << "Enter username: ";
            std::cin >> username;
            std::cout << "Enter password: ";
            std::cin >> password;
            system.createUser(username, password);
            std::cout << "Account type (Savings/Checking): ";
            std::string accountType;
            std::cin >> accountType;
            system.createAccount(username, accountType);
        }
        else if (choice == 3)
        {
            std::cout << "Exiting system." << std::endl;
        }
        else
        {
            std::cout << "Invalid option!" << std::endl;
        }
    } while (choice != 3);

    return 0;
}
