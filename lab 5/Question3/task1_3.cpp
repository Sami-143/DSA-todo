#include <iostream>
using namespace std;

int first_Occurance(int arr[], int n, int i, int key)
{

    if (i == n)
    {
        return -1;
    }
    if(arr[i] == key)
    {
        return i;
    }

    return first_Occurance(arr,n,i+1,key);
}


int main()
{
    int arr[] = {4,2,5,7,2,4,2};
    cout<<first_Occurance(arr,7,0,2);
    return 0;
}