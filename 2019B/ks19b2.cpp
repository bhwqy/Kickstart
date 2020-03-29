#include <bits/stdc++.h>
using namespace std;

struct Stone {
	int s, e, l;
	bool operator<(const Stone& st) const
	{
		return st.l * s < l * st.s;
	}
};

int main() {
	int T;
	cin >> T;
	for (int cse = 1; cse <= T; ++cse) {
		int n, totalSeconds = 0;
		cin >> n;
		vector<Stone> stones(n);
		for (int i = 0; i < n; ++i) {
			cin >> stones[i].s >> stones[i].e >> stones[i].l;
			totalSeconds += stones[i].s;
		}
		sort(stones.begin(), stones.end());
		vector<int> dp(totalSeconds + 1);
		for (int i = 0; i < n; ++i)
			for (int k = totalSeconds; k >= stones[i].s; --k)
				dp[k] = max(dp[k], dp[k - stones[i].s] + max(0, stones[i].e - stones[i].l * (k - stones[i].s)));
		int res = 0;
		for (int i = 0; i <= totalSeconds; ++i)
			res = max(res, dp[i]);
		cout << "Case #" << cse << ": " << res << "\n";
	}
	return 0;
}
