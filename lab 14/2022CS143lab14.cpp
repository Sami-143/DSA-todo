#include<iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

//class Solution {
//public:
//    vector<vector<string>> groupAnagrams(vector<string>& strs) {
//        unordered_map<string, vector<string>> mp;
//
//        for (auto x : strs) {
//            string word = x;
//            sort(word.begin(), word.end());
//            mp[word].push_back(x);
//        }
//
//        vector<vector<string>> ans;
//        for (auto x : mp) {
//            ans.push_back(x.second);
//        }
//        return ans;
//    }
//};
//
//int main() {
//    Solution solution;
//
//    vector<string> input = { "eat", "tea", "tan", "ate", "nat", "bat" };
//    vector<vector<string>> result = solution.groupAnagrams(input);
//
//    cout << "Grouped Anagrams:\n";
//    for (const auto& group : result) {
//        cout << "[ ";
//        for (const string& word : group) {
//            cout << word << " ";
//        }
//        cout << "]\n";
//    }
//
//    return 0;
//}

//leetcode 2
//vector<string> findRepeatedDnaSequences(string s) {
//    vector<string> result;
//    unordered_set<string> seen;
//    unordered_set<string> repeated;
//
//    // Iterate through the DNA sequence 
//    for (int i = 0; i <= s.length() - 10; ++i) {
//        string substring = s.substr(i, 10);
//
//        if (seen.count(substring) > 0) {
//            repeated.insert(substring);
//        }
//        else {
//            seen.insert(substring);
//        }
//    }
//    // Converting the repeated set to a vector 
//    result.assign(repeated.begin(), repeated.end());
//
//    return result;
//}
//
//int main() {
//    string dnaSequence = "AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT";
//    vector<string> result = findRepeatedDnaSequences(dnaSequence);
//
//    cout << "Repeated 10-letter sequences: ";
//    for (const string& sequence : result) {
//        cout << sequence << " ";
//    }
//
//    return 0;
//}