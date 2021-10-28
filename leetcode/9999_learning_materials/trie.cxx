struct TrieNode {
    vector<TrieNode*> children;
    const char *word;  // sentinal of end of a word, also points to that word

    TrieNode() : children(26), word(nullptr) {}  // for lower case letters only
    ~TrieNode() {
        for(TrieNode *child : children)
            delete child;
    }
};

struct Trie {
    TrieNode *root;  // dummy root
    
    Trie() : root(new TrieNode()) {}
    ~Trie() {
        delete root;
    }
    
    void add(const string &s) {
        TrieNode *cur = root;
        for(char c : s) {
            auto &next = cur->children[c-'a'];
            if(!next)
                next = new TrieNode();
            cur = next;
        }
        cur->word = s.c_str();  // mark as a word
    }
    
    bool find(const string &s) {
        TrieNode *cur = root;
        for(char c : s) {
            cur = cur->children[c-'a'];
            if(!cur)
                return false;
        }
        return cur->word!=nullptr;
    }
};
