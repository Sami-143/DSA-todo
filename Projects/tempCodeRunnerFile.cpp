vector<vector<int>> copy(Cell* starting, Cell* ending)
    {
        vector<vector<int>> copy = utlisForCopyOrPaste(starting, ending, "copy");
        if (copy.empty())
        {
            cout << "nothing is copied"; // but in excel sheet we can copy the empty cell as well;
            return { {} };
        }
        return copy;
    }

    void copiedElementDisplay(vector<vector<int>> copied)
    {
        // vector<vector<int>> copied = cut(origionalHead, origionalHead->down->down
        //                                                     ->down->down->right->right);
        for (int i = 0; i < copied.size(); i++)
        {
            for (int j = 0; j < copied[0].size(); j++)
            {
                cout << copied[i][j] << "-->";
            }
            cout << "Null" << endl;
        }
    }

    vector<vector<int>> cut(Cell* starting, Cell* ending)
    {
        vector<vector<int>> cut = utlisForCopyOrPaste(starting, ending, "cut");
        if (cut.empty())
        {
            cout << "nothing is copied";
            return { {} };
        }
        return cut;
    }

    void paste(vector<vector<int>> copyOrCut)
    {

        vector<vector<int>> copied = copyOrCut;

        if (current == nullptr)
        {
            cout << "poiting to null" << endl;
            return;
        }
        for (int i = 0; i < copied.size(); i++)
        {
            Cell* temp = current;
            for (int j = 0; j < copied[0].size(); j++)
            {
                temp->data = copied[i][j];
                if (temp->right == nullptr && j < copied[0].size() - 1)
                {
                    makeColumnForRight();
                    temp = current->right;

                }
                else
                {
                    cout << getColumnIndex() << "col" << getRowIndex() << "row" << endl;
                    temp = temp->right;
                }
            }
            if (current->down == nullptr && i < copied.size() - 1)
            {
                makeRowAtEnd();
            }
            current = current->down;
        }
    }
    vector<vector<int>> utlisForCopyOrPaste(Cell* starting, Cell* ending, string temp)
    {
        if (starting == nullptr || ending == nullptr)
        {
            cout << "invalid input ";
            return { {} }; // empty{}
        }
        // find the indexices of stating cell and ending cell
        Cell* tempCurr = current; // store current into temp variable and before the end of fuction do update the currrent current=temocurr
        current = starting;
        int startingRow = getRowIndex(); // give you the statign index
        int startingCol = getColumnIndex();
        current = ending;
        int endingRow = getRowIndex();
        int endingCol = getColumnIndex();
        if (startingRow > rows || startingCol > col || endingCol > col || endingRow > rows)
        {
            cout << "invalid input";
            return { {} };
        }
        vector<vector<int>> Copy;
        if (startingRow <= endingRow && startingCol <= endingCol)
        {
            for (int i = startingRow; i <= endingRow; i++)
            {
                vector<int> row;
                for (int j = startingCol; j <= endingCol; j++)
                {
                    Cell* cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }
        else if (startingRow > endingRow && startingCol > endingCol)
        {
            for (int i = endingRow; i <= startingRow; i++)
            {
                vector<int> row;
                for (int j = endingCol; j <= startingCol; j++)
                {
                    Cell* cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }

        else if (startingRow < endingRow && startingCol > endingCol)
        {
            for (int i = startingRow; i <= endingRow; i++)
            {
                vector<int> row;
                for (int j = endingCol; j <= startingCol; j++)
                {
                    Cell* cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                        cout << i << j;
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }
        else if (startingRow > endingRow && endingCol > startingCol)
        {

            for (int i = endingRow; i <= startingRow; i++)
            {
                vector<int> row;
                for (int j = startingCol; j <= endingCol; j++)
                {
                    Cell* cell = getCell(i, j);
                    if (cell != nullptr)
                    {
                        row.push_back(cell->data);
                    }
                    if (temp == "cut")
                    {
                        cell->data = -2;
                    }
                }
                Copy.push_back(row);
            }
        }
        current = tempCurr; // regain the current into his same position
        return Copy;
    }