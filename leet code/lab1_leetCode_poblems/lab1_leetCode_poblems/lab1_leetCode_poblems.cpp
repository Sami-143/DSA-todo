#include <iostream>
#include <fstream>   // For ofstream
//#include <cstdlib>   // For srand and rand
#include <ctime>     // For time

void CreateRandomFile(std::string fn, int Size, int RN = 100) {
    srand(time(0));
    std::ofstream Writer(fn);
    for (int i = 0; i < Size * 1024 * 1024; i++) {
        Writer << rand() % RN << " ";
    }
    Writer.close();  // Close the file when done
    //std::cout  << time(0) << std::endl;
}

template <typename T>
class Vector {
private:
    T* array;         // Pointer to the dynamically allocated array
    int size;         // Current size of the vector
    int capacity;     // Current capacity of the vector

public:
    // Constructor
    Vector() {
        size = 0;
        capacity = 2;
        array = new T[capacity];
    }

    // Operator overloading for indexing (read-only)
    T operator [](int index) const {
        return array[index];
    }

    // Operator overloading for indexing (read-write)
    T& operator [](int index) {
        return array[index];
    }

    // Friend function to overload the << operator for output
    friend std::ostream& operator << (std::ostream& out, const Vector& other) {
        for (int i = 0; i < other.size; ++i) {
            out << other.array[i] << " ";
        }
        return out;
    }

    // Function to push a value to the back of the vector
    void PushBack(T value) {
        if (size == capacity) {
            // If the vector is full, double its capacity
            capacity ++;
            T* newArray = new T[capacity];
            for (int i = 0; i < size; ++i) {
                newArray[i] = array[i];
            }
            delete[] array;
            array = newArray;
        }
        array[size++] = value;
    }

    // Function to load data from a file into the vector
    void LoadData(std::string filename, Vector<T> &grow) {
        std::ifstream file(filename);
        T number;
        while (file >> number)
        {
            grow.PushBack(number);
        }
        file.close();

    }
};

int main() {

    // Create a random data file
    CreateRandomFile("random.txt", 1); // Example usage
    std::cout << "Before Time : " << time(0) << std::endl;
    // Create a Vector of integers
    Vector<int> myVector;
    // Load data from the file
    myVector.LoadData("random.txt", myVector);
    std::cout << "After Time : " << time(0) << std::endl;


    // Push some values to the back of the Vector
    myVector.PushBack(1);
    myVector.PushBack(2);
    myVector.PushBack(3);

    

    

    //// Print the loaded data
    //std::cout << myVector << std::endl;

    //// Output the current time
    //std::cout << time(0) << std::endl;

    return 0;
}

