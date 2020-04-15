#include <algorithm>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;

int LOG2[305];
int st_max[305][10], st_min[305][10];
int goodness[305][305];

int a[305], le[305], ri[305];
stack<int> s;

inline int query(int l, int r) {
    int t = LOG2[r - l + 1];
    int m = max(st_max[l][t], st_max[r - (1 << t) + 1][t]);
    int n = min(st_min[l][t], st_min[r - (1 << t) + 1][t]);
    return m - n;
}

int main() {
    int T; scanf("%d", &T);
    LOG2[1] = 0;
    for (int i = 2; i <= 300; ++i)
        LOG2[i] = LOG2[i >> 1] + 1;

    for (int cse = 1; cse <= T; ++cse) {
        int r, c, k;
        scanf("%d%d%d", &r, &c, &k);
        for (int i = 1; i <= r; ++i) {
            for (int j = 1; j <= c; ++j) {
                int x; scanf("%d", &x);
                st_max[j][0] = st_min[j][0] = x;
            }
            for (int u = 1; (1 << u) <= c; ++u)
                for (int v = 1; v + (1 << u) - 1 <= c; ++v) {
                    st_max[v][u] = max(st_max[v][u - 1], st_max[v + (1 << (u - 1))][u - 1]);
                    st_min[v][u] = min(st_min[v][u - 1], st_min[v + (1 << (u - 1))][u - 1]);
                }
            for (int j = 1; j <= c; ++j) {
                int left = j, right = c;
                while (right - left > 1) {
                    int mid = (left + right) >> 1;
                    if (query(j, mid) <= k) left = mid;
                    else right = mid;
                }
                while (left <= c && query(j, left) <= k)
                    ++left;
                goodness[i][j] = left - j;
            }
        }
        
        // leetcode 42
        int res = 0;
        for (int j = 1; j <= c; ++j) {
            for (int i = 1; i <= r; ++i) a[i] = goodness[i][j];
            a[0] = a[r + 1] = 0;
            // left
            while (!s.empty()) s.pop();
            s.push(0);
            for (int i = 1; i <= r; ++i) {
                while (a[s.top()] >= a[i]) s.pop();
                le[i] = s.top(); s.push(i);
            }
            // right
            while (!s.empty()) s.pop();
            s.push(r + 1);
            for (int i = r; i >= 1; --i) {
                while (a[s.top()] >= a[i]) s.pop();
                ri[i] = s.top(); s.push(i);
            }
            for (int i = 1; i <= r; ++i) 
                res = max(res, a[i] * (ri[i] - le[i] - 1));
        }
        printf("Case #%d: %d\n", cse, res);
    }
    return 0;
}
