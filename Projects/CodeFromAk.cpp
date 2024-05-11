#include <iostream>
#include <list>
#include <iterator>
#include <algorithm> 
#include <string>
#include<queue>
#include<ctime>
#include<fstream>
#include <list>
#include <conio.h>
#include <cstdlib>
#include <stack>
#include<windows.h>

using namespace std;


string splitString(string input, char split)
{
    string result = "";
    int startIndex = 0;

    for (int i = 0; i < input.length(); i++)
    {
        if (input[i] == split)
        {
            startIndex = i + 1;
            break;
        }
    }

    for (int i = startIndex; i < input.length(); i++)
    {
        result = result + input[i];
    }

    return result;
}

void gotoxy(int column, int line)
{
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE),
        coord
    );
}



//File class
class File
{
public:
    string name;
    string data;
    string path;
    int size;


    // Default constructor
    File()
    {
        name = "";
        data = "";
        size = 0;
    }

    File(string filename, string filedata)
    {
        name = filename;
        data = filedata;
        size = data.length();
    }

    bool containsText(string searchText)
    {
        // Check if the file's data contains the search text
        size_t found = data.find(searchText);
        return found != string::npos;
    }

    void print_file_Data()
    {
        cout << data << endl;
    }

    bool operator<(const File& other) const {
        return size < other.size;
    }
};
class TextDocumentState
{
public:
    list<list<char>>* editingTextLines;
    list<char>::iterator colIterator;
    list<list<char>>::iterator rowIterator;
    int cursor_row, cursor_col;

    TextDocumentState()
    {
        cursor_row = cursor_col = 0;
        rowIterator = editingTextLines->begin();
        colIterator = rowIterator->begin();
        editingTextLines = new list<list<char>>();
        editingTextLines->push_back(list<char>());
    }

    void display()
    {
        for (auto iter = editingTextLines->begin(); iter != editingTextLines->end(); ++iter)
        {
            for (auto iter1 = iter->begin(); iter1 != iter->end(); ++iter1)
            {
                cout << *iter1;
            }
            cout << endl;
        }
    }
};


class TextEditor {
public:
    int cursor_row;
    int cursor_col;
    list<list<char>>* Lines;
    list<list<char>>::iterator rowIterator;
    list<char>::iterator colIterator;
    stack<TextDocumentState*>* redoStack;
    deque<TextDocumentState*>* undoQueue;

    TextEditor()
    {
        cursor_row = cursor_col = 0;
        Lines = new list<list<char>>();
        Lines->push_back(list<char>());
        redoStack = new stack<TextDocumentState*>();
        undoQueue = new deque<TextDocumentState*>();
        rowIterator = Lines->begin();
        colIterator = rowIterator->begin();
    }



    void SavingCurrentFileState() {
        TextDocumentState* state = new TextDocumentState();

        auto row_itr = state->editingTextLines->begin();
        for (auto iter = Lines->begin(); iter != Lines->end(); iter++, row_itr++) {
            state->editingTextLines->push_back(list<char>());
            for (auto iter1 = iter->begin(); iter1 != iter->end(); iter1++) {
                row_itr->push_back(*iter1);
            }
        }

        state->rowIterator = state->editingTextLines->begin();
        for (int idx = 0; idx < cursor_col; idx++) {
            state->rowIterator++;
        }
        state->colIterator = state->rowIterator->begin();
        for (int idx = 0; idx < cursor_row; idx++) {
            state->colIterator++;
        }
        state->cursor_row = cursor_row;
        state->cursor_col = cursor_col;

        undoQueue->push_back(state);

        if (undoQueue->size() > 5) {
            undoQueue->pop_front();
        }
    }
    void LoadingFileData(File* filename)
    {
        string current_line = "";
        string data = filename->data;

        for (int idx = 0; idx < data.length(); idx++)
        {
            if (data[idx] == '\n')
            {
                rowIterator = Lines->insert(rowIterator, list<char>());
                for (int j = 0; j < current_line.length(); j++)
                {
                    rowIterator->push_back(current_line[j]);
                }
                current_line = "";
                rowIterator++;
            }
            else
            {
                current_line += data[idx];
            }
        }

        if (current_line.length() > 0)
        {
            rowIterator = Lines->insert(rowIterator, list<char>());
            for (int j = 0; j < current_line.length(); j++)
            {
                rowIterator->push_back(current_line[j]);
            }
        }
        rowIterator = Lines->begin();
        colIterator = rowIterator->begin();
    }

    void SaveFile(File* file) {
        string data = "";
        for (auto iter = Lines->begin(); iter != Lines->end(); ++iter) {
            for (auto iter1 = iter->begin(); iter1 != iter->end(); ++iter1) {
                data += *iter1;
            }
            data += "\n";
        }
        file->data = data;
    }


    void display()
    {
        for (auto iter = Lines->begin(); iter != Lines->end(); ++iter)
        {
            for (auto iter1 = iter->begin(); iter1 != iter->end(); ++iter1)
            {
                cout << *iter1;
            }
            cout << endl;
        }
    }

    void loadCondition(TextDocumentState* state) {

        Lines = state->editingTextLines;
        rowIterator = Lines->begin();
        cursor_row = state->cursor_row;
        cursor_col = state->cursor_col;
        for (int idx = 0; idx < cursor_col; idx++) {
            rowIterator++;
        }
        colIterator = rowIterator->begin();
        for (int idx = 0; idx < cursor_row; idx++) {
            colIterator++;
        }
    }


