#include "trie.h"
#include <iostream>

int main() {
    Trie trie;

    // 1) Insert some words
    std::vector<std::string> words = {"apple", "app", "banana", "band", "bandana", "band"};
    std::cout << "Inserting words:\n";
    for (const auto &w : words) {
        bool ok = trie.insert(w);
        std::cout << "  \"" << w << "\": "
                  << (ok ? "inserted" : "duplicate/invalid") << "\n";
    }

    // 2) Test contains()
    std::cout << "\nTesting contains():\n";
    std::vector<std::string> queries = {"app", "apple", "apricot", "band", "ban"};
    for (const auto &q : queries) {
        std::cout << "  contains(\"" << q << "\") = "
                  << (trie.contains(q) ? "true" : "false") << "\n";
    }

    // 3) Test starts_with()
    std::cout << "\nWords starting with \"app\":\n";
    auto results = trie.starts_with("app");
    for (const auto &w : results) {
        std::cout << "  " << w << "\n";
    }

    // 4) Remove “app” and re-test
    std::cout << "\nRemoving \"app\":\n";
    bool removed = trie.remove("app");
    std::cout << "  remove(\"app\") = " << (removed ? "true" : "false") << "\n";
    std::cout << "  contains(\"app\") = "
              << (trie.contains("app") ? "true" : "false") << "\n";
    std::cout << "Words starting with \"app\" now:\n";
    results = trie.starts_with("app");
    for (const auto &w : results) {
        std::cout << "  " << w << "\n";
    }

    // 5) Remove “banana”
    std::cout << "\nRemoving \"banana\":\n";
    removed = trie.remove("banana");
    std::cout << "  remove(\"banana\") = " << (removed ? "true" : "false") << "\n";
    std::cout << "  contains(\"banana\") = "
              << (trie.contains("banana") ? "true" : "false") << "\n";

    return 0;
}

