#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

class Account {
protected:
    string username;
    string password;

public:
    void setUsername(string uname) {
        username = uname;
    }

    void setPassword(string p) {
        password = p;
    }

    string getUsername() {
        return username;
    }

    string getPassword() {
        return password;
    }
};

class BankAccount : public Account {
private:
    long long balance;

public:
    BankAccount() : balance(0) {}

    void createAccount() {
        ofstream file("accounts.txt", ios::app);
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter initial balance: ";
        cin >> balance;
        file << username << "," << password << "," << balance << endl;
        file.close();
        cout << "Account created successfully!" << endl;
    }

    bool login() {
        ifstream file("accounts.txt");
        string line;
        cout << "Enter username: ";
        string uname;
        cin >> uname;
        cout << "Enter password: ";
        string p;
        cin >> p;
        bool found = false;
        while (getline(file, line)) {
            stringstream ss(line);
            string unameFile, pstr;
            long long bal;
            getline(ss, unameFile, ',');
            getline(ss, pstr, ',');
            ss >> bal;
            if (unameFile == uname && pstr == p) {
                found = true;
                username = uname;
                password = p;
                balance = bal;
                break;
            }
        }
        file.close();
        return found;
    }

    void deposit(long long amount) {
        balance += amount;
        ofstream file("accounts.txt", ios::out | ios::trunc);
        ifstream temp("accounts.txt");
        string line;
        while (getline(temp, line)) {
            stringstream ss(line);
            string uname, pstr;
            long long p;
            getline(ss, uname, ',');
            getline(ss, pstr, ',');
            p = stol(pstr);
            long long bal;
            ss >> bal;
            if (uname == username) {
                file << uname << "," << password << "," << balance << endl;
            } else {
                file << line << endl;
            }
        }
        temp.close();
        file.close();
        ofstream trans("transactions.txt", ios::app);
        trans << username << "," << "Deposit of " << amount << endl;
        trans.close();
        cout << "Deposit successful!" << endl;
    }

    void withdraw(long long amount) {
        if (balance >= amount) {
            balance -= amount;
            ofstream file("accounts.txt", ios::out | ios::trunc);
            ifstream temp("accounts.txt");
            string line;
            while (getline(temp, line)) {
                stringstream ss(line);
                string uname, pstr;
                long long p;
                getline(ss, uname, ',');
                getline(ss, pstr, ',');
                p = stol(pstr);
                long long bal;
                ss >> bal;
                if (uname == username) {
                    file << uname << "," << password << "," << balance << endl;
                } else {
                    file << line << endl;
                }
            }
            temp.close();
            file.close();
            ofstream trans("transactions.txt", ios::app);
            trans << username << "," << "Withdrawal of " << amount << endl;
            trans.close();
            cout << "Withdrawal successful!" << endl;
        } else {
            cout << "Insufficient balance" << endl;
        }
    }

    void miniStatement() {
        ifstream file("transactions.txt");
        string line;
        cout << "Your mini statement:" << endl;
        while (getline(file, line)) {
            stringstream ss(line);
            string uname, trans;
            getline(ss, uname, ',');
            getline(ss, trans, ',');
            if (uname == username) {
                cout << trans << endl;
            }
        }
        cout << "Total balance: " << balance << endl;
        file.close();
    }
};

int main() {
    BankAccount account;
    int choice;
    while (true) {
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                account.createAccount();
                break;
            case 2:
                if (!account.login()) {
                    cout << "Invalid username or password" << endl;
                } else {
                    while (true) {
                        cout << "1. Deposit" << endl;
                        cout << "2. Withdrawal" << endl;
                       cout << "3. Mini Statement" << endl;
                        cout << "4. Logout" << endl;
                        cout << "Enter your choice: ";
                        int choice2;
                        cin >> choice2;
                        switch (choice2) {
                            case 1: {
                                long long amount;
                                cout << "Enter amount to deposit: ";
                                cin >> amount;
                                account.deposit(amount);
                                break;
                            }
                            case 2: {
                                long long amount;
                                cout << "Enter amount to withdraw: ";
                                cin >> amount;
                                account.withdraw(amount);
                                break;
                            }
                            case 3:
                                account.miniStatement();
                                break;
                            case 4:
                                cout << "Logged out successfully!" << endl;
                                break;
                            default:
                                cout << "Invalid choice" << endl;
                        }
                        if (choice2 == 4) {
                            break;
                        }
                    }
                }
                break;
            case 3:
                cout << "Exiting..." << endl;
                return 0;
            default:
                cout << "Invalid choice" << endl;
        }
    }
    return 0;
}