#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Trie {
    Trie* next[26];
    bool isEnd = false;

    Trie() {
        fill(next, next + 26, nullptr);
    }

    ~Trie() {
        for (int i = 0; i < 26; ++i) {
            if (next[i] != nullptr) {
                delete next[i];
            }
        }
    }

    void insert(const string& word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            if (node->next[index] == nullptr) {
                node->next[index] = new Trie();
            }
            node = node->next[index];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        Trie* node = this;
        for (char c : word) {
            int index = c - 'a';
            if (node->next[index] == nullptr) {
                return false;
            }
            node = node->next[index];
        }
        return node->isEnd;
    }

    bool startsWith(const string& prefix) {
        Trie* node = this;
        for (char c : prefix) {
            int index = c - 'a';
            if (node->next[index] == nullptr) {
                return false;
            }
            node = node->next[index];
        }
        return true;
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    cout << trie.search("apple") << endl;   // Output: 1 (true)
    cout << trie.search("app") << endl;     // Output: 0 (false)
    cout << trie.startsWith("app") << endl; // Output: 1 (true)
    trie.insert("app");
    cout << trie.search("app") << endl;     // Output: 1 (true)
    return 0;
}