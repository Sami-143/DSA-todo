#include <iostream>
#include <vector>
#include <windows.h>
#include<math.h>
using namespace std;

class Cell
{
public:
    int data;
    Cell *Up;
    Cell *Down;
    Cell *Right;
    Cell *Left;
    string color;

    Cell()
    {
        data = 1;
        Up = nullptr;
        Down = nullptr;
        Left = nullptr;
        Right = nullptr;
        color = "\33[37m";
    }

    Cell(int val)
    {
        data = val;
        Up = nullptr;
        Down = nullptr;
        Left = nullptr;
        Right = nullptr;
    }
};

class Spreadsheet
{
public:
    int totalRows;
    int totalColumns;
    Cell *currentHead;
    Cell *gridHead;
    Cell *selectedCell;
    Cell *startCell;
    Cell *endCell;

    Spreadsheet(int numRows, int numCols)
    {
        totalRows = numRows;
        totalColumns = numCols;
        startCell = nullptr;
        endCell = nullptr;
        gridHead = new Cell();
        selectedCell = gridHead;

        InitializeGrid();
    }

    void InitializeGrid()
    {

        Cell *curr_Ptr = gridHead;
        for (int j = 1; j < totalColumns; j++)
        {
            Cell *new_Cell = new Cell();
            curr_Ptr->Right = new_Cell;
            new_Cell->Left = curr_Ptr;
            curr_Ptr = curr_Ptr->Right;
        }

        curr_Ptr = gridHead;
        for (int i = 1; i < totalRows; i++)
        {
            Cell *new_Row = new Cell();
            curr_Ptr->Down = new_Row;
            new_Row->Up = curr_Ptr;

            curr_Ptr = curr_Ptr->Down;
        }

        curr_Ptr = gridHead;
        Cell *prev = gridHead;
        Cell *curr = gridHead->Right;

        for (int i = 1; i < totalColumns; i++)
        {
            Cell *pre_row_ptr = prev->Down;
            Cell *curr_row_ptr = curr;
            for (int j = 1; j < totalRows; j++)
            {
                Cell *new_Cell = new Cell();
                pre_row_ptr->Right = new_Cell;
                new_Cell->Left = pre_row_ptr;
                curr_row_ptr->Down = new_Cell;
                new_Cell->Up = curr_row_ptr;
                pre_row_ptr = pre_row_ptr->Down;
                curr_row_ptr = new_Cell;
            }

            prev = curr;       
            curr = curr->Right;
        }
    }

    friend void DisplayGrid(const Spreadsheet &spreadsheet);

    void Insert_Row_Above()
    {
        Cell *new_Row = new Cell();
        Cell *temp = gridHead->Right;

        if (selectedCell->Up)
        {
            Cell *prevRow = selectedCell->Up;
            selectedCell->Up = new_Row;

            new_Row->Down = selectedCell;
            prevRow->Down = new_Row;
            new_Row->Up = prevRow;

            Cell *above_ptr = prevRow->Right;
            Cell *currPtr = selectedCell->Right;

            for (int idx = 1; idx < totalColumns; idx++)
            {
                Cell *new_Cell = new Cell();

                new_Row->Right = new_Cell;
                new_Cell->Left = new_Row;
                above_ptr->Down = new_Cell;
                new_Cell->Up = above_ptr;
                currPtr->Up = new_Cell;
                new_Cell->Down = currPtr;

                new_Row = new_Cell;
                above_ptr = above_ptr->Right;
                currPtr = currPtr->Right;
            }
        }
        else
        {
            Add_Row_To_Top();
        }

        totalRows++;
    }

    void Insert_Row_Below()
    {
        Cell *new_Row = selectedCell;

        if (selectedCell->Down)
        {
            Cell *nextHead = selectedCell->Down;
            Cell *belowPtr = nextHead->Right;
            Cell *currPtr = selectedCell->Right;

            Cell *new_Head = new Cell();
            nextHead->Up = new_Head;
            new_Head->Down = nextHead;
            new_Head->Up = selectedCell;
            selectedCell->Down = new_Head;

            Cell *new_RowPointer = new_Head;

            for (int i = 1; i < totalColumns; i++)
            {
                Cell *new_Cell = new Cell();
                new_RowPointer->Right = new_Cell;
                new_Cell->Left = new_RowPointer;
                belowPtr->Up = new_Cell;
                new_Cell->Down = belowPtr;
                currPtr->Down = new_Cell;
                new_Cell->Up = currPtr;

                new_RowPointer = new_Cell;
                belowPtr = belowPtr->Right;
                currPtr = currPtr->Right;
            }
        }
        else
        {
            Add_Row_To_Bottom(new_Row);
        }

        totalRows++;
    }

