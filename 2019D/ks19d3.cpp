#include <bits/stdc++.h>
using namespace std;

struct Spot {
    int dist, cost;
    bool operator<(const Spot& s) const { return dist < s.dist; }
};

int main() {
    int T;
    scanf("%d", &T);
    for (int cse = 1; cse <= T; ++cse) {
        int k, n;
        scanf("%d%d", &k, &n);
        vector<Spot> spots(n);
        vector<long long> left_min_cost(n), right_min_cost(n);
        for (int i = 0; i < n; ++i)
            scanf("%d", &spots[i].dist);
        for (int i = 0; i < n; ++i)
            scanf("%d", &spots[i].cost);
        sort(spots.begin(), spots.end());
        if (k == 1) {
            right_min_cost[n - 2] = spots[n - 1].cost + spots[n - 1].dist;
            for (int warehouse_pos = n - 3; warehouse_pos >= 0; --warehouse_pos) {
                int i = warehouse_pos + 1;
                right_min_cost[warehouse_pos] = min(right_min_cost[warehouse_pos + 1], static_cast<long long>(spots[i].cost + spots[i].dist));
            }
            long long res = LLONG_MAX;
            for (int i = 0; i < n - 1; ++i) {
                int warehouse_cost = spots[i].cost - spots[i].dist;
                res = min(res, right_min_cost[i] + warehouse_cost);
            }
            printf("Case #%d: %lld\n", cse, res);
            continue;
        }
        int khalf = k >> 1, krem = k - khalf;
        
        priority_queue<int> leftq; // 最大堆
        long long leftq_sum = 0;
        for (int i = 0; i < khalf; ++i) {
            int tmp = spots[i].cost - spots[i].dist;
            leftq.push(tmp);
            leftq_sum += tmp;
        }
        left_min_cost[khalf] = leftq_sum;
        for (int warehouse_pos = khalf + 1; warehouse_pos < n - krem; ++warehouse_pos) {
            int i = warehouse_pos - 1;
            int tmp = spots[i].cost - spots[i].dist;
            if (tmp < leftq.top()) {
                leftq_sum += tmp - leftq.top();
                leftq.pop();
                leftq.push(tmp);
            }
            left_min_cost[warehouse_pos] = min(left_min_cost[warehouse_pos - 1], leftq_sum);
        }
        
        priority_queue<int> rightq;
        long long rightq_sum = 0;
        for (int i = n - 1; i >= n - krem; --i) {
            int tmp = spots[i].cost + spots[i].dist;
            rightq.push(tmp);
            rightq_sum += tmp;
        }
        right_min_cost[n - krem - 1] = rightq_sum;
        for (int warehouse_pos = n - krem - 2; warehouse_pos >= khalf; --warehouse_pos) {
            int i = warehouse_pos + 1;
            int tmp = spots[i].cost + spots[i].dist;
            if (tmp < rightq.top()) {
                rightq_sum += tmp - rightq.top();
                rightq.pop();
                rightq.push(tmp);
            }
            right_min_cost[warehouse_pos] = min(right_min_cost[warehouse_pos + 1], rightq_sum);
        }
        long long res = LLONG_MAX;
        for (int i = khalf; i < n - krem; ++i) {
            int warehouse_cost = (khalf - krem) * spots[i].dist + spots[i].cost;
            res = min(res, left_min_cost[i] + right_min_cost[i] + warehouse_cost);
        }
        printf("Case #%d: %lld\n", cse, res);
    }
    return 0;
}
