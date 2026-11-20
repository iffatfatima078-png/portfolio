#include <iostream>
using namespace std;

struct Student {
    char name[30];
    int roll;
    int marks[3];
    float avg;
};

int main() {
    Student s[3];
    float totalAvg = 0;

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

    // ---- OUTPUT TABLE ----
    cout << "\nName\tRoll\tMarks\t\tAverage\n";
    cout << "---------------------------------------------\n";

    for(int i = 0; i < 3; i++) {
        cout << s[i].name << "\t"
             << s[i].roll << "\t"
             << s[i].marks[0] << "," << s[i].marks[1] << "," << s[i].marks[2] << "\t"
             << s[i].avg << endl;
    }

    cout << "\nOverall Class Average = " << totalAvg / 3.0 << endl;

    return 0;
}

