#include <bits/stdc++.h>
using namespace std;
int a[105];

int main() {
	int T; scanf("%d", &T);
	for (int cse = 1; cse <= T; ++cse) {
		int n; scanf("%d", &n);
		for (int i = 1; i <= n; ++i)
			scanf("%d", &a[i]);
		int ans = 0;
		for (int i = 2; i < n; ++i)
			if (a[i] > a[i - 1] && a[i] > a[i + 1])
				ans++;
		printf("Case #%d: %d\n", cse, ans);
	}
	return 0;
}
