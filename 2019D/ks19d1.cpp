#include <bits/stdc++.h>
using namespace std;

class SegNode {
public:
    SegNode(int l, int r) : arrStart(l), arrEnd(r), left(nullptr), right(nullptr), 
        oddFirst(INT_MAX), oddLast(INT_MIN), data(0)
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

    int query() {
        if ((data & 1) == 0) return arrEnd - arrStart + 1;
        if (oddFirst == 0 || oddLast == arrEnd)
            return arrEnd;
        else
            return max(arrEnd - oddFirst, oddLast);
    }
    void updateOne(int pos, int val) {
        if (arrStart == arrEnd) {
            if (val & 1) {
                oddFirst = oddLast = arrStart;
            }
            else {
                oddFirst = INT_MAX;
                oddLast = INT_MIN;
            }
            data = val;
            return;
        }
        if (pos <= left->arrEnd)
            left->updateOne(pos, val);
        else
            right->updateOne(pos, val);
        data = left->data + right->data;
        oddFirst = min(left->oddFirst, right->oddFirst);
        oddLast = max(left->oddLast, right->oddLast);
    }
    void print(int i) const {
        cout << i << " " << arrStart << " " << arrEnd << " "  << "\n";
        if (left != nullptr) left->print(i * 2 + 1);
        if (right != nullptr) right->print(i * 2 + 2);
    }
private:
    int arrStart, arrEnd;
    SegNode* left;
    SegNode* right;
    int oddFirst, oddLast, data;
};

int main() {
    // 预处理位0和1
    int table[1024];
    for (int mask = 0; mask < 1024; ++mask)
    {
        int cnt = 0;
        for (int i = 0; i < 10; ++i)
            if ((mask >> i) & 1) cnt++;
        table[mask] = cnt & 1;
    }

    int T;
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        int n, q;
        scanf("%d%d", &n, &q);
        SegNode* root = new SegNode(0, n - 1);
        for (int i = 0; i < n; ++i) {
            int tmp;
            scanf("%d", &tmp);
            root->updateOne(i, table[tmp]);
        }

        printf("Case #%d:", cse);
        while (q--) {
            int pos, val;
            scanf("%d%d", &pos, &val);
            root->updateOne(pos, table[val]);
            printf(" %d", root->query());
        }
        printf("\n");
    }
    return 0;
}
