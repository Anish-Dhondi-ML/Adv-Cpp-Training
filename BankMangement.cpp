// 07-06-2023
/*
2. Program for banking management system

Using smart pointers -Create a class Bank with the following member functions,

OpenAccount() – It will take input account number, name and opening balance.
ShowAccount() – It will display the account details such as account number, name and balance.
Deposit() – It will ask for the amount to be added in available balance, and deposit the amount.
Withdrawal() – It will ask for the amount to be withdrawn from the available, will also check the available balance, if balance is available, it will deduct the amount from the available balance.
Search() – It will search for the record and display the account info.
*/ 

#include <iostream>
#include <string>
#include <vector>
#include <memory>

class BankAccount {
private:
    int accountNumber;
    std::string name;
    double balance;

public:
    BankAccount(int accNum, const std::string& accName, double accBalance)
        : accountNumber(accNum), name(accName), balance(accBalance) {}

    void ShowAccount() const {
        std::cout << "Account Number: " << accountNumber << std::endl;
        std::cout << "Account Name: " << name << std::endl;
        std::cout << "Balance: $" << balance << std::endl;
    }

    void Deposit(double amount) {
        balance += amount;
        std::cout << "Deposited $" << amount << " successfully." << std::endl;
    }

    void Withdrawal(double amount) {
        if (balance >= amount) {
            balance -= amount;
            std::cout << "Withdrawn $" << amount << " successfully." << std::endl;
        } else {
            std::cout << "Insufficient balance for withdrawal." << std::endl;
        }
    }

    bool Search(int accNum) const {
        return (accountNumber == accNum);
    }
};

class Bank {
private:
    std::vector<std::shared_ptr<BankAccount>> accounts;

public:
    void OpenAccount() {
        int accNum;
        std::string accName;
        double openingBalance;

        std::cout << "Enter account number: ";
        std::cin >> accNum;
        std::cout << "Enter account name: ";
        std::cin.ignore();
        std::getline(std::cin, accName);
        std::cout << "Enter opening balance: ";
        std::cin >> openingBalance;

        std::shared_ptr<BankAccount> account = std::make_shared<BankAccount>(accNum, accName, openingBalance);
        accounts.push_back(account);
        std::cout << "Account opened successfully." << std::endl;
    }

    void ShowAccount(int accNum) {
        bool found = false;
        for (const auto& account : accounts) {
            if (account->Search(accNum)) {
                account->ShowAccount();
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Account not found." << std::endl;
        }
    }

    void Deposit(int accNum, double amount) {
        bool found = false;
        for (const auto& account : accounts) {
            if (account->Search(accNum)) {
                account->Deposit(amount);
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Account not found." << std::endl;
        }
    }

    void Withdrawal(int accNum, double amount) {
        bool found = false;
        for (const auto& account : accounts) {
            if (account->Search(accNum)) {
                account->Withdrawal(amount);
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Account not found." << std::endl;
        }
    }
};

int main() {
    Bank bank;
    int choice, accNum;
    double amount;

    do {
        std::cout << "1. Open Account" << std::endl;
        std::cout << "2. Show Account" << std::endl;
        std::cout << "3. Deposit" << std::endl;
        std::cout << "4. Withdrawal" << std::endl;
        std::cout << "5. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                bank.OpenAccount();
                break;
            case 2:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                bank.ShowAccount(accNum);
                break;
            case 3:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Enter amount to deposit: ";
                std::cin >> amount;
                bank.Deposit(accNum, amount);
                break;
            case 4:
                std::cout << "Enter account number: ";
                std::cin >> accNum;
                std::cout << "Enter amount to withdraw: ";
                std::cin >> amount;
                bank.Withdrawal(accNum, amount);
                break;
            case 5:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;
    } while (choice != 5);

    return 0;
}
