#include <iostream>
using namespace std;

class Book
{
private:
    int pages;
    int chapters;
    int references;

public:
    // Default Constructor
    Book()
    {
        pages = 50;
        chapters = 5;
        references = 0;
    }

    // Method to get data with validation
    void getData()
    {
        cout << "Enter number of pages: ";
        cin >> pages;

        if (pages < 1)
            pages = 1;

        cout << "Enter number of chapters: ";
        cin >> chapters;

        if (chapters < 1)
            chapters = 1;

        cout << "Enter number of references: ";
        cin >> references;

        if (references < 0)
            references = 0;
    }

    // Display method
    void display()
    {
        cout << "Pages: " << pages << endl;
        cout << "Chapters: " << chapters << endl;
        cout << "References: " << references << endl;
    }

};

int main()
{
    Book b;

    b.getData();
    b.display();

    return 0;
}


