#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int n, k, p;
        cin >> n >> k >> p;
        vector<vector<int>> a(n, vector<int>(k));
        vector<vector<int>> s(n, vector<int>(k));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < k; ++j)
                cin >> a[i][j];
        for (int i = 0; i < n; ++i) {
            s[i][0] = a[i][0];
            for (int j = 1; j < k; ++j)
                s[i][j] = s[i][j - 1] + a[i][j];
        }
        vector<int> dp(p + 1, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = p; j >= 0; --j)
                for (int x = 1; x <= min(k, j); ++x)
                    dp[j] = max(dp[j], dp[j - x] + s[i][x - 1]);
        }
        int res = 0;
        for (int i = 0; i <= p; ++i)
            res = max(res, dp[i]);
        cout << "Case #" << cse << ": " << res << "\n";
    }
    return 0;
}