    void Add_Row_To_Top()
    {
        Cell *new_Head = new Cell();
        Cell *temp = gridHead;
        temp->Up = new_Head;
        new_Head->Down = temp;

        Cell *curr = new_Head;
        temp = temp->Right;

        for (int i = 1; i < totalColumns; i++)
        {
            Cell *new_Cell = new Cell();
            new_Cell->Left = curr;
            curr->Right = new_Cell;
            temp->Up = new_Cell;
            new_Cell->Down = temp;
            temp = temp->Right;
            curr = new_Cell;
        }

        gridHead = new_Head;
    }

    void Add_Row_To_Bottom(Cell *new_Row)
    {
        Cell *new_Head = new Cell();
        Cell *temp = new_Row->Right;
        new_Row->Down = new_Head;
        new_Head->Up = new_Row;

        Cell *curr = new_Head;

        for (int i = 1; i < totalColumns; i++)
        {
            Cell *new_Cell = new Cell();
            curr->Right = new_Cell;
            new_Cell->Left = curr;
            temp->Down = new_Cell;
            new_Cell->Up = temp;
            temp = temp->Right;
            curr = new_Cell;
        }
    }

    void Insert_Column_Right()
    {
        Cell *newColumn = selectedCell;

        while (newColumn->Up != NULL)
        {
            newColumn = newColumn->Up;
        }

        if (newColumn->Right)
        {
            Cell *nextColumnHead = newColumn->Right;
            Cell *nextPtr = nextColumnHead->Down;
            Cell *currPtr = newColumn->Down;
            Cell *new_Head = new Cell();
            new_Head->Left = newColumn;
            newColumn->Right = new_Head;
            new_Head->Right = nextColumnHead;
            nextColumnHead->Left = new_Head;

            for (int i = 1; i < totalRows; i++)
            {
                Cell *new_Cell = new Cell();
                new_Head->Down = new_Cell;
                new_Cell->Up = new_Head;
                nextPtr->Left = new_Cell;
                new_Cell->Right = nextPtr;
                currPtr->Right = new_Cell;
                new_Cell->Left = currPtr;

                new_Head = new_Cell;
                nextPtr = nextPtr->Down;
                currPtr = currPtr->Down;
            }
        }
        else
        {
            Add_Column_To_Right();
        }

        totalColumns++;
    }

    void Add_Column_To_Right()
    {
        Cell *newColumn = selectedCell;

        while (newColumn->Right != NULL)
        {
            newColumn = newColumn->Right;
        }

        Cell *new_Head = new Cell();
        Cell *temp = newColumn->Down;
        newColumn->Right = new_Head;
        new_Head->Left = newColumn;
        Cell *curr = new_Head;

        for (int i = 1; i < totalRows; i++)
        {
            Cell *new_Cell = new Cell();
            curr->Down = new_Cell;
            new_Cell->Up = curr;
            temp->Right = new_Cell;
            new_Cell->Left = temp;

            curr = new_Cell;
            temp = temp->Down;
        }
    }

    void Insert_Column_Left()
    {
        Cell *colHead = selectedCell;

        while (colHead->Up != nullptr)
        {
            colHead = colHead->Up;
        }

        if (colHead->Left)
        {
            Cell *prevColHead = colHead->Left;
            Cell *prevPointer = prevColHead->Down;
            Cell *currPtr = colHead->Down;
            Cell *new_Head = new Cell();
            new_Head->Right = colHead;
            colHead->Left = new_Head;
            new_Head->Left = prevColHead;
            prevColHead->Right = new_Head;

            for (int i = 1; i < totalRows; i++)
            {
                Cell *new_Cell = new Cell();
                new_Head->Down = new_Cell;
                new_Cell->Up = new_Head;
                prevPointer->Right = new_Cell;
                new_Cell->Left = prevPointer;
                currPtr->Left = new_Cell;
                new_Cell->Right = currPtr;

                new_Head = new_Cell;
                prevPointer = prevPointer->Down;
                currPtr = currPtr->Down;
            }
        }
        else
        {
            Add_Column_To_Left(colHead);
        }
        totalColumns++;
    }

