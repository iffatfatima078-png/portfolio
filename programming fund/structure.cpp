#include <iostream>
using namespace std;

struct Student {
    int roll;
    char name[20];
    int marks[3];
    float avg;
};

int main() {
    Student s[3];
    float totalAvg = 0;

    // Input details
    for(int i = 0; i < 3; i++) {
        cout << "Enter name of student " << i+1 << ": ";
        cin >> s[i].name;

        cout << "Enter roll number: ";
        cin >> s[i].roll;

        int sum = 0;
        cout << "Enter 3 subject marks: ";
        for(int j = 0; j < 3; j++) {
            cin >> s[i].marks[j];
            sum += s[i].marks[j];
        }

        s[i].avg = sum / 3.0;
        totalAvg += s[i].avg;
    }

    // Output
    cout << "\n--- Student Averages ---\n";
    for(int i = 0; i < 3; i++) {
        cout << "Name: " << s[i].name
             << ", Roll: " << s[i].roll
             << ", Average: " << s[i].avg << endl;
    }

    cout << "\nOverall Class Average = " << totalAvg / 3.0 << endl;

    return 0;
}

