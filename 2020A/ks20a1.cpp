#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int n, b;
        cin >> n >> b;
        vector<int> a(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        sort(a.begin(), a.end());
        int res = 0, spent = 0;
        while (spent + a[res] <= b) {
            spent += a[res];
            res++;
        }
        cout << "Case #" << cse << ": " << res << "\n";
    }
    return 0;
}