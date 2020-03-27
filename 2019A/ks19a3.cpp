#include <bits/stdc++.h>
using namespace std;

struct pa {
    int len, pos;
    pa(int x, int y) : len(x), pos(y) {}
    bool operator<(const pa& p) const {
        if (len != p.len)
            return len > p.len;
        return pos < p.pos;
    }
};

class SegData {
public:
    SegData() : curBookCount(0), treeBookCount(0) {};
    void insert(int i) {
        curBookCount++, treeBookCount++;
        whobooks.insert(i);
    }
    void del(int i) {
        curBookCount--, treeBookCount--;
        whobooks.erase(i);
    }
    set<int> whobooks;
    int curBookCount; // 这个区间当前被订阅的次数
    int treeBookCount; // 子树当前被订阅的次数
};

class SegNode {
public:
    SegNode() : arrStart(-1), arrEnd(-1), left(nullptr), right(nullptr) {}
    SegNode(int n) : arrStart(0), arrEnd(n - 1), left(nullptr), right(nullptr)
    {
        if (n <= 0)
            arrStart = -1, arrEnd = -1;
        else if (n == 1)
            return;
        else {
            int mid = (n - 1) >> 1;
            left = new SegNode(0, mid);
            right = new SegNode(mid + 1, n - 1);
        }
    }
    SegNode(int l, int r) : arrStart(l), arrEnd(r), left(nullptr), right(nullptr)
    {
        if (l != r) {
            int mid = (l + r) >> 1;
            left = new SegNode(l, mid);
            right = new SegNode(mid + 1, r);
        }
        else
            return;
    }
    ~SegNode() {
        delete left;
        delete right;
    }

    SegNode(const SegNode&) = delete;
    SegNode(SegNode&&) = delete;
    SegNode& operator=(const SegNode&) = delete;
    SegNode& operator=(SegNode&&) = delete;

    void insert(int i, int l, int r) {
        if (arrStart == l && arrEnd == r) {
            data.insert(i);
            return;
        }
        if (r < right->arrStart)
            left->insert(i, l, r);
        else if (l > left->arrEnd)
            right->insert(i, l, r);
        else
            left->insert(i, l, left->arrEnd), right->insert(i, right->arrStart, r);
        data.treeBookCount = min(left->data.treeBookCount, right->data.treeBookCount) + data.curBookCount;
    }
    void del(int i, int l, int r) {
        if (arrStart == l && arrEnd == r) {
            data.del(i);
            return;
        }
        if (r < right->arrStart)
            left->del(i, l, r);
        else if (l > left->arrEnd)
            right->del(i, l, r);
        else
            left->del(i, l, left->arrEnd), right->del(i, right->arrStart, r);
        data.treeBookCount = min(left->data.treeBookCount, right->data.treeBookCount) + data.curBookCount;
    }
    void query(int& i, int& who) {
        if (!data.whobooks.empty()) who = *data.whobooks.begin();
        if (arrStart == arrEnd) {
            i = arrStart;
            return;
        }
        if (left->data.treeBookCount < right->data.treeBookCount)
            left->query(i, who);
        else
            right->query(i, who);
    }
    void change(int i) {
        if (arrStart == arrEnd) {
            data.treeBookCount = 1e9;
            return;
        }
        if (i <= left->arrEnd)
            left->change(i);
        else
            right->change(i);
        data.treeBookCount = min(left->data.treeBookCount, right->data.treeBookCount) + data.curBookCount;
    }
    bool hasNonIntersect() const {
        return data.treeBookCount <= 1;
    }
    void print(int i) const {
        cout << i << " " << arrStart << " " << arrEnd << " " << data.curBookCount << "\n";
        if (left != nullptr)
            left->print(i * 2 + 1);
        if (right != nullptr)
            right->print(i * 2 + 2);
    }
private:
    // NOTE this is the start and end of the intervals
    int arrStart, arrEnd;
    SegData data;
    SegNode* left;
    SegNode* right;
};

class SegTree {
public:
    SegTree(int n) : root(new SegNode(n)), n(n) {}
    ~SegTree() { delete root; }
    SegTree(const SegTree&) = delete;
    SegTree(SegTree&&) = delete;
    SegTree& operator=(const SegTree&) = delete;
    SegTree& operator=(SegTree&&) = delete;

    void query(int& i, int& who) {
        root->query(i, who);
    }
    void insert(int i, int l, int r) {
        root->insert(i, l, r);
    }
    void change(int i) {
        root->change(i);
    }
    void del(int i, int l, int r) {
        root->del(i, l, r);
    }
    bool hasNonIntersect() const {
        return root->hasNonIntersect();
    }
    void print() const {
        root->print(0);
    }
private:
    SegNode* root;
    int n;
};

inline vector<pair<int, int>> getIntervals(const vector<pair<int, int>>& book) {
    int q = book.size();
    vector<int> tmp(q * 2);
    for (int i = 0; i < q; ++i)
        tmp[i << 1] = book[i].first, tmp[(i << 1) + 1] = book[i].second;
    sort(tmp.begin(), tmp.end());
    vector<pair<int, int>> res{ {tmp[0], tmp[0]} };
    for (int i = 1; i < tmp.size(); ++i) {
        if (tmp[i] != tmp[i - 1]) {
            if (tmp[i - 1] + 1 < tmp[i])
                res.push_back(make_pair(tmp[i - 1] + 1, tmp[i] - 1));
            res.push_back(make_pair(tmp[i], tmp[i]));
        }
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int n, q;
        cin >> n >> q;
        vector<pair<int, int>> book(q);

        for (int i = 0; i < q; ++i)
            cin >> book[i].first >> book[i].second;
        auto intervals = getIntervals(book);

        vector<pair<int, int>> book_interval(q);
        SegTree st(intervals.size());
        for (int i = 0; i < q; ++i) {
            int left = 0, right = intervals.size() - 1;
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (intervals[mid].first >= book[i].first)
                    book_interval[i].first = mid, right = mid - 1;
                else
                    left = mid + 1;
            }
            left = 0, right = intervals.size() - 1;
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (intervals[mid].second <= book[i].second)
                    book_interval[i].second = mid, left = mid + 1;
                else
                    right = mid - 1;
            }
            st.insert(i, book_interval[i].first, book_interval[i].second);
        }

        // 从后往前 贪心法找长度最长的区间
        int res = n;
        vector<int> b(q, 0);
        set<pa> G; // 红黑树维护区间 长度最长
        for (int i = 0; i < q; ++i)
            G.insert(pa(0, i));
        
        for (int i = 0; i < q; ++i) {
            while (st.hasNonIntersect()) {
                int id = -1, who = -1;
                st.query(id, who);
                st.change(id);
                if (who >= 0) {
                    G.erase(pa(b[who], who));
                    b[who] += intervals[id].second - intervals[id].first + 1;
                    G.insert(pa(b[who], who));
                }
            }
            auto gt = *G.begin();
            res = min(res, gt.len);
            G.erase(G.begin());
            st.del(gt.pos, book_interval[gt.pos].first, book_interval[gt.pos].second);
        }
        cout << "Case #" << cse << ": " << res << "\n";
    }
    return 0;
}