    void movingUpAfterKeyPressed() {
        if (cursor_col != 0) {
            cursor_col--;
            rowIterator--;
            if (cursor_row >= rowIterator->size()) {
                cursor_row = rowIterator->size();
            }
            colIterator = rowIterator->begin();
            for (int idx = 0; idx < cursor_row; idx++) {
                colIterator++;
            }
        }
    }

    void movingDownAfterKeyPressed() {
        if (cursor_col != Lines->size() - 1) {
            cursor_col++;
            rowIterator++;
            if (cursor_row >= rowIterator->size()) {
                cursor_row = rowIterator->size();
            }
            colIterator = rowIterator->begin();
            for (int idx = 0; idx < cursor_row; idx++) {
                colIterator++;
            }
        }
    }


    void movingRightAfterKeyPressed() {
        if (cursor_row > rowIterator->size() - 1 && cursor_col != Lines->size() - 1) {
            rowIterator++;
            cursor_col++;
            cursor_row = 0;
            colIterator = rowIterator->begin();
        }
        else if (cursor_row <= rowIterator->size() - 1) {
            cursor_row++;
            colIterator++;
        }
    }


    void movingLeftAfterKeyPressed() {
        if (cursor_row == 0 && cursor_col != 0) {
            rowIterator--;
            cursor_col--;
            cursor_row = rowIterator->size();
            colIterator = rowIterator->begin();
            for (int idx = 0; idx < cursor_row; idx++) {
                colIterator++;
            }
        }
        else if (cursor_row != 0) {
            cursor_row--;
            colIterator--;
        }
    }

    void BackpaceCommandFroomKeyBoard() {
        if (cursor_row == 0 && cursor_col != 0) {

            // copy data of this line
            list<char>* temp = new list<char>();
            for (auto iter = colIterator; iter != rowIterator->end(); ++iter) {
                temp->push_back(*iter);
            }

            // erase this line
            rowIterator = Lines->erase(rowIterator);

            // move to previous line
            rowIterator--;
            cursor_col--;
            cursor_row = rowIterator->size();
            colIterator = rowIterator->begin();
            for (int idx = 0; idx < cursor_row; idx++) {
                colIterator++;
            }

            // paste data of next line to current line
            for (auto iter = temp->begin(); iter != temp->end(); ++iter) {
                rowIterator->push_back(*iter);
            }
        }
        else if (cursor_row != 0) {
            cursor_row--;
            colIterator--;
            colIterator = rowIterator->erase(colIterator);
        }
    }

    void DeleteCommandinKeyBoard() {
        if (cursor_row == rowIterator->size() && cursor_col != Lines->size() - 1) {

            // copy data of next line
            list<char>* temp_iterator = new list<char>();
            auto tempItr = rowIterator;
            tempItr++;
            for (auto iter = tempItr->begin(); iter != tempItr->end(); ++iter) {
                temp_iterator->push_back(*iter);
            }

            // erase next line
            //rowIterator = lines->erase(tempItr);
            Lines->erase(tempItr);

            // paste data of next line to current line
            for (auto iter = temp_iterator->begin(); iter != temp_iterator->end(); ++iter) {
                rowIterator->push_back(*iter);
            }

            // reset column iterator
            colIterator = rowIterator->begin();
            for (int i = 0; i < cursor_row; i++) {
                colIterator++;
            }
        }
        else if (cursor_row != rowIterator->size()) {
            colIterator = rowIterator->erase(colIterator);
        }
    }

    void AppendAtNextLine() {

        // first copy the rest of the list
        list<char>* temp_itr = new list<char>();
        for (auto iter = colIterator; iter != rowIterator->end(); ++iter) {
            temp_itr->push_back(*iter);
        }

        // erase it in the current line and paste in the next line
        rowIterator->erase(colIterator, rowIterator->end());
        rowIterator = Lines->insert(++rowIterator, *temp_itr);
        colIterator = rowIterator->begin();

        cursor_col++;
        cursor_row = 0;
    }

    void AddingCharcter(char c) {
        rowIterator->insert(colIterator, c);
        cursor_row++;
    }

    void UndoCrtlZ() {
        if (!undoQueue->empty()) {
            TextDocumentState* state = undoQueue->back();
            undoQueue->pop_back();
            redoStack->push(state);
            loadCondition(state);
            system("cls");
            display();
        }
    }

    void RedoCrtlY(bool flag) {
        if (!redoStack->empty() && flag) {
            TextDocumentState* state = redoStack->top();
            redoStack->pop();

            system("cls");
            state->display();
            Sleep(2500);
            loadCondition(state);
            system("cls");
            display();
        }
    }

    void handleKeyPress(File* filename) {
        LoadingFileData(filename);

        system("color F0");
        system("cls");

        display();

        bool flag = false;
        bool falg1 = false;

        if (rowIterator->empty()) {
            rowIterator->push_back(' ');
            colIterator = rowIterator->begin();
        }

        while (true) {

            gotoxy(cursor_row, cursor_col);
            char character = _getch();

            if (character == 0)
                continue;
            
            else if (character == 75) 
            {
                movingLeftAfterKeyPressed();
            }
            else if (character == 77) 
            {
                movingRightAfterKeyPressed();
            }

            else if (character == 72) 
            {
                movingUpAfterKeyPressed();
            }


            else if (character == 80) 
            {
                movingDownAfterKeyPressed();
            }
            
            else if (character == 8) // backspace pressed
            {   
                SavingCurrentFileState();
                BackpaceCommandFroomKeyBoard();
                flag = true;
            }
            else if (character == 27) {  // escape key pressed
                break;
            }
            else if (character == 83)  // delete pressed
            { 
                SavingCurrentFileState();
                DeleteCommandinKeyBoard();
                flag = true;
            }
            else if (character == 26) // CTRL + Z
            {  
                UndoCrtlZ();
                falg1 = true;
            }
            else if (character == 25) // CTRL + Y
            {  
                RedoCrtlY(falg1);
                falg1 = false;
            }
            else if (character == 13) // enter key pressed
            {  
                SavingCurrentFileState();
                AppendAtNextLine();
                flag = true;
            }
            else // insert character
            {      
                SavingCurrentFileState();
                AddingCharcter(character);
                flag = true;
            }


            if (flag) {
                system("cls");
                display();
                flag = false;
                falg1 = false;
            }
        }

        SaveFile(filename);
        system("color 07");
        system("cls");
    }


};

