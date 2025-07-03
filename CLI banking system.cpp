#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

class User {
protected:
    string username, password;
    float balance;
public:
    User() : balance(0.0) {}
    virtual void menu() = 0;
    string getUsername() { return username; }
    bool login(string u, string p) {
        return (u == username && p == password);
    }
};

class Customer : public User {
    float fdAmount;
    float loanAmount;
public:
    Customer(string u, string p) {
        username = u;
        password = p;
        balance = 0.0;
        fdAmount = 0.0;
        loanAmount = 0.0;
    }

    void menu() override {
        int choice;
        do {
            cout << "\n[Customer] " << username << "'s Menu\n";
            cout << "1. Check Balance\n2. Deposit\n3. Withdraw\n4. Fixed Deposit\n5. Apply Loan\n6. Logout\nChoice: ";
            cin >> choice;
            switch (choice) {
                case 1: cout << "Current Balance: Rs." << balance << endl; break;
                case 2: {
                    float amt; cout << "Deposit Amount: Rs."; cin >> amt;
                    balance += amt; cout << "Deposited Successfully.\n"; break;
                }
                case 3: {
                    float amt; cout << "Withdraw Amount: Rs."; cin >> amt;
                    if (amt <= balance) { balance -= amt; cout << "Withdrawn.\n"; }
                    else cout << "Insufficient balance.\n";
                    break;
                }
                case 4: {
                    float amt; cout << "FD Amount: Rs."; cin >> amt;
                    if (amt <= balance) {
                        fdAmount += amt;
                        balance -= amt;
                        cout << "FD of Rs." << amt << " created.\n";
                    } else cout << "Insufficient balance.\n";
                    break;
                }
                case 5: {
                    float amt; cout << "Loan Amount: Rs."; cin >> amt;
                    loanAmount += amt;
                    cout << "Loan Request Submitted.\n";
                    break;
                }
                case 6: cout << "Logging out...\n"; break;
                default: cout << "Invalid!\n";
            }
        } while (choice != 6);
    }
};

class Admin : public User {
public:
    Admin() {
        username = "admin";
        password = "admin123";
    }

    void menu() override {
        cout << "\n[Admin] Welcome, Admin!\n";
        cout << "(In full version: View all users, Approve loans, etc.)\n";
    }
};

class BankSystem {
    vector<Customer> customers;
    Admin admin;

    void saveToFile() {
        ofstream fout("users.txt");
        for (auto &c : customers) {
            fout << c.getUsername() << endl;
        }
        fout.close();
    }

public:
    void run() {
        int choice;
        do {
            cout << "\n--- Welcome to CLI Bank ---\n";
            cout << "1. Register\n2. Login as Customer\n3. Login as Admin\n4. Exit\nChoice: ";
            cin >> choice;
            if (choice == 1) {
                string u, p;
                cout << "Choose Username: "; cin >> u;
                cout << "Choose Password: "; cin >> p;
                customers.push_back(Customer(u, p));
                cout << "Registration Successful!\n";
                saveToFile();
            } else if (choice == 2) {
                string u, p;
                cout << "Username: "; cin >> u;
                cout << "Password: "; cin >> p;
                bool found = false;
                for (auto &c : customers) {
                    if (c.login(u, p)) {
                        c.menu();
                        found = true;
                        break;
                    }
                }
                if (!found) cout << "Login Failed.\n";
            } else if (choice == 3) {
                string u, p;
                cout << "Admin Username: "; cin >> u;
                cout << "Admin Password: "; cin >> p;
                if (admin.login(u, p)) admin.menu();
                else cout << "Invalid Admin Credentials.\n";
            }
        } while (choice != 4);
        cout << "Thank you for using CLI Bank.\n";
    }
};

int main() {
    BankSystem bank;
    bank.run();
    return 0;
}
