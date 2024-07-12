#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct privateinfo {
    string username;
    string password;
    long long balance;
};

void createAccount(privateinfo& l) {
    ofstream file("accounts.txt", ios::app);
    cout << "Enter username: ";
    cin >> l.username;
    cout << "Enter password: ";
    cin >> l.password;
    cout << "Enter initial balance: ";
    cin >> l.balance;
    file << l.username << "," << l.password << "," << l.balance << endl;
    file.close();
    cout << "Account created successfully!" << endl;
}

bool login(privateinfo& l) {
    ifstream file("accounts.txt");
    string line;
    cout << "Enter username: ";
    cin >> l.username;
    cout << "Enter password: ";
    string p;
    cin >> p;
    bool found = false;
    while (getline(file, line)) {
        stringstream ss(line);
        string uname, pstr;
        long long bal;
        getline(ss, uname, ',');
        getline(ss, pstr, ',');
        ss >> bal;
        if (uname == l.username && pstr == p) {
            found = true;
            l.password = p;
            l.balance = bal;
            break;
        }
    }
    file.close();
    return found;
}

void amountDeposit(privateinfo& l, long long amount) {
    l.balance += amount;
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
        if (uname == l.username) {
            file << uname << "," << l.password << "," << l.balance << endl;
        } else {
            file << line << endl;
        }
    }
    temp.close();
    file.close();
    ofstream trans("transactions.txt", ios::app);
    trans << l.username << "," << "Deposit of " << amount << endl;
    trans.close();
    cout << "Deposit successful!" << endl;
}

void amountNeeded(privateinfo& l, long long amount) {
    if (l.balance >= amount) {
        l.balance -= amount;
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
            if (uname == l.username) {
                file << uname << "," << l.password << "," << l.balance << endl;
            } else {
                file << line << endl;
            }
        }
        temp.close();
        file.close();
        ofstream trans("transactions.txt", ios::app);
        trans << l.username << "," << "Withdrawal of " << amount << endl;
        trans.close();
        cout << "Withdrawal successful!" << endl;
    } else {
        cout << "Insufficient balance" << endl;
    }
}

void miniStatement(privateinfo& l) {
    ifstream file("transactions.txt");
    string line;
    cout << "Your mini statement:" << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        string uname, trans;
        getline(ss, uname, ',');
        getline(ss, trans, ',');
        if (uname == l.username) {
            cout << trans << endl;
        }
    }
    cout << "Total balance: " << l.balance << endl;
    file.close();
}

int main() {
    privateinfo l;
    int choice;
    while (true) {
        cout << "1. Create Account" << endl;
        cout << "2. Login" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                createAccount(l);
                break;
            case 2:
                if(!login(l))
                {
                    cout << "Invalid username or password" << endl;
                }
                else
                {while(true) {
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
                                amountDeposit(l, amount);
                                break;
                            }
                            case 2: {
                                long long amount;
                                cout << "Enter amount to withdraw: ";
                                cin >> amount;
                                amountNeeded(l, amount);
                                break;
                            }
                            case 3:
                                miniStatement(l);
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