    void Add_Column_To_Left(Cell *colHead)
    {
        Cell *new_Head = new Cell();
        Cell *temp = colHead->Down;
        colHead->Left = new_Head;
        new_Head->Right = colHead;
        gridHead = new_Head;

        for (int i = 1; i < totalRows; i++)
        {
            Cell *new_Cell = new Cell();
            new_Head->Down = new_Cell;
            new_Cell->Up = new_Head;
            temp->Left = new_Cell;
            new_Cell->Right = temp;

            new_Head = new_Cell;
            temp = temp->Down;
        }
    }

    void InsertCellByDownShift()
    {
        while (selectedCell->Down != nullptr)
        {
            selectedCell = selectedCell->Down;
        }

        while (selectedCell->Left != nullptr)
        {
            selectedCell = selectedCell->Left;
        }
        if (selectedCell->Down)
        {
            Cell *new_Row = selectedCell->Down;
            Cell *new_Cell = new Cell();
            new_Cell->Up = selectedCell;
            new_Cell->Down = new_Row;
            selectedCell->Down = new_Cell;
            new_Row->Up = new_Cell;

            new_Cell->Left = selectedCell->Left;
            new_Cell->Right = selectedCell->Right;
            if (selectedCell->Left)
            {
                selectedCell->Left->Right = new_Cell;
            }
            if (selectedCell->Right)
            {
                selectedCell->Right->Left = new_Cell;
            }
        }
        else
        {
            Insert_Row_Below();
        }

        totalRows++;
    }

    void InsertCellByRightShift()
    {
        while (selectedCell->Right != nullptr)
        {
            selectedCell = selectedCell->Right;
        }

        while (selectedCell->Up != nullptr)
        {
            selectedCell = selectedCell->Up;
        }
        if (selectedCell->Right)
        {
            Cell *nextColumn = selectedCell->Right;
            Cell *new_Cell = new Cell();
            new_Cell->Left = selectedCell;
            new_Cell->Right = nextColumn;
            selectedCell->Right = new_Cell;
            nextColumn->Left = new_Cell;
            new_Cell->Up = selectedCell->Up;
            new_Cell->Down = selectedCell->Down;
            if (selectedCell->Up)
            {
                selectedCell->Up->Down = new_Cell;
            }
            if (selectedCell->Down)
            {
                selectedCell->Down->Up = new_Cell;
            }
        }
        else
        {
            Insert_Column_Right();
        }

        totalColumns++;
    }

    void DeleteRow()
    {
        Cell *currentCell = selectedCell;
        Cell *tempCell = selectedCell;

        while (tempCell->Left != nullptr)
        {
            tempCell = tempCell->Left;
        }

        if (!tempCell->Up)
        {
            gridHead = gridHead->Down;
            Cell *downCell = tempCell->Down;

            while (downCell)
            {
                downCell->Up = nullptr;
                downCell = downCell->Right;
            }

            selectedCell = currentCell->Down;
        }
        else if (!tempCell->Down)
        {
            Cell *upCell = tempCell->Up;
            while (upCell)
            {
                upCell->Down = nullptr;
                upCell = upCell->Right;
            }

            selectedCell = currentCell->Up;
        }
        else
        {
            Cell *upCell = tempCell->Up;
            Cell *downCell = tempCell->Down;

            while (upCell)
            {
                upCell->Down = downCell;
                downCell->Up = upCell;

                upCell = upCell->Right;
                downCell = downCell->Right;
            }

            selectedCell = currentCell->Up;
        }

        totalRows--;
    }