// directory class
class Directory
{
public:
    string name;
    string path;
    list<Directory>* directory;
    list<File>* fileList;
    Directory* parent_head;

    Directory(string Directoryname, Directory* parent_head)
    {
        name = Directoryname;
        this->parent_head = parent_head;
        path = setPath();

        directory = new list<Directory>();
        fileList = new list<File>();
    }

    void addingFile(string file_name, string file_data)
    {
        fileList->push_back(File(file_name, file_data));
    }

    void addingDirectory(string directory_Name, Directory* parent_head)
    {
        directory->push_back(Directory(directory_Name, parent_head));
    }


    File* findingFile(string filename) {
        if (filename.find("V:\\") != string::npos || filename.find("V:") != string::npos) {
            return findingFile(filename.substr(filename.find("\\") + 1, filename.length() - 1));
        }
        else if (filename.find("\\") != string::npos) {
            string name = filename.substr(0, filename.find("\\"));

            for (auto it = directory->begin(); it != directory->end(); ++it) {
                if (it->name == name) {
                    return it->findingFile(filename.substr(filename.find("\\") + 1, filename.length() - 1));
                }
            }
        }
        else {
            for (auto it = fileList->begin(); it != fileList->end(); ++it) {
                if (it->name == filename) {
                    return &(*it);
                }
            }
           
        }
        return nullptr;
    }

    Directory getDirectoryByName(string directoryName)
    {
        for (auto it = directory->begin(); it != directory->end(); ++it)
        {
            if (it->name == directoryName)
            {
                return *it;
            }
        }
        // Return an empty directory if not found (you may want to handle this differently)
        return Directory("", nullptr);
    }

    File getFileByName(string fileName)
    {
        for (auto it = fileList->begin(); it != fileList->end(); ++it)
        {
            if (it->name == fileName)
            {
                return *it;
            }
        }
        // Return an empty file if not found (you may want to handle this differently)
        return File();
    }

    void printingPath()
    {
        cout << (path == "V" ? "V:\\" : path) << endl;
    }

    string setPath()
    {
        if (parent_head == nullptr)
        {
            return "V:\\";
        }
        return parent_head->path + name + "\\";
    }

    // checking if directory already exists
    bool doesDirectoryExist(string _name)
    {
        for (auto it = directory->begin(); it != directory->end(); it++)
        {
            if (it->name == _name)
            {
                return true;
            }
        }
        return false;
    }

    // checking if file already exists
    bool doesFileExist(string filename)
    {
        for (auto it = fileList->begin(); it != fileList->end(); it++)
        {
            if (it->name == filename)
            {
                return true;
            }
        }
        return false;
    }

    void RENAME(string currentName, string newName)
    {
        // Find the file with the current name
        auto itFile = fileList->begin();
        while (itFile != fileList->end()) {
            if (itFile->name == currentName) {
                break;
            }
            ++itFile;
        }

        // Find the directory with the current name
        auto itDirectory = directory->begin();
        while (itDirectory != directory->end()) {
            if (itDirectory->name == currentName) {
                break;
            }
            ++itDirectory;
        }

        // Check if either file or directory with the current name exists
        if (itFile != fileList->end() || itDirectory != directory->end())
        {
            // Check if a file or directory with the new name already exists
            if (!doesFileExist(newName) && !doesDirectoryExist(newName))
            {
                // Rename the file
                if (itFile != fileList->end()) {
                    itFile->name = newName;
                    cout << "File renamed successfully" << endl;
                    //SAVE("your_filename.txt");
                }

                // Rename the directory
                if (itDirectory != directory->end()) {
                    itDirectory->name = newName;
                    cout << "Directory renamed successfully" << endl;
                    //SAVE("your_filename.txt");
                }
            }
            else
            {
                cout << "File or directory with the new name already exists" << endl;
            }
        }
        else
        {
            cout << "File or directory with the current name not found" << endl;
        }
    }
    // get directory through path
    Directory* getDirectoryFromPath(string path) {
        if ( path == "V:" || path == "V:\\") {
            return this;
        }
        else if (path.find("\\") != string::npos) {
            string directoryname = path.substr(0, path.find("\\"));

            if (directoryname == "V:\\" || directoryname == "V:") {
                return this->getDirectoryFromPath(path.substr(path.find("\\") + 1, path.length() - 1));
            }

            for (auto it = directory->begin(); it != directory->end(); ++it) {
                if (it->name == directoryname) {
                    return it->getDirectoryFromPath(path.substr(path.find("\\") + 1, path.length() - 1));
                }
            }
        }
        else {
            for (auto it = directory->begin(); it != directory->end(); ++it) {
                if (it->name == path) {
                    return &(*it);
                }
            }
        }
        return nullptr;
    }

};

// tree class
class TreeNode
{
    priority_queue<string> priorityPrintQueue;
    string extension;
public:
    Directory* root;
    Directory* current_ptr;
    string prompt = "> ";

