#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
bool v1[1000005], v2[1000005];
ll Prime(ll a, ll b) {
    b++;
    if (a > b) return 0ll;
    for (ll i = 0; i * i < b; i++)
        v1[i] = true;
    for (ll i = 0; i < b - a; i++)
        v2[i] = true;

    for (ll i = 2; i * i < b; i++) {
        if (v1[i]) {
            // [2,b)
            for (ll j = 2 * i; j * j < b; j += i)
                v1[j] = false; 
            // 筛[a,b)
            // ((a+i-1)/i)*i是符合>=a最小是i倍数的数
            for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i)
                v2[j - a] = false;   
        }
    }
    ll k = 0;
    for (ll i = 0; i < b - a; i++)
        if (v2[i])
            k++;
    if (a <= 2 && b > 2) 
        k--;
    if (a <= 1 && b > 1)
        k--;
    return k;
}

ll getans(ll x, ll y) {
    ll a1 = Prime(x, y);
    ll a2 = Prime((x + 3) >> 2, y >> 2);
    ll a3 = ((y + 2) >> 2) - ((x + 1) >> 2);
    ll ans = a1 + a2 + a3;
    if (x <= 1 && y >= 1) ans++;
    if (x <= 4 && y >= 4) ans++;
    if (x <= 8 && y >= 8) ans++;
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        ll l, r;
        scanf("%lld%lld", &l, &r);
        printf("Case #%d: %lld\n", cse, getans(l, r));
    }
    return 0;
}
