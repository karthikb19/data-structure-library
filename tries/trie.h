#pragma once

#include <string>
#include <array>
#include <memory>
#include <vector>

// trie node
struct TrieNode {
    bool is_word = false;
    std::array<std::unique_ptr<TrieNode>, 26> children;
};

class Trie {
private:
    std::unique_ptr<TrieNode> root;
public:

    Trie() : root(std::make_unique<TrieNode>()){}

    bool insert(const std::string& s);
    bool contains(const std::string& s) const;
    std::vector<std::string> starts_with(const std::string& s) const; 
    bool remove(const std::string& s);
};
