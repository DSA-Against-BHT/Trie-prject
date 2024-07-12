#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#pragma once

struct Trie_Node{
    //Pointer to the 26 letters from the alphabet
    Trie_Node* Child[26];
    //The boolean variable marks the end of the word
    bool End;
    //Constructor
    Trie_Node(){
        End = false;
        for(int i = 0; i < 26; i ++){
            Child[i] = NULL;
        }
    }
};

//Insert a new word to Trie Structure
void Insertion(Trie_Node* &Root, std::string str);

//Search a word in Trie Structure
bool Search(Trie_Node* Root, std::string key);

//Delete a word from Trie Structure
Trie_Node* Delete_Recursion(Trie_Node* Root, std::string str, int count);
void Deletion(Trie_Node* &Root, std::string str);

//Search for words with the same Prefix
void Search_Prefix(Trie_Node* Root, std::string prefix);

//Display the data from trie
void Display(Trie_Node* Root, std::string str);

//Read data from Dic.txt
void Read_Data(std::string File_Name, Trie_Node* &Root);

//Function for the Project Problem
void Word_Generate(Trie_Node* &Root, std::string Input);
void Word_Generate_Recursion(Trie_Node* Root, const std::string& A, std::vector<std::string> &res, std::string str, bool B[]);