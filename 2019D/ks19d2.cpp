#include <bits/stdc++.h>
using namespace std;

int n, g, m;
map<int, vector<int>> clockwise_guests;
map<int, vector<int>> anticlock_guests;

inline bool calc1(int i, int mid, int right) {
    int tmp1 = (i - mid) % n;
    tmp1 += tmp1 < 0 ? n : 0;
    int tmp2 = (i - right) % n;
    tmp2 += tmp2 < 0 ? n : 0;
    // [tmp2, tmp1]
    if (tmp2 > tmp1)
        tmp1 += n;
    auto it1 = clockwise_guests.lower_bound(tmp1);
    auto it2 = clockwise_guests.lower_bound(tmp2);
    if (it1 != it2)
        return true;
    else if (it1 == clockwise_guests.end())
        return false;
    else if (it1->first == tmp1)
        return true;
    else
        return false;
}

inline bool calc2(int i, int mid, int right) {
    int tmp1 = (i + mid) % n;
    int tmp2 = (i + right) % n;
    // [tmp1, tmp2]
    if (tmp1 > tmp2)
        tmp2 += n;
    auto it1 = anticlock_guests.lower_bound(tmp1);
    auto it2 = anticlock_guests.lower_bound(tmp2);
    if (it1 != it2)
        return true;
    else if (it1 == anticlock_guests.end())
        return false;
    else if (it1->first == tmp2)
        return true;
    else
        return false;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {      
        scanf("%d%d%d", &n, &g, &m);
        clockwise_guests.clear();
        anticlock_guests.clear();
        for (int i = 0; i < g; ++i) {
            int pos;
            char tmp;
            scanf("%d %c", &pos, &tmp);
            pos--; // NOTE pos is [0, n) given [1, n]
            if (tmp == 'C') {
                if (clockwise_guests.find(pos) != clockwise_guests.end()) {
                    clockwise_guests[pos].push_back(i);
                    clockwise_guests[pos + n].push_back(i);
                }
                else {
                    clockwise_guests.insert(make_pair(pos, vector<int>{i}));
                    clockwise_guests.insert(make_pair(pos + n, vector<int>{i}));
                }
            }
            else {
                if (anticlock_guests.find(pos) != anticlock_guests.end()) {
                    anticlock_guests[pos].push_back(i);
                    anticlock_guests[pos + n].push_back(i);
                }
                else {
                    anticlock_guests.insert(make_pair(pos, vector<int>{i}));
                    anticlock_guests.insert(make_pair(pos + n, vector<int>{i}));
                }
            }
        }

        vector<int> last_visit_time(n, -1);
        for (int i = 0; i < n; ++i) {
            int left = 0, right = m;
            while (left <= right) {
                int mid = (left + right) >> 1;
                if (right - mid >= n) {
                    left = mid + 1;
                    continue;
                }
                if (calc1(i, mid, right) || calc2(i, mid, right))
                    left = mid + 1, last_visit_time[i] = mid;
                else
                    right = mid - 1;
            }
        }
        printf("Case #%d:", cse);
        vector<int> res(g, 0);
        for (int i = 0; i < n; ++i) {
            if (last_visit_time[i] == -1)
                continue;
            int tmp1 = (i - last_visit_time[i]) % n;
            tmp1 += tmp1 < 0 ? n : 0;
            int tmp2 = (i + last_visit_time[i]) % n;
            if (clockwise_guests.find(tmp1) != clockwise_guests.end())
                for (auto each : clockwise_guests[tmp1])
                    res[each]++;
            if (anticlock_guests.find(tmp2) != anticlock_guests.end())
                for (auto each : anticlock_guests[tmp2])
                    res[each]++;
        }
        for (auto each : res)
            printf(" %d", each);
        printf("\n");
    }
    return 0;
}