    void DeleteColumn()
    {
        Cell *currentCell = selectedCell;
        Cell *tempCell = selectedCell;
        while (tempCell->Up != nullptr)
        {
            tempCell = tempCell->Up;
        }
        if (!tempCell->Left)
        {
            gridHead = tempCell->Right;
            Cell *rightCell = tempCell->Right;

            while (rightCell)
            {
                rightCell->Left = nullptr;
                rightCell = rightCell->Down;
            }

            selectedCell = currentCell->Right;
        }
        else if (!tempCell->Right)
        {
            Cell *leftCell = tempCell->Left;

            while (leftCell)
            {
                leftCell->Right = nullptr;
                leftCell = leftCell->Down;
            }

            selectedCell = currentCell->Left;
        }
        else
        {
            Cell *leftCell = tempCell->Left;
            Cell *rightCell = tempCell->Right;

            while (leftCell)
            {
                leftCell->Right = rightCell;
                rightCell->Left = leftCell;

                leftCell = leftCell->Down;
                rightCell = rightCell->Down;
            }

            selectedCell = currentCell->Left;
        }
        totalColumns--;
    }

    void ClearColumn()
    {
        Cell *currentCell = selectedCell;

        while (currentCell != nullptr)
        {
            currentCell->data = 0;
            currentCell = currentCell->Down;
        }

        cout << "Column cleared successfully." << endl;
        DisplayGrid(*this);
    }

    void ClearRow()
    {
        Cell *currentCell = selectedCell;

        while (currentCell != nullptr)
        {
            currentCell->data = 0;
            currentCell = currentCell->Right;
        }

        cout << "Row cleared successfully." << endl;
        DisplayGrid(*this);
    }

    void DeleteCellByUpShift()
    {
        if (selectedCell->Up != nullptr)
        {
            Cell *current = selectedCell;
            Cell *temp = current;

            while (temp->Down != nullptr)
            {
                temp = temp->Down;
            }
            Cell *newCell = new Cell(1); 
            temp->Down = newCell;
            newCell->Up = temp;

            temp = current->Up;

            if (temp)
            {
                temp->Down = current->Down;
                if (current->Down)
                {
                    current->Down->Up = temp;
                }
            }
            else
            {
                if (current->Down)
                {
                    current->Down->Up = nullptr;
                }
            }
            if (!current->Left)
            {
                Cell *right = current->Right;
                temp = current->Down;

                while (temp)
                {
                    right->Left = temp;
                    temp->Right = right;

                    temp = temp->Down;
                    right = right->Down;
                }

                if (selectedCell == gridHead)
                {
                    gridHead = current->Down;
                }
            }
            else if (!current->Right)
            {
                Cell *left = current->Left;
                temp = current->Down;

                while (temp)
                {
                    left->Right = temp;
                    temp->Left = left;

                    temp = temp->Down;
                    left = left->Down;
                }
            }
            else
            {
                Cell *right = current->Right;
                Cell *left = current->Left;
                temp = current->Down;

                while (temp)
                {
                    right->Left = temp;
                    temp->Right = right;
                    left->Right = temp;
                    temp->Left = left;

                    temp = temp->Down;
                    right = right->Down;
                    left = left->Down;
                }
            }

            selectedCell = current->Down;
            totalRows--;
        }
        else
        {
            cout << "Cannot delete the topmost cell in the column." << std::endl;
        }
    }

    void DeleteCellByLeftShift()
    {
        if (selectedCell->Left != nullptr)
        {
            Cell *current = selectedCell;
            Cell *temp = current;

            // Move to the last cell in the row
            while (temp->Right != nullptr)
            {
                temp = temp->Right;
            }

            // Add a new cell at the end of the row
            Cell *newCell = new Cell(1); // Assuming you want to initialize the new cell with data 1
            temp->Right = newCell;
            newCell->Left = temp;

            // Deleting the selected cell
            temp = current->Left;

            if (temp)
            {
                temp->Right = current->Right;
                if (current->Right)
                {
                    current->Right->Left = temp;
                }
            }
            else
            {
                // If it is the first column
                if (current->Right)
                {
                    current->Right->Left = nullptr;
                }
            }

            // Left shifting the cells
            if (!current->Up)
            {
                // It is the first row
                Cell *below = current->Down;
                temp = current->Right;

                while (temp)
                {
                    below->Up = temp;
                    temp->Down = below;

                    temp = temp->Right;
                    below = below->Right;
                }

                if (selectedCell == gridHead)
                {
                    gridHead = current->Right;
                }
            }
            else if (!current->Down)
            {
                // It is the last row
                Cell *above = current->Up;
                temp = current->Right;

                while (temp)
                {
                    above->Down = temp;
                    temp->Up = above;

                    temp = temp->Right;
                    above = above->Right;
                }
            }
            else
            {
                // It is a middle row
                Cell *below = current->Down;
                Cell *above = current->Up;
                temp = current->Right;

                while (temp)
                {
                    below->Up = temp;
                    temp->Down = below;
                    above->Down = temp;
                    temp->Up = above;

                    temp = temp->Right;
                    below = below->Right;
                    above = above->Right;
                }
            }

            selectedCell = current->Right;
            totalColumns--;
        }
        else
        {
            cout << "Cannot delete the leftmost cell in the row." << std::endl;
        }
    }

