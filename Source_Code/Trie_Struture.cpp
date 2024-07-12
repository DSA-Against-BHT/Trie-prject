#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "Trie_Structure.hpp"

using namespace std;

void insertion(Trie_Node* &root, string str){
    Trie_Node* cur = root;
    for(int i = 0; i < str.size(); i++){
        if(cur->child[str[i] - 'a'] == NULL){
            cur->child[str[i] - 'a'] = new Trie_Node();
        }
        cur = cur->child[str[i] - 'a'];
    }
    cur->end = true;
}

bool search(Trie_Node* root, string key){
    Trie_Node* cur = root;
    for(int i = 0; i < key.size(); i++){
        if(cur->child[key[i] - 'a'] == NULL) return false;
        cur = cur->child[key[i] - 'a'];
    }
    return (cur->end == true);
}

Trie_Node* deleteRecursion(Trie_Node* root, string str, long long count){
    if(!root) return NULL;
    //Stopping condition:
    if(count == str.size()){
        if(root->end) root->end = false;
        bool check = true;
        for(int i = 0; i < 26; i++){
            if(root->child[i] != NULL){
                check = false;
                break;
            }
        }
        if(check){
            delete root;
            root = NULL;
        }
        return root;
    }

    root->child[str[count] - 'a'] = deleteRecursion(root->child[str[count] - 'a'], str, count + 1);
    bool check = true;
    for(int i = 0; i < 26; i++){
        if(root->child[i] != NULL){
            check = false;
            break;
        }
    }
    if(check && !root->end){
        delete root;
        root = NULL;
    }
    return root;
}

void deletion(Trie_Node* &root, string str){
    int count = 0;
    root = deleteRecursion(root, str, count);
}

void searchPrefix(Trie_Node* root, string prefix){
    Trie_Node* cur = root;
    for(int i = 0; i < prefix.size(); i++){
        if(cur->child[prefix[i] - 'a'] == NULL) return;
        cur = cur->child[prefix[i] - 'a'];
    }
    display(cur, prefix);
}

void display(Trie_Node* root, string str){
    if(root->end == true) cout << str << "\n";

    for(int i = 0; i < 26; i++){
        if(root->child[i] != NULL){
            char c = i + 'a';
            display(root->child[i], str + c);
        } 
    }
}

void readData(string file_name, Trie_Node* &root){
    ifstream fIn;
    fIn.open(file_name.c_str());
    if(!fIn.is_open()){
        cout << "Can not open Dic.txt file!";
        return;
    }
    while(!fIn.eof()){
        string str;
        getline(fIn, str);
        insertion(root, str);
    }
    fIn.close();
}

void wordGenerate(Trie_Node* &root, string input){
    readData("Dic.txt", root);
    string A; //String for containing character from input since the input contains spaces
    for(int i = 0; i < input.size(); i++){
        if(input[i] != ' ') A.push_back(input[i]);
    }
    vector<string> res; //Vector for containing result
    bool B[A.size()]; //Array for managing the appearances of characters from input
    for(int i = 0; i < A.size(); i++){
        B[i] = false;
    }
    string str = ""; //String for the Recursion
    wordGenerateRecursion(root, A, res, str, B);

    //Output
    cout << res.size() << "\n";
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << "\n";
    }
}

void wordGenerateRecursion(Trie_Node* root, const string& A, vector<string> &res, string str, bool B[]){
    //The recursion stops when the root->end is true and str.size() >= 3
    if(root->end && str.size() >= 3) res.push_back(str);
    
    for(int i = 0; i < A.size(); i++){
        if(!B[i] && root->child[A[i] - 'a'] != NULL){
            B[i] = true;
            str.push_back(A[i]);
            wordGenerateRecursion(root->child[A[i] - 'a'], A, res, str, B);
            //end then pop the last character
            str.pop_back();
            B[i] = false;
        }
    }
}