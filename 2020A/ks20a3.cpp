#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int n, k;
        cin >> n >> k;
        vector<int> m(n);
        vector<int> intervals;
        for (int i = 0; i < n; ++i)
            cin >> m[i];
        for (int i = 0; i < n - 1; ++i)
            intervals.push_back(m[i + 1] - m[i]);
        int left = 1, right = m[n - 1];
        while (left <= right) {
            int cur = 0;
            int mid = (left + right) / 2;
            for (auto i : intervals)
                // NOTE if i divides mid
                cur += i / mid - (i % mid == 0);
            if (cur > k)
                left = mid + 1;
            else
                right = mid - 1;
        }
        cout << "Case #" << cse << ": " << left << "\n";
    }
    return 0;
}