    int getRangeSum(Cell *startCell, Cell *endCell)
    {
        if (startCell == nullptr || endCell == nullptr)
        {
            cout << "Invalid input ";
            return 0;
        }

        Cell *tempSelectedCell = selectedCell;
        selectedCell = startCell;
        int startRow = getRowIndex(startCell);
        int startCol = getColumnIndex(startCell);
        selectedCell = endCell;
        int endRow = getRowIndex(endCell);
        int endCol = getColumnIndex(endCell);

        if (startRow > totalRows || startCol > totalColumns || endCol > totalColumns || endRow > totalRows)
        {
            cout << "Invalid input";
            return 0;
        }

        int sum = 0;
        for (int i = startRow; i <= endRow; i++)
        {
            for (int j = startCol; j <= endCol; j++)
            {
                sum += getValue(i, j);
            }
        }
        selectedCell = tempSelectedCell; // Restore the current cell to its original position
        return sum;
    }

    Cell *getCell(int s, int e)
    {
        Cell *forRow = gridHead;
        for (int i = 0; i < totalRows; i++)
        {
            Cell *forCol = forRow;
            for (int j = 0; j < totalColumns; j++)
            {
                if (i == s && j == e)
                {
                    return forCol; // get row index
                }
                forCol = forCol->Right;
            }
            forRow = forRow->Down;
        }
        return nullptr;
    }

    int getValue(int rowIdx, int colIdx)
    {
        Cell *currentRow = gridHead;

        for (int i = 0; i < totalRows; i++)
        {
            Cell *currentCell = currentRow;

            for (int j = 0; j < totalColumns; j++)
            {
                if (i == rowIdx && j == colIdx)
                {
                    return currentCell->data;
                }

                currentCell = currentCell->Right;
            }

            currentRow = currentRow->Down;
        }

        return -1;
    }

    int getRangeAverage(Cell *starting, Cell *ending)
    {
        int getSum = getRangeSum(starting, ending);
        int result = getSum / count(starting, ending);
        return result;
    }
    // part 18
    void RangeOptions(Cell *startCell, Cell *endCell, Cell *selectedCell)
    {
        int operationResult;
        int option = selectFunction();
        if (option == 1)
        {
            operationResult = getRangeSum(startCell, endCell);
        }
        else if (option == 2)
        {
            operationResult = getRangeAverage(startCell, endCell);
        }
        else if (option == 3)
        {
            operationResult = count(startCell, endCell);
        }
        else if (option == 4)
        {
            operationResult = Max(startCell, endCell);
        }
        else if (option == 5)
        {
            operationResult = Min(startCell, endCell);
        }

        else if(option == 6)
        {
            copyData(startCell,endCell);
        }
        else if(option == 7)
        {
            cut(startCell,endCell);
        }
        else
        {
            cout << "invalid input";
        }
        if (selectedCell == nullptr)
        {
            cout << "selected cell is representing to nullptr" << endl;
            return;
        }
        selectedCell->data = operationResult;
        cout << operationResult << "this is result " << endl;
    }
    int selectFunction()
    {
        int operation;
        cout << "1 - Calculate the SUM" << endl;
        cout << "2 - Calculate the AVG (Average)" << endl;
        cout << "3 - Count the number of cells" << endl;
        cout << "4 - Find the MAX value" << endl;
        cout << "5 - Find the MIN value" << endl;
        cout << "Enter your operation (1, 2, 3, 4, 5): ";
        cin >> operation;
        return operation;
    }

