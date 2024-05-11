#include<iostream>
using namespace std;

class Complex
{
    friend Complex SumNumbers(Complex q1, Complex q2);
    int a;
    int b;

    public:
    void setNumber(int n1 , int n2)
    {
        a = n1;
        b = n2;
    }
    void printNumber()
    {
        cout<<"The complex number is : " << a << "+" <<b <<"i" <<endl;
    }
};

Complex SumNumbers(Complex o1, Complex o2)
{
    Complex o3;
    o3.setNumber((o1.a + o2.a) , (o1.b + o2.b));
    return o3;
}

int main()
{
    Complex a1,a2,sum;
    a1.setNumber(2 , 5);
    a1.printNumber();
    a2.setNumber(9 , 0);
    a2.printNumber();
    sum = SumNumbers(a1,a2);
    sum.printNumber();
}