#include<iostream>
using namespace std;

class Count
{
    private:
        int n;
        int n1;
    public:
    Count()
    {
         n  = 1;
         n1  = 0;
    }
void Show()
{
    cout << "The value of N ids: "  << n << " value of N1 is "<< n1 ;
}

void operator --()
{
    n = n - 1;
    n1 = n1 -1;
}

};
int main()
{
    Count a;
    a.Show();
    --a;
    a.Show();
}