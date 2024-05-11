#include<iostream>
#include<vector>
using namespace std;


void insertionSort(vector<int> arr)
{
    for (size_t i = 1; i < arr.size(); i++)
    {
        int current = arr[i];
        int j = i-1;

        while (arr[j]> current)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = current;
        
    }
    
}

int main()
{
    int n = 0;
    cout << "Enter number: ";
    cin >> n;

    int arr[n]={};

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int smallest = 0;
    int temp = 0;
    for(int i =0;i<n;i++)
    {
        smallest = arr[i];
        for(int j = i+1; j<n;j++)
        {
            if(smallest>arr[j])
            {
                temp = smallest;
                smallest = arr[j];
                arr[j] =temp; 
            }
        }
        arr[i] = smallest;
        smallest = arr[i];
    }


    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
}