#include <iostream>
using namespace std;

class Cell
{
public:
    int data;
    Cell *Up;
    Cell *Down;
    Cell *Right;
    Cell *Left;

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
    Cell *current_ptr;
    Cell *head;

public:
    Excel(int numRows, int numCols)
    {
        rows = numRows;
        cols = numCols;
        current_ptr = nullptr;
        head = nullptr;

        InitializeGrid();
    }

    void InitializeGrid()
    {
        head = new Cell(0);
        current_ptr = head;

        for (int i = 0; i < rows; ++i)
        {
            Cell *current_row = current_ptr;
            for (int j = 0; j < cols; ++j)
            {
                if (j < cols - 1)
                {
                    Cell *new_cell = new Cell(0);
                    current_row->Right = new_cell;
                    new_cell->Left = current_row;
                    current_row = new_cell;
                }
            }

            if (i < rows - 1)
            {
                Cell *new_row = new Cell(0);
                current_ptr->Down = new_row;
                new_row->Up = current_ptr;
                current_ptr = new_row;
            }
        }
    }

    friend void DisplayGrid(const Excel &excel);

    void InsertRowAbove()
    {
        if (current_ptr == nullptr || current_ptr->Up == nullptr)
        {
            Cell *new_row = new Cell(3);
            new_row->Down = head;
            head->Up = new_row;
            head = new_row;
            current_ptr = head;
            rows++;
        }
        else
        {
            Cell *new_row = new Cell(3);
            Cell *row_above = current_ptr->Up;

            row_above->Down = new_row;
            new_row->Up = row_above;

            // Update up link of the current row
            new_row->Down = current_ptr;
            current_ptr->Up = new_row;

            current_ptr = new_row;
            rows++;
        }
    }

    void InsertRowBelow()
    {

    }
    void InsertColoumnAtRight()
    {
        if (current_ptr == nullptr)
        {
            return; 
        }

        current_ptr = head;
        while(current_ptr != nullptr)
        {

            
        Cell *new_column = new Cell(1);
        current_ptr->Right->Left = new_column;
        new_column->Right = current_ptr->Right;
        current_ptr->Right = new_column;
        new_column->Left = current_ptr;

        current_ptr = current_ptr->Down;
        }
        current_ptr = head->Right;
        while(current_ptr->Down != nullptr)
        {
            current_ptr->Down = current_ptr->Left->Down->Right;
            current_ptr->Left->Down->Right->Up = current_ptr;

        }
    }
    void InsertColoumnAtLeft()
    {

    }
};

void DisplayGrid(const Excel &excel)
{
    Cell *current_row = excel.head;

    while (current_row != nullptr)
    {
        Cell *current_cell = current_row;

        while (current_cell != nullptr)
        {
            cout << current_cell->data << "-->";
            current_cell = current_cell->Right;
        }
        cout << "NULL"; 
        cout << endl;
        current_row = current_row->Down;
    }
}



int main()
{
    Excel excel(5, 5);
    DisplayGrid(excel);
    cout << "wait the following is the updated grid" << endl;
    cout << "Updated Grid" << endl;
    excel.InsertRowAbove();
    DisplayGrid(excel);
    cout << "wait the following is the updated grid" << endl;
    cout << "Updated Grid" << endl;
    excel.InsertColoumnAtRight();
    DisplayGrid(excel);
    return 0;
}
