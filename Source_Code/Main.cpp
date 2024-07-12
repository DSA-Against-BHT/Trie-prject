#include <iostream>
#include <string>
#include "Trie_Structure.hpp"

int main (){
    Trie_Node* Root = new Trie_Node();
    Word_Generate(Root, "a c e p");
    return 0;
}