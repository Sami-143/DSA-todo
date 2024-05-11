#include <iostream>
#include <fstream>
#include <string>
#include <ctime> // Add this for time function
using namespace std;

template <typename T>
class AutoGrowingArray
{
private:
    int size;
    int capacity;
    T* arr;

public:
    AutoGrowingArray()
    {
        size = 0;
        capacity = 1;
        arr = new T[capacity];
    }

    void push_back(T value)
    {
        if (size == capacity)
        {
            capacity++;
            T* temp = new T[capacity];
            for (int i = 0; i < size; i++)
            {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
        }

        arr[size] = value;
        size++;
    }

    void CreateRandomfile(string fn, int size, int RN = 100)
    {
        srand(time(0));
        ofstream Writer(fn);
        for (int i = 0; i < size * 1024 * 1024; i++)
        {
            Writer << rand() % RN << " ";
        }
    }
};

string parse_record(string record, int field)
{
    int comma_count = 1;
    string item;
    for (int idx = 0; idx < record.length(); idx++)
    {
        if (record[idx] == ',')
        {
            comma_count = comma_count + 1;
        }
        else if (comma_count == field)
        {
            item = item + record[idx];
        }
    }
    return item;
}

// Declare load_data before main
void load_data(AutoGrowingArray<int>& obj);

int main()
{
    AutoGrowingArray<int> a;
    cout << "BEFORE: " << time(0) << endl;
    load_data(a);

    string path = "C:\\Users\\AL-FATAH LAPTOP\\OneDrive\\Desktop\\Output.txt";
    a.CreateRandomfile(path, 2);
    cout << "AFTER: " << time(0) << endl;
}

void load_data(AutoGrowingArray<int>& obj)
{
    string record;
    int idx = 0;
    ifstream recordfile;
    recordfile.open("Output.txt", ios::in);
    while (getline(recordfile, record))
    {
        int g = stoi(parse_record(record, 1));
        obj.push_back(g);
    }
    recordfile.close();
}
