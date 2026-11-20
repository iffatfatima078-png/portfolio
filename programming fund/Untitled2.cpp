#include <iostream>
#include <string>
using namespace std;

void replaceAll(string &sent, string &oldWord, string &newWord)
{
    int pos = 0;

    // Find the substring and replace it repeatedly
    while ((pos = sent.find(oldWord, pos)) != -1)
    {
        sent.replace(pos, oldWord.length(), newWord);
        pos += newWord.length(); // move forward
    }
}

int main()
{
    string sentence;

    cout << "Enter a sentence: ";
    getline(cin, sentence);

    string oldWord, newWord;

    cout << "Enter word to replace: ";
    cin >> oldWord;

    cout << "Enter new word: ";
    cin >> newWord;

    replaceAll(sentence, oldWord, newWord); // Arguments passed by reference

    cout << "Updated sentence: " << sentence << endl;

    return 0;
}