    int count(Cell *startCell, Cell *endCell)
    {
        if (startCell == nullptr || endCell == nullptr)
        {
            cout << "invalid input ";
            return 0;
        }
        int startRow = getRowIndex(startCell);
        int startCol = getColumnIndex(startCell);
        selectedCell = endCell;
        int endRow = getRowIndex(endCell);
        int endCol = getColumnIndex(endCell);
        if (startRow > totalRows || startCol > totalColumns || endCol > totalColumns || endRow > totalRows)
        {
            cout << "invalid input";
            return 0;
        }
        int count = 0;
        for (int i = startRow; i <= endRow; i++)
        {
            for (int j = startCol; j <= endCol; j++)
            {
                count++;
            }
        }
        return count;
    }

    int Max(Cell *startCell, Cell *endCell)
    {
        if (startCell == nullptr || endCell == nullptr)
        {
            cout << "Invalid input ";
            return 0;
        }

        int startRow = getRowIndex(startCell);
        int startCol = getColumnIndex(startCell);
        selectedCell = endCell;
        int endRow = getRowIndex(endCell);
        int endCol = getColumnIndex(endCell);

        if (startRow > totalRows || startCol > totalColumns || endCol > totalColumns || endRow > totalRows)
        {
            cout << "Invalid input";
            return 0;
        }

        int maximum = 0;
        for (int i = startRow; i <= endRow; i++)
        {
            for (int j = startCol; j <= endCol; j++)
            {
                maximum = max(maximum, getValue(i, j));
            }
        }
        return maximum;
    }

    int Min(Cell *startCell, Cell *endCell)
    {
        if (startCell == nullptr || endCell == nullptr)
        {
            cout << "invalid input ";
            return 0;
        }

        int startingRow = getRowIndex(startCell); // give you the statign index
        int startingCol = getColumnIndex(startCell);

        int endRow = getRowIndex(endCell);
        int endCol = getColumnIndex(endCell);
        if (startingRow > totalRows || startingCol > totalColumns || endCol > totalColumns || endRow > totalRows)
        {
            cout << "invalid input";
            return 0;
        }
        int minimum = Max(startCell, endCell);
        for (int i = startingRow; i <= endRow; i++)
        {
            for (int j = startingCol; j <= endCol; j++)
            {
                minimum = min(minimum, getValue(i, j));
            }
        }

        return minimum;
    }

    int getColumnIndex(Cell *cell)
    {
        Cell *forRow = gridHead;
        for (int i = 0; i < totalColumns; i++)
        {
            Cell *forCol = forRow;
            for (int j = 0; j < totalRows; j++)
            {
                if (forCol == cell)
                {
                    return i; // get column index
                }
                forCol = forCol->Down;
            }
            forRow = forRow->Right;
        }
        return -1;
    }

    int getRowIndex(Cell *targetCell) // will give you the current index
    {
        Cell *currentRow = gridHead;

        for (int rowIndex = 0; rowIndex < totalRows; rowIndex++)
        {
            Cell *currentColumn = currentRow;

            for (int colIndex = 0; colIndex < totalColumns; colIndex++)
            {
                if (currentColumn == targetCell)
                {
                    return rowIndex; // get row index
                }

                currentColumn = currentColumn->Right;
            }

            currentRow = currentRow->Down;
        }

        return -1;
    }

    void copyData(Cell *startCell, Cell *endCell)
    {
        if (startCell == nullptr || endCell == nullptr)
        {
            cout << "Invalid selection for copy operation." << endl;
            return;
        }

        vector<vector<int>> copiedData;

        int startRow = getRowIndex(startCell);
        int startCol = getColumnIndex(startCell);

        int endRow = getRowIndex(endCell);
        int endCol = getColumnIndex(endCell);

        if (startRow < endRow && startCol < endCol)
        {
            for (int i = startRow; i <= endRow; i++)
            {
                vector<int> row;
                for (int j = startCol; j <= endCol; j++)
                {
                    row.push_back(getValue(i, j));
                }
                copiedData.push_back(row);
            }
        }
        else if (startRow > endRow && startCol > endCol)
        {
            for (int i = endRow; i <= startRow; i++)
            {
                vector<int> row;
                for (int j = endCol; j <= startCol; j++)
                {
                    row.push_back(getValue(i, j));
                }
                copiedData.push_back(row);
            }
        }
        else if (startRow < endRow && startCol > endCol)
        {
            for (int i = startRow; i <= endRow; i++)
            {
                vector<int> row;
                for (int j = endCol; j <= startCol; j++)
                {
                    row.push_back(getValue(i, j));
                }
                copiedData.push_back(row);
            }
        }
        else if (startRow > endRow && startCol < endCol)
        {
            for (int i = endRow; i <= startRow; i++)
            {
                vector<int> row;
                for (int j = startCol; j <= endCol; j++)
                {
                    row.push_back(getValue(i, j));
                }
                copiedData.push_back(row);
            }
        }

        cout << "Copy operation successful." << endl;
    }

