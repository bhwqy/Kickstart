#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    map<char, TrieNode*> m;
    bool isword;
    int count;
    int depth;

    TrieNode() : isword(false), count(0), depth(0) {}
    TrieNode(int d) : isword(false), count(1), depth(d + 1) {}
    ~TrieNode() {
        for (auto pa : m)
            delete pa.second;
    }
};

class Trie {
public:
    Trie() : root(new TrieNode) {}

    ~Trie() {
        delete root;
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (auto c : word) {
            if (node->m.find(c) != node->m.end()) {
                node = node->m[c];
                node->count++;
            }
            else {
                TrieNode* tmp = new TrieNode(node->depth);
                node->m.insert(make_pair(c, tmp));
                node = tmp;
            }
        }
        node->isword = true;
    }

    TrieNode* root;
};

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int n, k;
        cin >> n >> k;
        Trie trie;
        for (int i = 0; i < n; ++i) {
            string tmp;
            cin >> tmp;
            trie.insert(tmp);
        }
        int res = 0;
        queue<TrieNode*> q;
        q.push(trie.root);
        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            res += node->count / k;
            for (auto pa : node->m)
                q.push(pa.second);
        }
        cout << "Case #" << cse << ": " << res << "\n";
    }
    return 0;
}
