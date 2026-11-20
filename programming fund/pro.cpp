#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

/* -----------------------------------------
   ONLINE EXAMINATION SYSTEM (C++)
   WITH STUDENT / ADMIN LOGIN
   FIRST SEMESTER FRIENDLY
   ----------------------------------------- */

#define MAX_QUESTIONS 5
#define EXAM_TIME 60

struct User
{
    string username;
    string password;
    string role; // student or admin
};

struct Question
{
    string question;
    string options[4];
    int correct;
};

struct Result
{
    string username;
    int score;
    float percentage;
    char grade;
};

void menu();
void adminMenu();
bool login(User &u);
void registerUser();
void startExam(string user);
void loadQuestions(Question q[]);
char calculateGrade(float p);
void saveResult(Result r);
void showResults();

int main()
{
    int choice;
    User u;

    while (true)
    {
        menu();
        cin >> choice;

        switch (choice)
        {
        case 1:
            if (login(u))
            {
                if (u.role == "student")
                {
                    startExam(u.username);
                }
                else if (u.role == "admin")
                {
                    adminMenu();
                }
            }
            else
            {
                cout << "Login failed!" << endl;
            }
            break;

        case 2:
            registerUser();
            break;

        case 3:
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Invalid choice!" << endl;
        }
    }
}

void menu()
{
    cout << "\n==== ONLINE EXAM SYSTEM ====" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice: ";
}

bool login(User &u)
{
    ifstream fin("users.txt");
    string uname, pass;

    if (!fin)
    {
        cout << "No users found." << endl;
        return false;
    }

    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;

    while (fin >> u.username >> u.password >> u.role)
    {
        if (u.username == uname && u.password == pass)
        {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

void registerUser()
{
    ofstream fout("users.txt", ios::app);
    User u;

    cout << "New Username: ";
    cin >> u.username;
    cout << "New Password: ";
    cin >> u.password;
    cout << "Role (student/admin): ";
    cin >> u.role;

    fout << u.username << " " << u.password << " " << u.role << endl;
    fout.close();

    cout << "Registration successful!" << endl;
}

void adminMenu()
{
    int ch;
    cout << "\n==== ADMIN MENU ====" << endl;
    cout << "1. View All Results" << endl;
    cout << "2. Logout" << endl;
    cout << "Enter choice: ";
    cin >> ch;

    if (ch == 1)
        showResults();
}

void startExam(string user)
{
    Question q[MAX_QUESTIONS];
    loadQuestions(q);

    int score = 0;
    int ans;
    time_t start = time(0);

    cout << "Exam started!" << endl;

    for (int i = 0; i < MAX_QUESTIONS; i++)
    {
        if (difftime(time(0), start) > EXAM_TIME)
            break;

        cout << "\nQ" << i + 1 << ": " << q[i].question << endl;
        for (int j = 0; j < 4; j++)
            cout << j + 1 << ". " << q[i].options[j] << endl;

        cout << "Answer: ";
        cin >> ans;

        if (ans == q[i].correct)
            score++;
    }

    Result r;
    r.username = user;
    r.score = score;
    r.percentage = (score * 100.0) / MAX_QUESTIONS;
    r.grade = calculateGrade(r.percentage);

    cout << "Score: " << r.score << endl;
    cout << "Percentage: " << r.percentage << "%" << endl;
    cout << "Grade: " << r.grade << endl;

    saveResult(r);
}

void loadQuestions(Question q[])
{
    q[0] = {"C++ is a ____ language", {"Procedural", "Object Oriented", "Assembly", "Markup"}, 2};
    q[1] = {"Which symbol ends statement?", {":", ";", ",", "."}, 2};
    q[2] = {"Which header is for file handling?", {"iostream", "fstream", "string", "cmath"}, 2};
    q[3] = {"Which loop runs at least once?", {"for", "while", "do-while", "none"}, 3};
    q[4] = {"Which keyword creates object?", {"class", "struct", "object", "new"}, 4};
}

char calculateGrade(float p)
{
    if (p >= 80) return 'A';
    else if (p >= 60) return 'B';
    else if (p >= 40) return 'C';
    else return 'F';
}

void saveResult(Result r)
{
    ofstream fout("results.txt", ios::app);
    fout << r.username << " " << r.score << " " << r.percentage << " " << r.grade << endl;
    fout.close();
}

void showResults()
{
    ifstream fin("results.txt");
    Result r;
    cout << "\nUSERNAME SCORE PERCENT GRADE" << endl;
    while (fin >> r.username >> r.score >> r.percentage >> r.grade)
        cout << r.username << " " << r.score << " " << r.percentage << " " << r.grade << endl;
    fin.close();
    
    
}