    void cut(Cell *startCell, Cell *endCell)
    {
        if (startCell == nullptr || endCell == nullptr)
        {
            cout << "Invalid selection for cut operation." << endl;
            return;
        }
        int startRow = getRowIndex(startCell);
        int startCol = getColumnIndex(startCell);

        int endRow = getRowIndex(endCell);
        int endCol = getColumnIndex(endCell);
        vector<vector<int>> copiedData;
        for (int i = startRow; i <= endRow; i++)
        {
            vector<int> row;
            for (int j = startCol; j <= endCol; j++)
            {
                row.push_back(getValue(i, j));
            }
            copiedData.push_back(row);
        }

        for (int i = startRow; i <= endRow; i++)
        {
            for (int j = startCol; j <= endCol; j++)
            {
                copiedData[i - startRow][j - startCol] = getValue(i, j);
                getCell(i, j)->data = 0; 
            }
        }

        cout << "Cut operation successful." << endl;
    }


    void paste()
    {
        //time was up and the code was not complete....but half of code i have been implemented
    }
    void userManual()
    {
        cout << "Use arrow keys to navigate." << endl;
        cout << "Press Space to enter data." << endl;
        cout << "Press Escape to exit." << endl;
        cout << "Press CTRL + A to insert a row above the selected cell." << endl;
        cout << "Press CTRL + B to insert a row below the selected cell." << endl;
        cout << "Press CTRL + R to insert a column to the right of the selected cell." << endl;
        cout << "Press CTRL + L to insert a column to the left of the selected cell." << endl;
        cout << "Press CTRL + I to insert cells by right shift." << endl;
        cout << "Press CTRL + K to insert cells by down shift." << endl;
        cout << "Press CTRL + O to delete cells by left shift." << endl;
        cout << "Press CTRL + U to delete cells by up shift." << endl;
        cout << "Press CTRL + D to delete a column." << endl;
        cout << "Press CTRL + E to delete a row." << endl;
        cout << "Press CTRL + M to clear a column." << endl;
        cout << "Press CTRL + N to clear a row." << endl;
        cout << "Press F1 key to select a range of cells." << endl;
    }

    int getInputData()
    {
        cout << "Enter data: ";
        int inputData = 0;
        cin >> inputData;
        selectedCell->data = inputData;
    }
};

void KeyMover(Spreadsheet &spreadsheet, string color, bool &flag)
{
    if (GetAsyncKeyState(VK_UP) && spreadsheet.selectedCell->Up != nullptr)
    {
        spreadsheet.selectedCell->color = "\33[37m";
        spreadsheet.selectedCell = spreadsheet.selectedCell->Up;
        spreadsheet.selectedCell->color = "\33[33m";
        flag = true;
    }
    if (GetAsyncKeyState(VK_DOWN) && spreadsheet.selectedCell->Down != nullptr)
    {
        spreadsheet.selectedCell->color = "\33[37m";
        spreadsheet.selectedCell = spreadsheet.selectedCell->Down;
        spreadsheet.selectedCell->color = "\33[33m";
        flag = true;
    }
    if (GetAsyncKeyState(VK_RIGHT) && spreadsheet.selectedCell->Right != nullptr)
    {
        spreadsheet.selectedCell->color = "\33[37m";
        spreadsheet.selectedCell = spreadsheet.selectedCell->Right;
        spreadsheet.selectedCell->color = "\33[33m";
        flag = true;
    }
    if (GetAsyncKeyState(VK_LEFT) && spreadsheet.selectedCell->Left != nullptr)
    {
        spreadsheet.selectedCell->color = "\33[37m";
        spreadsheet.selectedCell = spreadsheet.selectedCell->Left;
        spreadsheet.selectedCell->color = "\33[33m";
        flag = true;
    }
}

