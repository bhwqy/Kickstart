#include <bits/stdc++.h>
using namespace std;

class Disjoint {
public:
    Disjoint(int n) : parent(n), rank(n, 1) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }
    void merge(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx == rooty)
            return;
        if (rank[rootx] < rank[rooty]) {
            parent[rootx] = rooty;
        }
        else {
            parent[rooty] = rootx;
        }
        if (rank[rootx] == rank[rooty])
            rank[rootx]++;
    }
    int find(int x) {
        if (parent[x] == x)
            return x;
        int new_parent = find(parent[x]);
        parent[x] = new_parent;
        return parent[x];
    }
    int getUnconnected() const {
        int count = 0;
        for (int i = 0; i < parent.size(); ++i)
            if (parent[i] == i)
                count++;
        return count;
    }
private:
	vector<int> parent;
	vector<int> rank;
};

int main() {
	int T;
	scanf("%d", &T);
	for (int cse = 1; cse <= T; ++cse) {
		int n, m;
		scanf("%d%d", &n, &m);
        Disjoint ds(n);
		for (int i = 0; i < m; ++i) {
			int c, d;
			scanf("%d%d", &c, &d);
            ds.merge(c - 1, d - 1);
		}
        int res = ds.getUnconnected();
        if (res == 1)
            printf("Case #%d: %d\n", cse, n - 1);
        else
            printf("Case #%d: %d\n", cse, n - 2 + res);
	}
	return 0;
}

