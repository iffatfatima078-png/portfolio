#include <iostream>
#include <string>
using namespace std;

class Admin;   // Forward Declaration

class Customer {
private:
    int id;
    string name;
    double balance;

    static int customerCount;

public:
    Customer(int i, string n, double b) {
        id = i;
        name = n;
        balance = b;
        customerCount++;
    }

    // Customer can only view his own record
    void viewRecord() const {
        cout << "Customer ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }

    // Static function to get total customers
    static int getCustomerCount() {
        return customerCount;
    }

    // Making Admin friend
    friend class Admin;
};

// Initialize static member
int Customer::customerCount = 0;


class Admin {
private:
    string adminName;

public:
    Admin(string n) {
        adminName = n;
    }

    // Admin can view all customer data (including private)
    void viewCustomer(const Customer &c) {
        cout << "Admin Accessing Customer Data" << endl;
        cout << "ID: " << c.id << endl;
        cout << "Name: " << c.name << endl;
        cout << "Balance: " << c.balance << endl;
    }

    // Admin can update customer balance
    void updateBalance(Customer &c, double newBalance) {
        c.balance = newBalance;
        cout << "Balance Updated Successfully!" << endl;
    }

    // Admin can check total registered customers
    void totalCustomers() {
        cout << "Total Registered Customers: "
             << Customer::getCustomerCount() << endl;
    }
};


int main() {

    Admin admin1("System Admin");

    Customer c1(101, "Ali", 5000);
    Customer c2(102, "Sara", 8000);

    // Customer View
    cout << "\n--- Customer View ---\n";
    c1.viewRecord();

    // Admin View
    cout << "\n--- Admin View ---\n";
    admin1.viewCustomer(c1);

    // Admin updating record
    admin1.updateBalance(c1, 10000);

    cout << "\n--- After Update ---\n";
    admin1.viewCustomer(c1);

    // Check total customers
    cout << "\n--- Admin Checking Total Customers ---\n";
    admin1.totalCustomers();

    return 0;
}
