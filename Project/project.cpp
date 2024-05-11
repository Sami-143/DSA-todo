#include <iostream>
#include <vector>
using namespace std;

class Cell
{
public:
    int data;
    Cell* Up;
    Cell* Down;
    Cell* Right;
    Cell* Left;

    Cell(int val)
    {
        data = val;
        Up = nullptr;
        Down = nullptr;
        Left = nullptr;
        Right = nullptr;
    }
};

class Excel
{
private:
    int rows;
    int cols;
    Cell* current_ptr;
    vector<vector<Cell*>> gridContainer;

public:
    Excel(int numRows, int numCols)
    {
        rows = numRows;
        cols = numCols;
        current_ptr = nullptr;
        initialize_Grid(numRows, numCols);
    }

    void initialize_Grid(int rows, int cols)
    {
        //initaize the grid with empty 
        for (int i = 0; i < rows; i++)
        {
            vector<Cell*> grid;
            for (int j = 0; j < cols; j++)
            {
                grid.push_back(nullptr);
            }
            gridContainer.push_back(grid);
        }
        for (int i = 0; i < rows; i++)
        {
            
            for (int j = 0; j < cols; j++)
            {
                Cell* cell = new Cell(0); // Assign unique values.
                gridContainer[i][j]= cell;

                if (i > 0)
                {
                    cell->Up = gridContainer[i - 1][j];
                    gridContainer[i - 1][j]->Down = cell;
                }
                if (j > 0)
                {
                    cell->Left = gridContainer[i][j - 1];
                    gridContainer[i][j - 1]->Right = cell;
                }
            }
          
        }
    }
    void insertRowAtAbove()
    {
        
    }

    void display()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                cout << gridContainer[i][j]->data << "-->";
            }
            cout << "NULL" << endl;
        }
    }
};

int main()
{
    Excel excel(5, 5);
    excel.display();

    return 0;
}