    TreeNode():extension(".txt")
    {
        current_ptr = root = new Directory("V", nullptr);
    }

    void addFile(string _name, string _data)
    {
        root->fileList->push_back(File(_name, _data));
    }

    void addDirectory(string _name)
    {
        root->directory->push_back(Directory(_name, root));
    }

    void printingPath()
    {
        cout << root->path << endl;
    }

    // dir function
    void DIR()
    {
        if (current_ptr->directory->empty() && current_ptr->fileList->empty())
        {
            cout << "No files or directory in the current directory." << endl;
        }
        else
        {
            cout << "directory:" << endl;
            for (auto it = current_ptr->directory->begin(); it != current_ptr->directory->end(); ++it)
            {
                cout << "   [DIR]  " << it->name << endl;
            }

            cout << endl
                << "Files:" << endl;
            for (auto it = current_ptr->fileList->begin(); it != current_ptr->fileList->end(); ++it)
            {
                cout << "   [FILE] " << it->name << endl;
            }

            cout << endl
                << "\t\t(" << current_ptr->directory->size() << ") Dir(s)" << endl;
            cout << "\t\t(" << current_ptr->fileList->size() << ") File(s)" << endl;
        }
    }

    // rmdir function
    void RMDIR(string directoryname) {
        if (!current_ptr->doesDirectoryExist(directoryname)) {
            cout << "Directory not found" << endl;
            return;
        }
        for (auto it = current_ptr->directory->begin(); it != current_ptr->directory->end(); ++it) {
            if (it->name == directoryname)
            {
                current_ptr->directory->erase(it);
                break;
            }
        }
    }

    // mkdir function
    void MKDIR(string directoryName) {

        if (directoryName.empty()) {
            cout << "Invalid syntax" << endl;
            return;
        }

        if (directoryName.find("\\") != string::npos || directoryName == "V:\\" || directoryName == "V:") {
            cout << "Invalid syntax" << endl;
            return;
        }

        // checking if directory already exists
        if (!current_ptr->doesDirectoryExist(directoryName) && !current_ptr->doesFileExist(directoryName))
        {
            current_ptr->directory->push_back(Directory(directoryName, current_ptr));
        }
        else
        {
            cout << "Directory or name already exists" << endl;
        }
    }

    // mkfile function
    void createFile(string fileName)
    {
        if (fileName.empty())
        {
            cout << "Invalid syntax: File name cannot be empty" << endl;
            return;
        }

        if (!isValidFileName(fileName))
        {
            cout << "Invalid file name: File name should contain only alphanumeric characters and no spaces" << endl;
            return;
        }

        // checking for duplicate file names
        if (!current_ptr->doesFileExist(fileName) && !current_ptr->doesDirectoryExist(fileName))
        {
            cout << "Enter file data: ";
            string fileData = getInput();
            current_ptr->addingFile(fileName + extension, fileData); // Use default extension

            cout << "File created successfully" << endl;
        }
        else
        {
            cout << "File or name already exists" << endl;
        }
    }

    // Function to check if a file name is valid
    bool isValidFileName(const string& fileName)
    {
        // Check if the file name contains only alphanumeric characters and no spaces
        return all_of(fileName.begin(), fileName.end(), [](char c) { return isalnum(c) || c == '_'; });
    }

    // rmfile function
    void DEL(string fileName)
    {
        if (!current_ptr->doesFileExist(fileName)) {
            cout << "File not found" << endl;
            return;
        }
        for (auto it = current_ptr->fileList->begin(); it != current_ptr->fileList->end(); ++it) {
            if (it->name == fileName) {
                current_ptr->fileList->erase(it);
                break;
            }
        }
    }

    // Add this function in the TreeNode class
    void PROMPT(string newPrompt)
    {
        // Assuming newPrompt is a valid prompt format
        current_ptr->path = newPrompt;
    }
    

    void ATTRIB(string attrib)
    {
        File* file = current_ptr->findingFile(attrib);
        if (file == nullptr) {
            cout << "file not found" << endl;
            return;
        }
        cout << "The name of file is: " << file->name << endl;
        cout << "The data of file is: " << file->data << endl;
        cout << "The size of file is: " << file->size << endl;
    }

    void find(string filename)
    {

        File* file = current_ptr->findingFile(filename);
        if (file == nullptr) {
            cout << "file not found" << endl;
            return;
        }
        cout << "The name of file is: " << file->name << endl;
        cout << "The data of file is: " << file->data << endl;

    }

    // findf function
    void Findf(string inputString) {
        string name = inputString.substr(0, inputString.find(" "));
        string text = inputString.substr(inputString.find(" ") + 1, inputString.length() - 1);

        File* file = current_ptr->findingFile(name);
        if (file == nullptr) {
            cout << "Could not find the file :(" << endl;
            return;
        }

        if (file->data.find(text) != string::npos) {
            cout << "Found the text :)" << endl;
            cout << "The name of file is: " << file->name << endl;
            cout << "The data of file is: " << file->data << endl;
        }
        else {
            cout << "Text is not found" << endl;
        }
    }

    // Update the CONVERT function to take two arguments
    void CONVERT(const string& oldExtension, const string& newExtension)
    {
        // Validate new extension
        if (isValidExtension(newExtension))
        {
            ConvertExtensionsRecursive(root, oldExtension, newExtension);
        }
        else
        {
            cout << "Invalid new file extension. Conversion aborted." << endl;
        }
    }

