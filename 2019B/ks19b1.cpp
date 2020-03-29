#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int n, q;
        string s;
        cin >> n >> q >> s;
        vector<vector<int>> m(n + 1, vector<int>(26, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < 26; ++j)
                m[i + 1][j] = m[i][j];
            m[i + 1][s[i] - 'A']++;
        }

        int res = 0;
        int left, right;
        for (int i = 0; i < q; ++i) {
            cin >> left >> right;
            // NOTE 左开右闭区间
            left--;
            if ((right - left) & 1) {
                int has1 = 0;
                for (int j = 0; j < 26; ++j) {
                    if ((m[right][j] - m[left][j]) & 1) {
                        has1++;
                        if (has1 == 2)
                            break;
                    }
                }
                if (has1 == 1)
                    res++;
            }
            else {
                bool isP = true;
                for (int j = 0; j < 26; ++j) {
                    if ((m[right][j] - m[left][j]) & 1) {
                        isP = false;
                        break;
                    }
                }
                if (isP)
                    res++;
            }
        }
        printf("Case #%d: %d\n", cse, res);
    }
    return 0;
}
