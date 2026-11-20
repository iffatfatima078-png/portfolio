#include <iostream>
using namespace std;
class Employee {
public:
    
    virtual float calculateSalary() = 0;

    
    virtual ~Employee() {}
};


class FullTimeEmployee : public Employee {
private:
    float monthlySalary;

public:
    FullTimeEmployee(float salary) {
        monthlySalary = salary;
    }

    float calculateSalary() override {
        return monthlySalary;
    }
};


class PartTimeEmployee : public Employee {
private:
    float hourlyRate;
    int hoursWorked;

public:
    PartTimeEmployee(float rate, int hours) {
        hourlyRate = rate;
        hoursWorked = hours;
    }

    float calculateSalary() override {
        return hourlyRate * hoursWorked;
    }
};

int main() {
    // Creating objects
    FullTimeEmployee fullEmp(60000);     // Monthly salary
    PartTimeEmployee partEmp(500, 20);   // 500 per hour, 20 hours

    // Base class pointers (Polymorphism)
    Employee* emp1 = &fullEmp;
    Employee* emp2 = &partEmp;

    // Output
    cout << "Full-Time Employee Salary: " << emp1->calculateSalary() << endl;
    cout << "Part-Time Employee Salary: " << emp2->calculateSalary() << endl;

    return 0;
}