    void ConvertExtensionsRecursive(Directory* directories, const string& oldExtension, const string& newExtension)
    {
        for (auto& file : *directories->fileList)
        {
            size_t dotIndex = file.name.find_last_of('.');
            if (dotIndex != string::npos)
            {
                string fileExtension = file.name.substr(dotIndex + 1);
                if (fileExtension == oldExtension)
                {
                    // Modify the file extension
                    file.name = file.name.substr(0, dotIndex) + "." + newExtension;
                    cout << "\tChanged   to " << file.name << "\"" << endl;
                }
            }
        }

        for (auto& subdirectory : *directories->directory)
        {
            ConvertExtensionsRecursive(&subdirectory, oldExtension, newExtension);
        }
    }

    bool isValidExtension(const string& extension)
    {
        if (extension.empty() || extension.size() >= 10 || extension[0] != '.') {
            return false;  // Extension must start with a dot, be non-empty, and less than 10 characters
        }

        return all_of(extension.begin() + 1, extension.end(), [](char c) { return isalnum(c); });
    }



 // findStr function
    void FINDSTR(string txt) {
        for (auto it = current_ptr->fileList->begin(); it != current_ptr->fileList->end(); ++it) {
            if (it->data.find(txt) != string::npos) {
                cout << "The name of file is: " << it->name << endl;
                cout << "The data of file is: " << it->data << endl;
            }
        }
    }

    // format function
    void FORMAT()
    {
        // Clear the fileList and directory in the current directory
        current_ptr->fileList->clear();
        current_ptr->directory->clear();

        cout << "Directory formatted: " << current_ptr->path << endl;
    }

    // utility function to delete a file given specified a path
    void del_File(string filepath) {
        if (filepath.find("V:\\") != string::npos || filepath.find("V:") != string::npos) {
            return del_File(filepath.substr(filepath.find("\\") + 1, filepath.length() - 1));
        }
        else if (filepath.find("\\") != string::npos) {
            string name = filepath.substr(0, filepath.find("\\"));

            for (auto it = current_ptr->directory->begin(); it != current_ptr->directory->end(); ++it) {
                if (it->name == name) {
                    return del_File(filepath.substr(filepath.find("\\") + 1, filepath.length() - 1));
                }
            }
        }
        else {
            for (auto it = current_ptr->fileList->begin(); it != current_ptr->fileList->end(); ++it) {
                if (it->name == filepath) {
                    current_ptr->fileList->erase(it);
                    return;
                }
            }
        }
    }

    // utility function to delete a directory given specified a path
    void deleteDirectory(string filepath) {
        if (filepath.find("V:\\") != string::npos || filepath.find("V:") != string::npos) {
            return deleteDirectory(filepath.substr(filepath.find("\\") + 1, filepath.length() - 1));
        }
        else if (filepath.find("\\") != string::npos) {
            string name = filepath.substr(0, filepath.find("\\"));

            for (auto it = current_ptr->directory->begin(); it != current_ptr->directory->end(); ++it) {
                if (it->name == name) {
                    return deleteDirectory(filepath.substr(filepath.find("\\") + 1, filepath.length() - 1));
                }
            }
        }
        else {
            for (auto it = current_ptr->directory->begin(); it != current_ptr->directory->end(); ++it) {
                if (it->name == filepath) {
                    current_ptr->directory->erase(it);
                    return;
                }
            }
        }
    }

    // utility function to set path after moving directory
    void setingPathAfterMove(Directory* filepath) {//also change this function 
        for (auto it = filepath->directory->begin(); it != filepath->directory->end(); ++it) {
            it->path = filepath->path + it->name + "\\";
            setingPathAfterMove(&(*it));
        }
    }

    // move directory form source to destination or file
    void MOVE(string input) {
        string sourcePath = input.substr(0, input.find(" "));
        string destinationPath = input.substr(input.find(" ") + 1, input.length() - 1);

        if (sourcePath.empty() || destinationPath.empty()) {
            cout << "Invalid syntax" << endl;
            return;
        }

        // check if source exists
        Directory* sourceDir = current_ptr->getDirectoryFromPath(sourcePath);
        File* sourceFile = current_ptr->findingFile(sourcePath);

        if (sourceDir == nullptr && sourceFile == nullptr) {
            cout << "Source not found" << endl;
            return;
        }

        // check if destination exists
        Directory* destinationDir = current_ptr->getDirectoryFromPath(destinationPath);
        File* destinationFile = current_ptr->findingFile(destinationPath);

        if (destinationFile != nullptr) {
            // Show an error message if the destination is a file
            cout << "Cannot move to a file" << endl;
            return;
        }

        // Move directory to destination
        if (sourceDir != nullptr) {
            // Check if the destination directory already contains a directory with the same name
            if (destinationDir->doesDirectoryExist(sourceDir->name)) {
                cout << "Destination directory already contains a directory with the same name" << endl;
                return;
            }

            // Move the directory
            sourceDir->parent_head = destinationDir;
            sourceDir->path = destinationDir->path + sourceDir->name + "\\";
            destinationDir->directory->push_back(*sourceDir);
            setingPathAfterMove(sourceDir);
            deleteDirectory(sourcePath);

            cout << "Directory moved successfully" << endl;
        }
        // Move file to destination
        else if (sourceFile != nullptr) {
            // Check if the destination directory already contains a file with the same name
            if (destinationDir->doesFileExist(sourceFile->name)) {
                cout << "Destination directory already contains a file with the same name" << endl;
                return;
            }

            // Move the file
            destinationDir->fileList->push_back(*sourceFile);
            del_File(sourcePath);

            cout << "File moved successfully" << endl;
        }
    }

