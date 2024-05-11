#include<iostream>
using namespace std;

int binarySearch(int arr[],int n,int key)
{
    int s=0;
    int e = n;

    int mid= (s+e)/2;

    while(s<=e)
    {
        if(arr[mid] == key)
        {
            return mid;
        }
        else if (arr[mid] > key)
        {
            e = mid -1;
        }
        else if(arr[mid] < key)
        {
            e = mid + 1;
        }
    }
    return -1;
}

int main()
{
    int n;
    cin>>n;
    int arr[n];

    for(int idx = 0; idx<n; idx++)
    {
        cin>>arr[idx];
    }    

    int key;
    cin>>key;

    cout<<binarySearch(arr,n,key);
}