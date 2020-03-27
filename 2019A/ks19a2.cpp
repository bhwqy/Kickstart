#include <bits/stdc++.h>
using namespace std;

const int dir[4][2]{ {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int main() {
    int T;
    cin >> T;
    for (int cse = 1; cse <= T; ++cse) {
        int r, c;
        queue<pair<int, int>> q;
        cin >> r >> c;
        vector<string> grid(r);
        vector<vector<int>> dist(r, vector<int>(c, INT_MAX));
        for (int i = 0; i < r; ++i) {
            cin >> grid[i];
            for (int j = 0; j < c; ++j)
                if (grid[i][j] == '1') {
                    dist[i][j] = 0;
                    q.push(make_pair(i, j));
                }
        }
        
        int max_dist = 0;      
        while (!q.empty()) {
            int i = q.front().first, j = q.front().second;
            q.pop();
            for (int k = 0; k < 4; ++k) {
                int i0 = i + dir[k][0], j0 = j + dir[k][1];
                if (i0 < 0 || i0 >= r || j0 < 0 || j0 >= c)
                    continue;
                if (dist[i0][j0] != INT_MAX)
                    continue;
                dist[i0][j0] = dist[i][j] + 1;
                max_dist = max(max_dist, dist[i0][j0]);
                q.push(make_pair(i0, j0));
            }
        }

        int left = 0, right = max_dist;
        // 能否修建至多一个站点到达mid
        bool success;
        // 二分法寻找第一个成功
        while (left <= right) {
            int mid = (left + right) >> 1;
            success = false;

            int ijsum_max = INT_MIN, ijsum_min = INT_MAX;
            int ijdiff_max = INT_MIN, ijdiff_min = INT_MAX;

            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    if (dist[i][j] > mid) {
                        ijsum_max = max(ijsum_max, i + j);
                        ijsum_min = min(ijsum_min, i + j);
                        ijdiff_max = max(ijdiff_max, i - j);
                        ijdiff_min = min(ijdiff_min, i - j);
                    }
                }
            }

            for (int i = 0; i < r; ++i) {
                for (int j = 0; j < c; ++j) {
                    if (grid[i][j] != '1') {
                        if (max(abs(i + j - ijsum_max), abs(i + j - ijsum_min)) <= mid
                            && max(abs(i - j - ijdiff_max), abs(i - j - ijdiff_min)) <= mid) {
                            success = true;
                            break;
                        }
                    }
                }
                if (success)
                    break;
            }

            if (success)
                right = mid - 1;
            else
                left = mid + 1;
        }
        if (left > max_dist)
            printf("Case #%d: %d\n", cse, max_dist);
        else
            printf("Case #%d: %d\n", cse, left);
    }
    return 0;
}