void DisplayGrid(const Spreadsheet &spreadsheet)
{
    Cell *currentRow = spreadsheet.gridHead;

    while (currentRow != nullptr)
    {
        Cell *currentCell = currentRow;

        while (currentCell != nullptr)
        {
            cout << currentCell->color << currentCell->data << "|";
            currentCell = currentCell->Right;
        }

        cout << "NULL";
        cout << endl;
        currentRow = currentRow->Down;
    }
}

void rangeRunning(Spreadsheet &spreadsheet)
{
    bool RangeRunning = true, flag = false;
    Cell *current = spreadsheet.selectedCell;
    Sleep(100);
    while (RangeRunning)
    {
        KeyMover(spreadsheet, "\33[35m", flag);
        if (GetAsyncKeyState(VK_F1))
        {
            if (spreadsheet.startCell == nullptr)
            {
                spreadsheet.startCell = spreadsheet.selectedCell;
                cout << "Start cell selected" << endl;
                cout << "Select End cell..." << endl;
                flag = true;
            }
            else
            {
                spreadsheet.endCell = spreadsheet.selectedCell;
                cout << "End cell selected" << endl;
                RangeRunning = false;
                spreadsheet.startCell->color = "\33[37m";
                spreadsheet.endCell->color = "\33[37m";
            }
        }
        Sleep(100);

        if (flag)
        {
            flag = false;
            system("cls");
            spreadsheet.userManual();
            DisplayGrid(spreadsheet);
            if (spreadsheet.startCell != nullptr)
            {
                spreadsheet.startCell->color = "\33[35m";
                cout << "Start cell selected" << endl;
                cout << "Select end cell" << endl;
            }
            else
            {
                cout << "Select start cell" << endl;
            }
        }
    }
    spreadsheet.selectedCell = current;
}

int main()
{
    Spreadsheet spreadsheet(5, 5);
    spreadsheet.selectedCell = spreadsheet.gridHead;
    system("cls");
    spreadsheet.userManual();
    DisplayGrid(spreadsheet);

    bool ExcelRunning = true, flag = false;
    while (ExcelRunning)
    {
        KeyMover(spreadsheet, "\33[33m", flag);

        if (GetAsyncKeyState(VK_ESCAPE))
        {
            ExcelRunning = false;
            system("cls");
        }
        if (flag)
        {
            system("cls");
            spreadsheet.userManual();
            DisplayGrid(spreadsheet);
            flag = false;
        }

        if (GetAsyncKeyState(VK_SPACE))
        {
            spreadsheet.getInputData();
            flag = true;
        }

        else if (GetAsyncKeyState(VK_CONTROL))
        {
            if (GetAsyncKeyState('A'))
            {
                spreadsheet.Insert_Row_Above();
                flag = true;
            }
            else if (GetAsyncKeyState('B'))
            {
                spreadsheet.Insert_Row_Below();
                flag = true;
            }
            else if (GetAsyncKeyState('R'))
            {
                spreadsheet.Insert_Column_Right();
                flag = true;
            }
            else if (GetAsyncKeyState('L'))
            {
                spreadsheet.Insert_Column_Left();
                flag = true;
            }
            else if (GetAsyncKeyState('I'))
            {
                spreadsheet.InsertCellByRightShift();
                flag = true;
            }
            else if (GetAsyncKeyState('K'))
            {
                spreadsheet.InsertCellByDownShift();
                flag = true;
            }
            else if (GetAsyncKeyState('O'))
            {
                spreadsheet.DeleteCellByLeftShift();
                flag = true;
            }
            else if (GetAsyncKeyState('U'))
            {
                spreadsheet.DeleteCellByUpShift();
                flag = true;
            }
            else if (GetAsyncKeyState('D'))
            {
                spreadsheet.DeleteColumn();
                flag = true;
            }
            else if (GetAsyncKeyState('E'))
            {
                spreadsheet.DeleteRow();
                flag = true;
            }
            else if (GetAsyncKeyState('M'))
            {
                spreadsheet.ClearColumn();
                flag = true;
            }
            else if (GetAsyncKeyState('N'))
            {
                spreadsheet.ClearRow();
                flag = true;
            }
        }

        else if (GetAsyncKeyState(VK_F1))
        {
            rangeRunning(spreadsheet);
            spreadsheet.RangeOptions(spreadsheet.startCell, spreadsheet.endCell, spreadsheet.selectedCell);
        }
        Sleep(200);
    }

    return 0;
}
