#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Trie_Node{
    // Pointer to the 26 letters from the alphabet
    Trie_Node* child[26];
    // The boolean variable marks the end of the word
    bool end;
    // Constructor
    Trie_Node(){
        end = false;
        for(int i = 0; i < 26; i++){
            child[i] = NULL;
        }
    }
};

// Function to input data from console
void inputConsole(string &input);

// Insert a new word to Trie Structure
void insertion(Trie_Node* &root, string str);

// Search a word in Trie Structure
bool search(Trie_Node* root, string key);

// Delete a word from Trie Structure
bool hasChildren(Trie_Node* node);
Trie_Node* deleteRecursion(Trie_Node* root, const string& str, long long count);
void deletion(Trie_Node* &root, const string& str);

// Search for words with the same Prefix
void searchPrefix(Trie_Node* root, string prefix);

// Display the data from trie
void display(Trie_Node* root, string str);

// Read data from Dic.txt
void readData(string file_name, Trie_Node* &root);

// Function for the Project Problem
void wordGenerate(Trie_Node* &root, string input);
void wordGenerateRecursion(Trie_Node* root, const string& A, vector<string> &res, string& str, bool B[]);