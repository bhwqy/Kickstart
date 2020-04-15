#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
const int MAXN = 1005;
int pos[MAXN], color[MAXN];
vector<int> a[MAXN];
int dp[MAXN][MAXN][2];

int main() {
	int T; scanf("%d", &T);
	for (int cse = 1; cse <= T; ++cse) {
		int n, k; scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &pos[i]);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &color[i]);
		for (int i = 1; i <= 1000; ++i)
			a[i].clear();
		for (int i = 1; i <= n; ++i)
			a[color[i]].push_back(pos[i]);
		for (int i = 1; i <= 1000; ++i)
			sort(a[i].begin(), a[i].end());
        
        for (int i = 0; i <= 1000; ++i)
            for (int j = 0; j <= 1000; ++j)
                dp[i][j][0] = dp[i][j][1] = 1e9;
        for (int i = 0; i <= 1000; ++i)
            dp[i][0][0] = dp[i][0][1] = 0;

        for (int i = 1; i <= 1000; ++i) {
            for (int j = 0; j <= k; ++j)
                dp[i][j][0] = dp[i - 1][j][0], dp[i][j][1] = dp[i - 1][j][1];
            for (int j = 0; j < a[i].size(); ++j) {
                for (int x = j + 1; x <= k; ++x) {
                    dp[i][x][0] = min(dp[i][x][0], dp[i - 1][x - j - 1][0] + 2 * a[i][j]);
                    dp[i][x][1] = min(dp[i][x][1], dp[i - 1][x - j - 1][0] + a[i][j]);
                    dp[i][x][1] = min(dp[i][x][1], dp[i - 1][x - j - 1][1] + 2 * a[i][j]);
                }
            }
        }
        int ans = 1e9;
        for (int i = 1; i <= 1000; ++i)
            ans = min(ans, dp[i][k][1]);
		printf("Case #%d: %d\n", cse, ans);
	}
	return 0;
}