    // copy directory form source to destination or file
    void copy(string input) {

        // folder to folder -> it will copy all the files inside this directory to destination
        // file to folder -> it will copy the file to destination if there is no file of it's name
        // file to file -> it will copy the data
        // folder to file -> it will copy and add the data of all the files in the directory

        int fileCount = 0;

        string sourcePath = input.substr(0, input.find(" "));
        string destinationPath = input.substr(input.find(" ") + 1, input.length() - 1);

        if (sourcePath.empty() || destinationPath.empty()) {
            cout << "Invalid Syntax" << endl;
            return;
        }

        // check if source exists
        Directory* sourceDir = current_ptr->getDirectoryFromPath(sourcePath);
        File* sourceFile = current_ptr->findingFile(sourcePath);

        if (sourceDir == nullptr && sourceFile == nullptr) {
            cout << "Source is not found" << endl;
            return;
        }

        // check if destination exists
        Directory* destinationDir = current_ptr->getDirectoryFromPath(destinationPath);
        File* destinationFile = current_ptr->findingFile(destinationPath);

        if (destinationFile == nullptr && destinationDir == nullptr) {
            cout << "Destination is not found" << endl;
            return;
        }

        // now 4 cases

        // folder to folder
        if (sourceDir != nullptr && destinationDir != nullptr) {

            // copy all the files in the directory to destination
            for (auto it = sourceDir->fileList->begin(); it != sourceDir->fileList->end(); ++it) {
                if (destinationDir->doesFileExist(it->name)) {
                    File* temp = destinationDir->findingFile(it->name);
                    temp->data = it->data;
                    temp->size = it->size;
                }
                else {
                    destinationDir->fileList->push_back(copyFile(&(*it)));
                }
                fileCount++;
            }

            cout << "Copied " << fileCount << " items" << endl;
        }
        // file to folder
        else if (sourceFile != nullptr && destinationDir != nullptr) {

            // check if file of same name exists
            if (destinationDir->doesFileExist(sourceFile->name)) {
                File* temp = destinationDir->findingFile(sourceFile->name);
                temp->data = sourceFile->data;
                temp->size = sourceFile->size;
                cout << "1 item copied" << endl;
                return;
            }

            destinationDir->fileList->push_back(copyFile(sourceFile));
            cout << "1 item copied" << endl;
        }
        // file to file
        else if (sourceFile != nullptr && destinationFile != nullptr) {
            destinationFile->data = sourceFile->data;
            destinationFile->size = sourceFile->size;
            cout << "Successfully copied 1 file" << endl;
        }
        // folder to file
        else if (sourceDir != nullptr && destinationFile != nullptr) {

            // copy all the files in the directory to destination
            destinationFile->data = "";
            destinationFile->size = 0;
            for (auto it = sourceDir->fileList->begin(); it != sourceDir->fileList->end(); ++it) {
                destinationFile->data += it->data;
                destinationFile->size += it->size;
                fileCount++;
            }

            cout << "Copied " << fileCount << " items" << endl;
        }
    }


    void VER()
    {
        // Display the version of your program
        cout << "Program Version: 1.0\n";
    }

    // make a new file and copy the data of the file in it
    File copyFile(File* filepath) {
        return File(filepath->name, filepath->data);
    }

    void openEditor(string filename) 
    {
        File* file = current_ptr->findingFile(filename);
        if (file == nullptr) {
            cout << "File not found" << endl;
            return;
        }
        TextEditor editor;
        editor.handleKeyPress(file);
    }

    void printDirectoryStructure(Directory* currentDirectory, int level)
    {
        // Print the current directory
        for (int i = 0; i < level; ++i)
        {
            cout << "   ";
        }

        cout << "[DIR] " << currentDirectory->name << "\n";

        // Recursively print subdirectories
        for (auto it = currentDirectory->directory->begin(); it != currentDirectory->directory->end(); ++it)
        {
            printDirectoryStructure(&(*it), level + 1);
        }

        // Print files in the current directory
        for (auto it = currentDirectory->fileList->begin(); it != currentDirectory->fileList->end(); ++it)
        {
            for (int i = 0; i < level + 1; ++i)
            {
                cout << "   ";
            }

            cout << "[FILE] " << it->name << "\n";
        }
    }
    void TREE()
    {
        // Display the complete directory structure
        cout << "Complete Directory Structure:\n";

        // Start the recursive traversal from the root
        printDirectoryStructure(root, 0);
    }


    void PRINT(string fileName)
    {
        current_ptr->addingFile(fileName, "File content goes here");
        cout << "File added to the print queue: " << fileName << endl;
    }


    void PPRINT(string fileName)
    {
        priorityPrintQueue.push(fileName);
        cout << "File added to the priority print queue: " << fileName << endl;
    }

    void PQUEUE()
    {
        cout << "Priority Based Print Queue:" << endl;
        // Display the current state of the priority print queue
        int count = 1;
        priority_queue<string> tempQueue = priorityPrintQueue;
        while (!tempQueue.empty())
        {
            cout << count++ << ". " << tempQueue.top() << endl;
            tempQueue.pop();
        }
    }

    void QUEUE(const list<File>* fileList)
    {
        cout << "Print Queue with Time Left:" << endl;

        // Create a queue and copy elements from the list to the queue
        queue<File> tempQueue;

        for (const File& file : *fileList)
        {
            tempQueue.push(file);
        }

        // Display the current state of the print queue with time left for each element
        int count = 1;
        while (!tempQueue.empty())
        {
            File file = tempQueue.front();
            cout << count++ << ". " << file.name << " - " << file.size << " bytes" << endl;

            // Calculate and display time left based on file size (adjust as needed)
            time_t currentTime = time(nullptr);
            time_t endTime = currentTime + (file.size / 1024); // Assuming 1 KB per second
            cout << "   Time left: " << difftime(endTime, currentTime) << " seconds" << endl;

            tempQueue.pop();
        }
    }

