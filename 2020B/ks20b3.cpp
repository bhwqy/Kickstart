#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9;
typedef pair<ll, ll> pl4;
const pl4 dirs[4]{ {1, 0}, {0, 1}, {mod - 1, 0}, {0, mod - 1} };
int get_dir(char c) {
    if(c == 'E') return 0;
    if(c == 'S') return 1;
    if(c == 'W') return 2;
    if(c == 'N') return 3;
    assert(0);
    return -1;
}

char s[2005];
int n, T;
pl4 pos;

pl4 move(int k, int& i) {
    pl4 dx{ 0, 0};
    for (int j = i; j < n; ++j) {
        if (s[j] >= '2' && s[j] <= '9') {
            int k = s[j] - '0';
            j += 2;
            auto dy = move(k, j);
            dx.first = (dx.first + dy.first) % mod;
            dx.second = (dx.second + dy.second) % mod;
        }
        else if (s[j] == ')') {
            i = j;
            break;
        }
        else {
            int d = get_dir(s[j]);
            dx.first = (dx.first + dirs[d].first) % mod;
            dx.second = (dx.second + dirs[d].second) % mod;
        }
    }
    return { ((ll)k * dx.first) % mod, ((ll)k * dx.second) % mod};
}

int main() {
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        scanf("%s", s); n = strlen(s);
        pos.first = 0, pos.second = 0;
        for (int i = 0; i < n; ++i) {
            if (s[i] >= '2' && s[i] <= '9') {
                int k = s[i] - '0';
                i += 2;
                auto dx = move(k, i);
                pos.first = (pos.first + dx.first) % mod;
                pos.second = (pos.second + dx.second) % mod;
            }
            else {
                int d = get_dir(s[i]);
                pos.first = (pos.first + dirs[d].first) % mod;
                pos.second = (pos.second + dirs[d].second) % mod;
            }
        }
        printf("Case #%d: %lld %lld\n", cse, pos.first + 1, pos.second + 1);
    }
    return 0;
}