#include "trie.h"

bool check_word(const std::string& s){
    if(s.empty()){
        return false;
    }

    int len = int(s.size());
    for(int i = 0; i < len; ++i){
        if(s[i] - 'a' < 0 || s[i] - 'a' >= 26){
            return false;
        }
    }
    return true;
}

bool Trie::insert(const std::string& s){
    if(!check_word(s)){ return false; }

    int len = int(s.size());
    TrieNode* head = root.get();
    for(int i = 0; i < len; ++i){
        int index = s[i] - 'a';
        if(!head->children[index]){
            head->children[index] = std::make_unique<TrieNode>(); 
        }
        head = head->children[index].get();
    }
    if(head->is_word){
        return false;
    }
    head->is_word = true;
    return true;
}

bool Trie::contains(const std::string& s) const {
    if(!check_word(s)){ return false; }

    int len = int(s.size());
    TrieNode* head = root.get();
    for(int i = 0; i < len; ++i){
        int index = s[i] - 'a';
        if(!head->children[index]){
            return false;
        }   
        head = head->children[index].get();
    }
    return (head->is_word ? true : false);
}

void dfs_starts_with(TrieNode* head, std::string& s, std::vector<std::string>& words){
    if(head->is_word){
        words.push_back(s);
    }
    for(int i = 0; i < 26; ++i){
        if(head->children[i]){
            s.push_back('a'+i);
            TrieNode* child = head->children[i].get();
            dfs_starts_with(child, s, words);
            s.pop_back();
        }
    }
}

std::vector<std::string> Trie::starts_with(const std::string& s) const{
    if(!check_word(s)) { return {}; } 

    int len = int(s.size());
    TrieNode* head = root.get();
    for(int i = 0; i < len; ++i){
        int index = s[i] - 'a';
        if(!head->children[index]){
            return {};
        }
        head = head->children[index].get();
    }
    std::vector<std::string> words;
    std::string buffer = s;
    dfs_starts_with(head, buffer, words);
    return words;
}

bool dfs_remove(const std::string& s, int idx, std::unique_ptr<TrieNode>& node){
    int len = int(s.size());
    if(idx < len){
        int index = s[idx] - 'a';
        if(node->children[index]){
            auto& child = node->children[index];
            if(dfs_remove(s, idx+1, child)){
                child.reset();
            }
        }
    } else{
        node->is_word = false;
    }

    if(node->is_word){
        return false;
    }
    bool can_remove = true;
    for(int i = 0; i < 26; ++i){
        if(node->children[i]){
            can_remove = false;
        }
    }
    return can_remove; 
}

bool Trie::remove(const std::string& s){
    if(!check_word(s) || !contains(s)) { return false; }
    dfs_remove(s, 0, root);
    return true;
}