    void SAVE(string fileName)
    {
        // Find the file in the current directory
        File targetFile = current_ptr->getFileByName(fileName);

        if (!targetFile.name.empty())
        {
            // Save the file content to disk
            ofstream outputFile(fileName);
            if (outputFile.is_open())
            {
                outputFile << targetFile.data;
                outputFile.close();
                cout << "File saved: " << fileName << endl;
            }
            else
            {
                cout << "Unable to save file: " << fileName << endl;
            }
        }
        else
        {
            cout << "File not found: " << fileName << endl;
        }
    }


    void LOADTREE(const string& filename)
    {
        ifstream inputFile(filename);

        if (!inputFile.is_open())
        {
            cout << "Error: Unable to open file " << filename << endl;
            return;
        }

        // Clear the existing tree
        root->directory->clear();
        root->fileList->clear();

        string line;
        while (getline(inputFile, line))
        {
            processTreeLine(line);
        }

        inputFile.close();
        cout << "Tree loaded successfully from " << filename << endl;
    }

    void processTreeLine(const string& line)
    {
        size_t lastSlashPos = line.find_last_of('/');

        // Check if the line represents a directory or a file
        if (lastSlashPos != string::npos)
        {
            // It's a directory
            string dirName = line.substr(0, lastSlashPos);
            Directory* parentDir = current_ptr->getDirectoryFromPath(dirName);

            if (parentDir != nullptr)
            {
                current_ptr = parentDir;
                current_ptr->addingDirectory(line.substr(lastSlashPos + 1), current_ptr);
            }
            else
            {
                cout << "Error: Parent directory not found for " << line << endl;
            }
        }
        else
        {
            // It's a file
            current_ptr->addingFile(line, "File content goes here");
        }
    }



    // input function
    bool input_option()
    {
        cout << current_ptr->path << prompt;
        string input = getInput();

        if (input == "exit") {
            system("cls");
            return false;
        }
        else if (input == "prompt") {//Change this syntax
            prompt = prompt == "> " ? "$ " : "> ";
        }
        else if (input == "format") {
            FORMAT();
        }
        else if (input == "dir") {
            DIR();
        }
        else if (input == "tree") {
            
            TREE();
        }
        else if (input == "cd.." || input == "cd ..") {
            if (current_ptr->parent_head != nullptr) {
                current_ptr = current_ptr->parent_head;
            }
        }
        else if (input == "cd/") {
            current_ptr = root;
        }
        else if (input == "cd.") {
            current_ptr->printingPath();
        }
        else if (input == "help") {
            HelperCommand();
        }
        else if (input.substr(0, 5) == "edit ") {
            openEditor(input.substr(5, input.length() - 1));
            system("cls");
            Header();
        }
        else if (input == "cls") {
            system("cls");
            Header();
        }
        else if (input.substr(0, 3) == "cd ") {

            Directory* temp = current_ptr->getDirectoryFromPath(input.substr(3, input.length() - 1));
            if (temp != nullptr) {
                current_ptr = temp;
            }
            else {
                cout << "Directory not found" << endl;
            }

        }
        else if (input.substr(0, 8) == "findstr ") {
            FINDSTR(input.substr(8, input.length() - 1));
        }
        else if (input.substr(0, 6) == "findf ") {
            Findf(input.substr(6, input.length() - 1));
        }
        else if (input.substr(0, 5) == "copy ") {
            copy(input.substr(5, input.length() - 1));
        }
        else if (input.substr(0, 5) == "move ") {
            move(input.substr(5, input.length() - 1));
        }
        else if (input.substr(0, 7) == "attrib ") {
            ATTRIB(input.substr(7, input.length() - 1));
        }
        else if (input.substr(0, 5) == "mkdir") {
            MKDIR(input.substr(6, input.length() - 1));
        }
        else if (input.substr(0, 6) == "create") {
            createFile(input.substr(7, input.length() - 1));
        }
        else if (input.substr(0, 5) == "rmdir") {
            RMDIR(input.substr(6, input.length() - 1));
        }
        else if (input == "pwd") {
            current_ptr->printingPath();
        }
        else if (input.substr(0, 6) == "rename") {
            string oldName = input.substr(7, input.find(" ", 7) - 7);
            string newName = input.substr(input.find(" ", 7) + 1, input.length() - 1);

            if (oldName.empty() || newName.empty()) {
                cout << "Invalid syntax for rename command" << endl;
            }
            else {
                current_ptr->RENAME(oldName, newName);
            }
        }

        else if (input.substr(0, 7) == "convert")
        {
            // Assuming the syntax is "convert <old_extension> <new_extension>"
            size_t firstSpaceIndex = input.find(' ');
            if (firstSpaceIndex != string::npos)
            {
                string parameters = input.substr(firstSpaceIndex + 1);
                size_t secondSpaceIndex = parameters.find(' ');
                if (secondSpaceIndex != string::npos)
                {
                    string oldExtension = parameters.substr(0, secondSpaceIndex);
                    string newExtension = parameters.substr(secondSpaceIndex + 1);

                    CONVERT(oldExtension, newExtension);
                }
            }
        }

        else if (input.substr(0, 5) == "del") {
            DEL(input.substr(6, input.length() - 1));
        }
        else if (input.substr(0, 5) == "find ") {
            string filename = input.substr(5, input.length() - 1);
            find(filename);
        }

        else if (input.substr(0, 5) == "print")
        {
            PRINT(input.substr(6, input.length() - 1));
        }

        else if (input.substr(0, 5) == "queue")
        {
            QUEUE(current_ptr->fileList);
        }

        else if (input.substr(0, 4) == "save")
        {
            string fileName = splitString(input.substr(5), ' ');
            SAVE(fileName);
        }

        else {
            cout << "Invalid command" << endl;
        }
        return true;
    }

