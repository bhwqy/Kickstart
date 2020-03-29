#include <bits/stdc++.h>
using namespace std;

class SegData {
public:
    SegData() : val(0), lazy(0) {}
    int val, lazy;
};

class SegNode {
public:
    static int MAXTYPE;

    SegNode(int l, int r) : arrStart(l), arrEnd(r), left(nullptr), right(nullptr)
    {
        if (l != r) {
            int mid = (l + r) >> 1;
            left = new SegNode(l, mid);
            right = new SegNode(mid + 1, r);
        }
    }
    ~SegNode() {
        delete left;
        delete right;
    }

    SegNode(const SegNode&) = delete;
    SegNode(SegNode&&) = delete;
    SegNode& operator=(const SegNode&) = delete;
    SegNode& operator=(SegNode&&) = delete;

    int query(int l, int r) {
        if (arrStart == l && arrEnd == r)
            return data.val;
        int res = -1e9;
        if (left != nullptr && l <= left->arrEnd)
            res = max(res, left->query(l, min(r, left->arrEnd)));
        if (right != nullptr && r >= right->arrStart)
            res = max(res, right->query(max(l, right->arrStart), r));
        return res;
    }
    void updateOne(int l, int r, int val) {
        if (l == arrStart && r == arrEnd) {
            data.val += val;
            data.lazy += val;
            return;
        }
        pushdown();
        if (left != nullptr && l <= left->arrEnd)
            left->updateOne(l, min(r, left->arrEnd), val);
        if (right != nullptr && r >= right->arrStart)
            right->updateOne(max(l, right->arrStart), r, val);
        data.val = max(left == nullptr ? 0 : left->data.val, right == nullptr ? 0 : right->data.val);
    }
    void print(int i) const {
        cout << i << " " << arrStart << " " << arrEnd << " " << data.val << " " << data.lazy << "\n";
        if (left != nullptr) left->print(i * 2 + 1);
        if (right != nullptr) right->print(i * 2 + 2);
    }

private:
    void pushdown() {
        if (data.lazy == 0)
            return;
        int val = data.lazy;
        data.lazy = 0;
        if (left != nullptr) {
            left->data.lazy += val;
            left->data.val += val;
        }
        if (right != nullptr) {
            right->data.lazy += val;
            right->data.val += val;
        }
        data.val = max(left == nullptr ? 0 : left->data.val, right == nullptr ? 0 : right->data.val);
    }

    int arrStart, arrEnd;
    SegData data;
    SegNode* left;
    SegNode* right;
};

int SegNode::MAXTYPE = 0;

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int n;
        cin >> n >> SegNode::MAXTYPE;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        
        map<int, vector<int>> m;
        
        SegNode* root = new SegNode(0, n - 1);
        int res = 0;
        for (int i = n - 1; i >= 0; --i) {
            int v = a[i];
            a[i] = 1;
            if (m.find(v) != m.end())
                m[v].push_back(i);
            else
                m.insert(make_pair(v, vector<int>{i}));
            root->updateOne(i, n - 1, 1);
            
            if (m[v].size() > SegNode::MAXTYPE) {
                int pos = m[v][m[v].size() - SegNode::MAXTYPE - 1];
                root->updateOne(pos, n - 1, -SegNode::MAXTYPE - a[pos]);
                a[pos] = -SegNode::MAXTYPE;
            }
            if (m[v].size() > SegNode::MAXTYPE + 1) {
                int pos = m[v][m[v].size() - SegNode::MAXTYPE - 2];
                root->updateOne(pos, n - 1, -a[pos]);;
                a[pos] = 0;
            }
            res = max(res, root->query(i, n - 1));
            
            // cout << "\n";
            // root->print(0);
        }
        delete root;
        cout << "Case #" << cse << ": " << res << "\n";
    }
    return 0;
}
