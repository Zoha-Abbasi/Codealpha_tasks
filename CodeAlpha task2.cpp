#include <iostream>
#include <string>
using namespace std;

const int MAX_USERS = 100;
string usernames[MAX_USERS];
string passwords[MAX_USERS];
int userCount = 0;

bool isUsernameTaken(const string& username) {
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == username) {
            return true;
        }
    }
    return false;
}

void registerUser() {
    string username, password;
    cout << "=== Register ===" << endl;
    cout << "Enter username: ";
    cin >> username;

    if (isUsernameTaken(username)) {
        cout << "Error: Username already taken.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    usernames[userCount] = username;
    passwords[userCount] = password;
    userCount++;

    cout << "Registration successful!\n";
}

void loginUser() {
    string username, password;
    cout << "=== Login ===" << endl;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == username && passwords[i] == password) {
            cout << "Login successful! Welcome, " << username << ".\n";
            return;
        }
    }

    cout << "Invalid username or password.\n";
}

int main() {
    int choice;
    while (true) {
        cout << "\n==== Menu ====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1)
            registerUser();
        else if (choice == 2)
            loginUser();
        else if (choice == 3) {
            cout << "Goodbye!\n";
            break;
        }
        else
            cout << "Invalid choice. Try again.\n";
    }

    return 0;
}
