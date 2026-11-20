#include<iostream>
#include<string>
using namespace std;

struct Student {
    string name;
    int marks[3]; // 3 subjects
    float percentage;
};

// Function 1: Input lene ke liye
void inputStudent(Student &s) {
    cout << "Enter name: ";
    cin >> s.name;

    int total = 0;
    cout << "Enter marks of 3 subjects:" << endl;
    for(int i = 0; i < 3; i++) {
        cout << "Subject " << i+1 << ": ";
        cin >> s.marks[i];
        total = total + s.marks[i];
    }

    // Formula lagaya
    s.percentage =( (float)total / 300 ) * 100 ; // 3*100 = 300;
}

// Function 2: Display karne ke liye
void displayStudent(Student s) {
    

    cout << "\n===== RESULT =====" << endl;
    cout << "Name: " << s.name << endl;
    cout << "Marks: " << s.marks[0] << ", " << s.marks[1] << ", " << s.marks[2] << endl;
    cout << "Percentage: " << s.percentage << "%" << endl;
}

int main() {
    Student s1; // struct ka 1 variable banaya

    inputStudent(s1); // function call
    displayStudent(s1); // function call

    
    return 0;
}