    // get input
    string getInput()
    {
        string input;
        getline(cin, input);
        return input;
    }

    // run function
    void run()
    {
        system("cls");
        Header();
        while (input_option())
            ;
    }

    // help function
    void HelperCommand()
    {
        SetConsoleColor(FOREGROUND_GREEN);
        cout << "attrib <file name> - Displays file attributes." << endl;
        SetConsoleColor(FOREGROUND_RED);
        cout << "cd <directory name> - Displays the name of or changes the current directory." << endl;
        SetConsoleColor(FOREGROUND_BLUE);
        cout << "cd. - Prints working directory (current directory)." << endl;
        SetConsoleColor(FOREGROUND_INTENSITY);
        cout << "cd.. - Changes directory to the previous directory." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
        cout << "cd\\ - Changes directory to the root directory (V:\\>)." << endl;
        SetConsoleColor(FOREGROUND_GREEN);
        cout << "convert -<old extension> <.new extension> " << endl;
        SetConsoleColor(FOREGROUND_RED);
        cout << "copy <source> <destination> - Copies one file in the current directory to another location." << endl;
        SetConsoleColor(FOREGROUND_BLUE);
        cout << "create <file name> - Creates a file with the provided name and allows user to enter contents." << endl;
        SetConsoleColor(FOREGROUND_INTENSITY);
        cout << "del <file name> - Deletes a file with the provided name." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
        cout << "dir - Displays a list of files and subdirectories in the current directory." << endl;
        SetConsoleColor(FOREGROUND_GREEN);
        cout << "edit <file name> - Opens a file, allows user to edit, and saves the contents of the file." << endl;
        SetConsoleColor(FOREGROUND_RED);
        cout << "exit - Quits the program." << endl;
        SetConsoleColor(FOREGROUND_BLUE);
        cout << "find <file name> - Searches for a file in the current virtual directory." << endl;
        SetConsoleColor(FOREGROUND_INTENSITY);
        cout << "findf <file name> <text> - Searches for a text string in the currently open file or a specified file." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
        cout << "findstr <text> - Searches for strings in all files of the current virtual directory." << endl;
        SetConsoleColor(FOREGROUND_GREEN);
        cout << "format - Formats the current virtual directory, empties the current directory and all subdirectories." << endl;
        SetConsoleColor(FOREGROUND_RED);
        cout << "help - Provides Help information for all commands." << endl;
        SetConsoleColor(FOREGROUND_BLUE);
        cout << "loadtree - Load a given tree in the tree structure from a file named tree.txt." << endl;
        SetConsoleColor(FOREGROUND_INTENSITY);
        cout << "mkdir <directory name> - Creates a virtual directory." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
        cout << "move <source> <destination> - Moves one file from one directory to another." << endl;
        SetConsoleColor(FOREGROUND_GREEN);
        cout << "pprint <file name> - Adds a text file to the priority-based print queue and displays the current priority queue." << endl;
        SetConsoleColor(FOREGROUND_RED);
        cout << "prompt - Changes the Windows command prompt (e.g., from V:\\> to V$)." << endl;
        SetConsoleColor(FOREGROUND_BLUE);
        cout << "PRINT <file name> - Adds a text file to the print queue and displays the current queue." << endl;
        SetConsoleColor(FOREGROUND_INTENSITY);
        cout << "PQUEUE - Shows the current state of the priority-based print queue with time left for each element." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
        cout << "pwd - Prints the working directory." << endl;
        SetConsoleColor(FOREGROUND_GREEN);
        cout << "queue - Shows the current state of the print queue with time left for each element." << endl;
        SetConsoleColor(FOREGROUND_RED);
        cout << "rename <old name> <new name> - Renames a file." << endl;
        SetConsoleColor(FOREGROUND_BLUE);
        cout << "rmdir <directory name> - Removes a directory along with its contents." << endl;
        SetConsoleColor(FOREGROUND_INTENSITY);
        cout << "save - Saves the currently open file to disk." << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
        cout << "tree - Displays the complete directory structure." << endl;
        SetConsoleColor(FOREGROUND_GREEN);
        cout << "ver - Displays the version of your program." << endl;
        ResetConsoleColor();
    }

    void SetConsoleColor(int color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    // Reset text color to default
    void ResetConsoleColor()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    }
    void Header() {
        cout << "/******************************************************************************" << endl;
        cout << " *                      D O S S   S H E L L   -   P R O J E C T               *" << endl;
        cout << " *                                                                            *" << endl;
        cout << " * Course Code:     CS-153 & CS-143                                           *" << endl;
        cout << " * Academic Year:   2022                                                      *" << endl;
        cout << " * Author:          Ayesha and Sami                                           *" << endl;
        cout << " *                                                                            *" << endl;
        cout << " * Description:     Welcome to the DOSS Shell, a sophisticated command-line   *" << endl;
        cout << " *                  interface designed for CS-153 & CS-143 coursework. Dive   *" << endl;
        cout << " *                  into a seamless user experience with powerful commands    *" << endl;
        cout << " *                  and intuitive functionalities.                            *" << endl;
        cout << " *****************************************************************************/" << endl;
    }
};


int main() {
    
    TreeNode tree;

    tree.run();
    return 0;
}