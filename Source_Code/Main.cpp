#include <iostream>
#include <string>
#include "Trie_Structure.hpp"

int main() {
    Trie_Node* root = new Trie_Node();
    string input;
    inputConsole(input);
    wordGenerate(root, input);
    return 0;
}