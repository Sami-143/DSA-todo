#include <iostream>
using namespace std;

int last_Occurance(int arr[], int n, int i, int key)
{
    if (i == n)
    {
        return -1;
    }

    int rest_Array = last_Occurance(arr, n, i + 1, key);

    if (rest_Array != -1)
    {
        return rest_Array;
    }

    if (arr[i] == key)
    {
        return i;
    }

    return -1;
}

int main()
{
    int arr[] = {4, 2, 5, 7, 2, 4, 2};
    cout << last_Occurance(arr, 7, 0, 2);
    return 0;
}
