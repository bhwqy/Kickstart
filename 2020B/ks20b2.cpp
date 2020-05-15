#include <bits/stdc++.h>
using namespace std;
long long x[1005];
int main()
{
    int T; scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        int n; long long d; scanf("%d%lld", &n, &d);
        for (int i = 1; i <= n; ++i) scanf("%lld", &x[i]);
        long long left = 1, right = d;
        while (left <= right) {
            long long mid = (left + right) / 2;
            //printf("left = %lld，mid = %lld,right = %lld\n", left,mid, right);
            bool success = true;
            //判断是否可以
            long long curindex = mid;
            for (int i = 1; i <= n; ++i) {
                long long tmp = curindex / x[i];
                long long tmp2 = tmp * x[i];
                if (tmp2 < curindex) tmp2 += x[i];
                if (tmp2 > d) {
                    success = false;
                    break;
                }
                else {
                    curindex = tmp2;
                }
            }

            if (success)
                left = mid+1;
            else
                right = mid-1;
            /*printf("left = %d,right = %d\n", left, right);*/
        }
        bool success = true;
        for (int i = 1; i <= n; ++i) {
            long long curindex = left;
            //判断是否可以
            for (int i = 1; i <= n; ++i) {
                long long tmp = curindex / x[i];
                long long tmp2 = tmp * x[i];
                if (tmp2 < curindex) tmp2 += x[i];
                if (tmp2 > d) {
                    success = false;
                    break;
                }
                else {
                    curindex = tmp2;
                }
            }
        }
        if (!success) left--;
        printf("Case #%d: %lld\n", cse, left);
    }
    return 0;
}