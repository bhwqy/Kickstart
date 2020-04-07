#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;

char instruction[50010];
class IntervalSet {
public:
    IntervalSet() : data{{INT_MAX, INT_MAX}, {INT_MIN, INT_MIN}} {}
    void insert(int x) {
        auto i = data.lower_bound(make_pair(x, x));
        auto j = i--;
        if (i->second == x - 1 && j->first == x + 1) {
            int t1 = i->first, t2 = j->second;
            data.insert(make_pair(t1, t2));
            data.erase(i);
            data.erase(j);
        }
        else if (i->second == x - 1) {
            int t1 = i->first;
            data.insert(make_pair(t1, x));
            data.erase(i);
        }
        else if (j->first == x + 1) {
            int t2 = j->second;
            data.insert(make_pair(x, t2));
            data.erase(j);
        }
        else {
            data.insert(make_pair(x, x));
        }
    }
    int query(int x, bool pos_dir) {
        auto i = data.lower_bound(make_pair(x, x));
        auto j = i--;
        if (pos_dir) {
            if (j->first == x)
                return j->second + 1;
            else
                return x + 1;
        }
        else {
            if (i->second == x)
                return i->first - 1;
            else
                return x - 1;
        }
    }

private:
    set<pii> data;
};

int main() {
    int T;
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        int n, r, c, x, y;
        scanf("%d%d%d%d%d%s", &n, &r, &c, &x, &y, instruction);
        vector<IntervalSet> rows(r), cols(c);
        x--, y--;
        for (int i = 0; i < n; ++i) {
            int dx, dy;
            auto c = instruction[i];
            if (c == 'N'){
                dy = y;
                dx = cols[y].query(x - 1, false);
            }
            else if (c == 'S') {
                dy = y;
                dx = cols[y].query(x + 1, true);
            }
            else if (c == 'W') {
                dx = x;
                dy = rows[x].query(y - 1, false);
            }
            else {
                dx = x;
                dy = rows[x].query(y + 1, true);
            }
            rows[x].insert(y), rows[y].insert(x);
            x = dx, y = dy;
        }
        x++, y++;
        printf("Case #%d: %d %d\n", cse, x, y);
    }
    return 0;
}
