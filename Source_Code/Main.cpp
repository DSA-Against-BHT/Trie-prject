#include <iostream>
#include <string>
#include "Trie_Structure.hpp"

int main (){
    Trie_Node* root = new Trie_Node();
    wordGenerate(root, "a c e p");
    return 0;
}