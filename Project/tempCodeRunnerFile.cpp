
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 void RangeSelection(Spreedsheet spreedsheet, Spreedsheet *range)
    {
        // storing current selected cell
        Cell *current = spreedsheet.selectedCell;

        // selecting cells
        cout << "Select Starting cell..." << endl;

        bool selecting = true, modify = false;
        Sleep(100);
        while (selecting)
        {
            arrowMovement("\33[35m", modify);
            if (GetAsyncKeyState(VK_F1))
            {
                if (range->start == nullptr)
                {
                    range->start = excel->selected;
                    cout << "Start cell selected" << endl;
                    cout << "Select End cell..." << endl;
                    modify = true;
                }
                else
                {
                    range->end = excel->selected;
                    cout << "End cell selected" << endl;
                    selecting = false;
                    range->start->color = "\33[37m";
                    range->end->color = "\33[37m";
                }
            }
            Sleep(100);

            if (modify)
            {
                modify = false;
                system("cls");
                userManual();
                DisplayGrid(spreadsheet);
                if (range->start != nullptr)
                {
                    range->start->color = "\33[35m";
                    cout << "Start cell selected" << endl;
                    cout << "Select end cell" << endl;
                }
                else
                {
                    cout << "Select start cell" << endl;
                }
            }
        }

        // resetting the selected cell to default
        excel->selected = current;
    }


        void GetRangeSum(Cell *RangeStart, Cell *RangeEnd)
    {
        int sum = 0;

        // Validate input parameters
        if (RangeStart == nullptr || RangeEnd == nullptr)
        {
            cout << "Invalid range." << endl;
            return;
        }

        // Iterate over the range and accumulate the data values
        Cell *currentRow = RangeStart;

        while (currentRow != nullptr && currentRow != RangeEnd->Down)
        {
            Cell *currentCell = currentRow;

            while (currentCell != nullptr && currentCell != RangeEnd->Right)
            {
                sum += currentCell->data;
                currentCell = currentCell->Right;
            }

            currentRow = currentRow->Down;
        }

        cout << "Sum of the range: " << sum << endl;
    }

    void GetRangeAverage(Cell *RangeStart, Cell *RangeEnd)
    {
        int sum = 0;
        int count = 0;

        // Validate input parameters
        if (RangeStart == nullptr || RangeEnd == nullptr)
        {
            cout << "Invalid range." << endl;
            return;
        }

        // Iterate over the range and accumulate the sum and count
        Cell *currentRow = RangeStart;

        while (currentRow != nullptr && currentRow != RangeEnd->Down)
        {
            Cell *currentCell = currentRow;

            while (currentCell != nullptr && currentCell != RangeEnd->Right)
            {
                sum += currentCell->data;
                count++;
                currentCell = currentCell->Right;
            }

            currentRow = currentRow->Down;
        }

        // Calculate and display the average
        if (count > 0)
        {
            double average = static_cast<double>(sum) / count;
            cout << "Average of the range: " << average << endl;
        }
        else
        {
            cout << "No data in the specified range." << endl;
        }
    }

    int RangeManual()
    {
        int option = 0;
        cout << "1● SUM" << endl;
        cout << "2● AVG " << endl;
        cout << "3● COUNT " << endl;
        cout << "4● MIN" << endl;
        cout << "5● MAX" << endl;

        cout<< "Select one of the Above Option : ";
        cin>> option;  

        return option;     
    }
