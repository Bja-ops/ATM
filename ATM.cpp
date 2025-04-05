#include <iostream>
#include <unordered_map>
#include <fstream>
using namespace std;

struct User {
    string email;
    string password;
};

unordered_map<string, User> users;
string loggedInEmail = "";

void loadUsersFromFile() {
    ifstream file("users.txt");
    string email, password;
    while (file >> email >> password) {
        users[email] = {email, password};
    }
    file.close();
}

void saveUserToFile(const string& email, const string& password) {
    ofstream file("users.txt", ios::app);
    file << email << " " << password << endl;
    file.close();
}

void createAccount() {
    string email, password;
    cout << "Give email: ";
    cin >> email;
    if (users.find(email) != users.end()) {
        cout << "User exists!" << endl;
        return;
    }
    cout << "Give password: ";
    cin >> password;
    users[email] = {email, password};
    saveUserToFile(email, password);
    cout << "User created!" << endl;
}

bool loginToAccount() {
    string email, password;
    cout << "Give email: ";
    cin >> email;
    auto it = users.find(email);
    if (it == users.end()) 
    {
        cout << "No user with this email found!" << endl;
        return false;
    }
    cout << "Give password: ";
    cin >> password;
    if (it->second.password == password) 
    {
        cout << "Login success!" << endl;
        loggedInEmail = email;
        return true;
    } 
    else 
    {
        cout << "Bad password!" << endl;
        return false;
    }
}

void cashMachine() {
    int money = 3000;
    cout << "Cash machine value: " << money << endl;

    string command;
    cout << "What you want to do? (login/register): ";
    cin >> command;

    if (command == "Register" || command == "register") 
    {
        createAccount();
    } 
    else if (command == "Login" || command == "login") 
    {
        if (!loginToAccount()) return;
    } 
    else 
    {
        cout << "Invalid option!" << endl;
        return;
    }

    string operation;
    cout << "What you want to do? (Withdraw/deposit): ";
    cin >> operation;

    if (operation == "Withdraw" || operation == "withdraw") 
    {
        cout << "How much you want to withdraw? ";
        int withdraw;
        cin >> withdraw;
        if (withdraw > money) 
        {
            cout << "Cash machine doesn't have enough money, sorry." << endl;
        } else 
        {
            money -= withdraw;
            cout << "Withdraw successful. Cash machine value: " << money << endl;
        }
    } 

    else if (operation == "Deposit" || operation == "deposit") 
    {
        cout << "How much you want to deposit? ";
        int deposit;
        cin >> deposit;
        money += deposit;
        cout << "Deposit successful. Cash machine value: " << money << endl;
    } 
    else 
    {
        cout << "Invalid operation!" << endl;
    }
}

int main() {
    loadUsersFromFile();
    cashMachine();
    return 0;
}
