#include<iostream>
#include<list>
#include<math.h>
#include<vector>
using namespace std;

vector<int> vec(10, -1);
vector<list<int>> vectr(10);
vector<int> collision(10, 0);

int hashFunction(int key) {
    return key % 10;
}

void insertUsingQuadraticProbing(int value) {
    bool flag = true;
    int i = 0;
    int index = hashFunction(value);
    while (flag) {
        if (vec[index] == -1) {
            vec[index] = value;
            flag = false;
        }
        else {
            collision[index]++;
            index = hashFunction(value + pow(collision[index], 2));
        }
    }
}

void insertUsingChaining(int value) {
    int index = hashFunction(value);
    vectr[index].push_back(value);
}

void insertUsingLinearProbing(int value) {
    bool flag = true;
    int i = 0;
    while (flag) {
        int index = hashFunction(value + i);
        if (vec[index] == -1) {
            vec[index] = value;
            flag = false;
        }
        else {
            i++;
        }
    }
}

bool searchUsingLinearProbing(int value) {
    int i = 0;
    while (true) {
        if (i == vec.size() - 1)
            return false;
        int index = hashFunction(value + i);
        if (vec[index] == value) {
            return true;
        }
        else if (vec[index] == -1) {
            return false;
        }
        else {
            i++;
        }
    }
}

bool searchUsingQuadraticProbing(int value) {
    int i = 0;
    int index = hashFunction(value);
    while (true) {
        if (i == vec.size() - 1)
            return false;
        if (vec[index] == value) {
            return true;
        }
        else {
            collision[index]++;
            i++;
            index = hashFunction(value + pow(collision[index], 2));
        }
    }
}

bool searchUsingChaining(int value) {
    int index = hashFunction(value);
    for (auto num : vectr[index]) {
        if (num == value)
            return true;
    }
    return false;
}

int main() {
    // Chaining Method
    insertUsingChaining(22);
    insertUsingChaining(34);
    insertUsingChaining(52);
    insertUsingChaining(29);
    insertUsingChaining(21);
    insertUsingChaining(82);
    insertUsingChaining(11);
    insertUsingChaining(24);
    insertUsingChaining(26);

    cout << "Chaining Method:" << endl;
    for (int i = 0; i < vectr.size(); i++) {
        cout << "Index " << i << ": ";
        for (auto j : vectr[i])
            cout << j << "  ";
        cout << endl;
    }
    cout << "Search result for 34: " << searchUsingChaining(34) << endl;
    cout << "Search result for 15: " << searchUsingChaining(15) << endl;
    cout << "Search result for 82: " << searchUsingChaining(82) << endl;
    cout << "Search result for 42: " << searchUsingChaining(42) << endl;

    // Linear Probing
    vec.assign(10, -1); // Reset the vector for Linear Probing
    insertUsingLinearProbing(22);
    insertUsingLinearProbing(59);
    insertUsingLinearProbing(11);
    insertUsingLinearProbing(44);
    insertUsingLinearProbing(55);
    insertUsingLinearProbing(26);
    insertUsingLinearProbing(25);
    insertUsingLinearProbing(99);
    insertUsingLinearProbing(78);
    insertUsingLinearProbing(33);

    cout << "\nLinear Probing:" << endl;
    for (int i : vec) {
        cout << i << "  ";
    }
    cout << endl;
    cout << "Search result for 11: " << searchUsingLinearProbing(11) << endl;
    cout << "Search result for 79: " << searchUsingLinearProbing(79) << endl;
    cout << "Search result for 25: " << searchUsingLinearProbing(25) << endl;
    cout << "Search result for 17: " << searchUsingLinearProbing(17) << endl;

    // Quadratic Probing
    vec.assign(10, -1); // Reset the vector for Quadratic Probing
    collision.assign(10, 0); // Reset the collision vector
    insertUsingQuadraticProbing(22);
    insertUsingQuadraticProbing(59);
    insertUsingQuadraticProbing(11);
    insertUsingQuadraticProbing(44);
    insertUsingQuadraticProbing(55);
    insertUsingQuadraticProbing(26);
    insertUsingQuadraticProbing(25);
    insertUsingQuadraticProbing(99);
    insertUsingQuadraticProbing(78);
    insertUsingQuadraticProbing(33);

    cout << "\nQuadratic Probing:" << endl;
    for (int i : vec) {
        cout << i << "  ";
    }
    cout << endl;
    cout << "Search result for 11: " << searchUsingQuadraticProbing(11) << endl;
    cout << "Search result for 79: " << searchUsingQuadraticProbing(79) << endl;
    cout << "Search result for 25: " << searchUsingQuadraticProbing(25) << endl;
    cout << "Search result for 17: " << searchUsingQuadraticProbing(17) << endl;

    return 0;
}



// class Solution {
// 	vector<string> res;
// 	vector<int> fre;
// public:
// 	vector<string> findRepeatedDnaSequences(string s) {
// 		string str = "";
// 		for (int i = 0;i < s.size() - 10;i++) {
// 			bool flag = true;
// 			str = s.substr(i, 10);
// 			for (int i = 0;i < res.size();i++) {
// 				if (str == res[i]) {
// 					fre[i]++;
// 					flag = false;
// 				}
// 			}
// 			if (flag) {
// 				res.push_back(str);
// 				fre.push_back(1);
// 			}
// 		}
// 		vector<string> result;
// 		for (int i = 0;i < res.size();i++) {
// 			if (fre[i] > 1) {
// 				result.push_back(res[i]);
// 			}
// 		}
// 		return result;
// 	}
// };

// class Solution1 {
// 	vector<vector<string>> ans;
// public:
// 	vector<vector<string>> groupAnagrams(vector<string>& strs) {
// 		for (int i = 0;i < strs.size();i++) {
// 			for (int j = 0;j < ans.size();j++) {
// 				for (int k = 0;k < ans[j].size();k++) {
// 					string str = strs[i];
// 					string str1 = ans[j][k];
// 					if (str.size() == str1.size()) {
// 						vector<char> res;
// 						int count = 0;
// 						for (char c : str) {
// 							for (char d : str1) {
// 								if (c == d) {
// 									count++;
// 								}
// 							}
// 						}
// 						if (count == str.size()) {
// 							ans[j].push_back(str);
// 						}
// 					}
// 				}
// 			}
// 		}
// 		return ans;
// 	}
// };