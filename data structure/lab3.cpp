#include <iostream>
using namespace std;

void search(int[], int, int);

int main()
{
    cout << "HELLOOOOOO";

    const int SIZE = 11;

    int arr[SIZE] = {2, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21};

    int k = 5;

    search(arr, SIZE, k);

    return 0;
}


void search(int arr[], int n, int k)
{
    int low = 0;
    int high = n - 1;
    int mid = (low + high) / 2;

    cout << "\nValues in the array are:";

    for (int z = 0; z < n; z++)
    {
        cout << "\n" << arr[z];
    }

    cout << "\n\nSearching " << k << " in the array..";

    do
    {
        if (arr[mid] == k)
        {
            cout << "\nValue found!";
            break;
        }
        else if (k < arr[mid])
        {
            high = mid - 1;
            mid = (low + high) / 2;
        }
        else if (k > arr[mid])
        {
            low = mid + 1;
            mid = (low + high) / 2;
        }
    }
    while (low <= high);
}
