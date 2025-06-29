#include <iostream>
#include <string>
using namespace std;

const int MAX_CUSTOMERS = 100;
const int MAX_TRANSACTIONS = 100;

class Transaction {
public:
    string type;
    double amount;

    Transaction() {
        type = "";
        amount = 0;
    }

    Transaction(string t, double a) {
        type = t;
        amount = a;
    }
};

class Account {
private:
    string accountNumber;
    double balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;

public:
    Account(string accNum) {
        accountNumber = accNum;
        balance = 0;
        transactionCount = 0;
    }

    string getAccountNumber() {
        return accountNumber;
    }

    double getBalance() {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions[transactionCount++] = Transaction("Deposit", amount);
        cout << "Deposit successful!\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        transactions[transactionCount++] = Transaction("Withdraw", amount);
        cout << "Withdrawal successful!\n";
        return true;
    }

    void addTransaction(string type, double amount) {
        transactions[transactionCount++] = Transaction(type, amount);
    }

    void showTransactions() {
        cout << "Transaction History:\n";
        for (int i = 0; i < transactionCount; i++) {
            cout << transactions[i].type << " of Rs. " << transactions[i].amount << endl;
        }
    }

    void showInfo() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: Rs. " << balance << endl;
        showTransactions();
    }
};

class Customer {
private:
    string name;
    Account* account;

public:
    Customer() {
        name = "";
        account = nullptr;
    }

    Customer(string customerName, string accNumber) {
        name = customerName;
        account = new Account(accNumber);
    }

    ~Customer() {
        delete account;
    }

    Account* getAccount() {
        return account;
    }

    string getName() {
        return name;
    }

    void showDetails() {
        cout << "\nCustomer: " << name << endl;
        account->showInfo();
    }
};

Customer* customers[MAX_CUSTOMERS];
int customerCount = 0;

Customer* findCustomer(string accNum) {
    for (int i = 0; i < customerCount; i++) {
        if (customers[i]->getAccount()->getAccountNumber() == accNum) {
            return customers[i];
        }
    }
    return nullptr;
}

int main() {
    int choice;

    while (true) {
        cout << "\n===== Banking System Menu =====\n";
        cout << "1. Create Customer\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer Funds\n";
        cout << "5. Show Account Info\n";
        cout << "6. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        if (choice == 1) {
            string name, accNum;
            cout << "Enter customer name: ";
            cin >> name;
            cout << "Enter new account number: ";
            cin >> accNum;

            if (findCustomer(accNum)) {
                cout << "Account number already exists!\n";
                continue;
            }

            customers[customerCount++] = new Customer(name, accNum);
            cout << "Customer and account created!\n";
        }

        else if (choice == 2) {
            string accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;

            Customer* cust = findCustomer(accNum);
            if (!cust) {
                cout << "Account not found!\n";
                continue;
            }

            cout << "Enter deposit amount: ";
            cin >> amount;
            cust->getAccount()->deposit(amount);
        }

        else if (choice == 3) {
            string accNum;
            double amount;
            cout << "Enter account number: ";
            cin >> accNum;

            Customer* cust = findCustomer(accNum);
            if (!cust) {
                cout << "Account not found!\n";
                continue;
            }

            cout << "Enter withdrawal amount: ";
            cin >> amount;
            cust->getAccount()->withdraw(amount);
        }

        else if (choice == 4) {
            string fromAcc, toAcc;
            double amount;
            cout << "Enter sender account number: ";
            cin >> fromAcc;
            cout << "Enter receiver account number: ";
            cin >> toAcc;

            Customer* sender = findCustomer(fromAcc);
            Customer* receiver = findCustomer(toAcc);

            if (!sender || !receiver) {
                cout << "One or both accounts not found!\n";
                continue;
            }

            cout << "Enter amount to transfer: ";
            cin >> amount;

            if (sender->getAccount()->withdraw(amount)) {
                receiver->getAccount()->deposit(amount);
                sender->getAccount()->addTransaction("Transfer to " + toAcc, amount);
                receiver->getAccount()->addTransaction("Received from " + fromAcc, amount);
                cout << "Transfer successful!\n";
            }
        }

        else if (choice == 5) {
            string accNum;
            cout << "Enter account number: ";
            cin >> accNum;

            Customer* cust = findCustomer(accNum);
            if (!cust) {
                cout << "Account not found!\n";
                continue;
            }

            cust->showDetails();
        }

        else if (choice == 6) {
            cout << "Thank you for using the banking system.\n";
            break;
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }


    for (int i = 0; i < customerCount; i++) {
        delete customers[i];
    }

    return 0;
}
