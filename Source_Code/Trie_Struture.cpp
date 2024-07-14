#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "Trie_Structure.hpp"

using namespace std;

void inputConsole(string input) {
    cout << "Input list of letters: ";
    getline(cin, input);
}

void insertion(Trie_Node* &root, string str) {
    Trie_Node* cur = root;
    for (int i = 0; i < str.size(); i++) {
        if (cur->child[str[i] - 'a'] == NULL) {
            cur->child[str[i] - 'a'] = new Trie_Node();
        }
        cur = cur->child[str[i] - 'a'];
    }
    cur->end = true;
}

bool search(Trie_Node* root, string key) {
    Trie_Node* cur = root;
    for (int i = 0; i < key.size(); i++) {
        if (cur->child[key[i] - 'a'] == NULL) return false;
        cur = cur->child[key[i] - 'a'];
    }
    return (cur->end == true);
}

// Helper function to check if a node has any children
bool hasChildren(Trie_Node* node) {
    for (int i = 0; i < 26; ++i) {
        if (node->child[i] != nullptr) return true;
    }
    return false;
}

Trie_Node* deleteRecursion(Trie_Node* root, const string& str, long long count) {
    if (!root) return nullptr;

    if (count == str.size()) {
        if (root->end) root->end = false;

        if (!hasChildren(root)) {
            delete root;
            return nullptr;
        }
        return root;
    }

    root->child[str[count] - 'a'] = deleteRecursion(root->child[str[count] - 'a'], str, count + 1);

    if (!hasChildren(root) && !root->end) {
        delete root;
        return nullptr;
    }
    return root;
}

void deletion(Trie_Node* &root, const string& str) {
    long long count = 0;
    root = deleteRecursion(root, str, count);
}

void display(Trie_Node* root, string str) {
    if (root->end == true) cout << str << "\n";

    for (int i = 0; i < 26; i++) {
        if (root->child[i] != NULL) {
            char c = i + 'a';
            display(root->child[i], str + c);
        } 
    }
}

void searchPrefix(Trie_Node* root, string prefix) {
    Trie_Node* cur = root;
    for (int i = 0; i < prefix.size(); i++) {
        if (cur->child[prefix[i] - 'a'] == NULL) return;
        cur = cur->child[prefix[i] - 'a'];
    }
    display(cur, prefix);
}

void readData(string file_name, Trie_Node* &root) {
    ifstream fIn;
    fIn.open(file_name.c_str());
    if (!fIn.is_open()) {
        cout << "Can not open Dic.txt file!";
        return;
    }
    while(!fIn.eof()) {
        string str;
        getline(fIn, str);
        insertion(root, str);
    }
    fIn.close();
}

void wordGenerateRecursion(Trie_Node* root, const string& A, vector<string> &res, string& str, bool B[]) {
    if (root->end && str.size() >= 3) res.push_back(str);
    
    for (int i = 0; i < A.size(); ++i) {
        if (!B[A[i] - 'a'] && root->child[A[i] - 'a'] != nullptr) {
            B[A[i] - 'a'] = true;
            str.push_back(A[i]);
            wordGenerateRecursion(root->child[A[i] - 'a'], A, res, str, B);
            str.pop_back();
            B[A[i] - 'a'] = false;
        }
    }
}

void wordGenerate(Trie_Node* &root, string input) {
    readData("Dic.txt", root);
    
    string A;
    for (char c : input)
        if (c != ' ') A.push_back(c);
    
    // Sort and remove duplicates
    sort(A.begin(), A.end());
    A.erase(unique(A.begin(), A.end()), A.end());
    
    vector<string> res;
    bool B[26] = {0};
    
    string str = "";
    wordGenerateRecursion(root, A, res, str, B);
    
    // Output
    cout << res.size() << "\n";
    for (const string& word : res)
        cout << word << "\n";
}