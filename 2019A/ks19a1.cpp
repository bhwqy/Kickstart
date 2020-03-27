#include <bits/stdc++.h>
using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        int n, p;
        scanf("%d%d", &n, &p);
        vector<int> skills(n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &skills[i]);
        int cur = 0;
        sort(skills.begin(), skills.end());
        for (int i = 0; i < p - 1; ++i)
            cur += skills[p - 1] - skills[i];
        int res = cur;
        for (int i = 1; i < n - p + 1; ++i) {
            cur += (skills[i + p - 1] - skills[i + p - 2]) * (p - 1) + skills[i - 1] - skills[i + p - 2];
            res = min(res, cur);
        }
        printf("Case #%d: %d\n", cse, res);
    }
    return 0;
}
