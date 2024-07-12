#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include "Trie_Structure.hpp"

void Insertion(Trie_Node* &Root, std::string str){
    Trie_Node* Cur = Root;
    for(int i = 0; i < str.size(); i ++){
        if(Cur->Child[str[i] - 'a'] == NULL){
            Cur->Child[str[i] - 'a'] = new Trie_Node();
        }
        Cur = Cur->Child[str[i] - 'a'];
    }
    Cur->End = true;
}

bool Search(Trie_Node* Root, std::string key){
    Trie_Node* Cur = Root;
    for(int i = 0; i < key.size(); i ++){
        if(Cur->Child[key[i] - 'a'] == NULL) return false;
        Cur = Cur->Child[key[i] - 'a'];
    }
    return (Cur->End == true);
}

Trie_Node* Delete_Recursion(Trie_Node* Root, std::string str, int count){
    if(!Root) return NULL;
    //Stopping condition:
    if(count == str.size()){
        if(Root->End) Root->End = false;
        bool check = true;
        for(int i = 0; i < 26; i ++){
            if(Root->Child[i] != NULL){
                check = false;
                break;
            }
        }
        if(check){
            delete Root;
            Root = NULL;
        }
        return Root;
    }

    Root->Child[str[count] - 'a'] = Delete_Recursion(Root->Child[str[count] - 'a'], str, count + 1);
    bool check = true;
    for(int i = 0; i < 26; i ++){
        if(Root->Child[i] != NULL){
            check = false;
            break;
        }
    }
    if(check && !Root->End){
        delete Root;
        Root = NULL;
    }
    return Root;
}

void Deletion(Trie_Node* &Root, std::string str){
    int count = 0;
    Root = Delete_Recursion(Root, str, count);
}

void Search_Prefix(Trie_Node* Root, std::string prefix){
    Trie_Node* Cur = Root;
    for(int i = 0; i < prefix.size(); i ++){
        if(Cur->Child[prefix[i] - 'a'] == NULL) return;
        Cur = Cur->Child[prefix[i] - 'a'];
    }
    Display(Cur, prefix);
}

void Display(Trie_Node* Root, std::string str){
    if(Root->End == true){
        std::cout << str << std::endl;
    }

    for(int i = 0; i < 26; i ++){
        if(Root->Child[i] != NULL){
            char c = i + 'a';
            Display(Root->Child[i], str + c);
        } 
    }
}

void Read_Data(std::string File_Name, Trie_Node* &Root){
    std::ifstream fIn;
    fIn.open(File_Name.c_str());
    if(!fIn.is_open()){
        std::cout << "Can not open Dic.txt file";
        return;
    }
    while(!fIn.eof()){
        std::string str;
        getline(fIn, str);
        Insertion(Root, str);
    }
    fIn.close();
}

void Word_Generate(Trie_Node* &Root, std::string Input){
    Read_Data("Dic.txt", Root);
    std::string A; //String for containing character from input since the input contains spaces
    for(int i = 0; i < Input.size(); i ++){
        if(Input[i] != ' ') A.push_back(Input[i]);
    }
    std::vector<std::string> res; //Vector for containing result
    bool B[A.size()]; //Array for managing the appearances of characters from Input
    for(int i = 0; i < A.size(); i ++){
        B[i] = false;
    }
    std::string str = ""; //String for the Recursion
    Word_Generate_Recursion(Root, A, res, str, B);

    //Output
    std::cout << res.size() << std::endl;
    for(int i = 0; i < res.size(); i ++){
        std::cout << res[i] << std::endl;
    }
}

void Word_Generate_Recursion(Trie_Node* Root, const std::string& A, std::vector<std::string> &res, std::string str, bool B[]){
    //The recursion stops when the Root->End is true and str.size() >= 3
    if(Root->End && str.size() >= 3){
        res.push_back(str);
    }

    for(int i = 0; i < A.size(); i ++){
        if(!B[i] && Root->Child[A[i] - 'a'] != NULL){
            B[i] = true;
            str.push_back(A[i]);
            Word_Generate_Recursion(Root->Child[A[i] - 'a'], A, res, str, B);
            //End then pop the last character
            str.pop_back();
            B[i] = false;
        }
    }
}