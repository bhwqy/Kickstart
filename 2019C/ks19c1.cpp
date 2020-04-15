#include <iostream>
#include <vector>
#include <map>
using namespace std;

#define mp make_pair
typedef pair<int, int> pii;

const int maxn = 200005;
map<pii, pii> fax, fay, up, down, le, ri;

pii findx(pii t) {
	if (fax[t] == t)
		return t;
	return fax[t] = findx(fax[t]);
}

pii findy(pii t) {
	if (fay[t] == t) 
		return t;
	return fay[t] = findy(fay[t]);
}

void addx(int x, int y) {
	bool hl = fax.count(mp(x, y - 1)), hr = fax.count(mp(x, y + 1));
	if (!hl && !hr)	{
		fax[mp(x, y)] = mp(x, y);
		le[mp(x, y)] = mp(x, y - 1);
		ri[mp(x, y)] = mp(x, y + 1);
	}
	if (hl && !hr) {
		fax[mp(x, y)] = findx(mp(x, y - 1));
		ri[findx(mp(x, y - 1))] = mp(x, y + 1);
	}
	if (!hl && hr) {
		fax[mp(x, y)] = findx(mp(x, y + 1));
		le[findx(mp(x, y + 1))] = mp(x, y - 1);
	}
	if (hl && hr) {
		pii f1 = findx(mp(x, y - 1));
		pii f2 = findx(mp(x, y + 1));
		fax[mp(x, y)] = fax[f2] = f1;
		ri[f1] = ri[f2];
	}
}

void addy(int x, int y) {
	bool hu = fay.count(mp(x - 1, y)), hd = fay.count(mp(x + 1, y));
	if (!hu && !hd) {
		fay[mp(x, y)] = mp(x, y);
		up[mp(x, y)] = mp(x - 1, y);
		down[mp(x, y)] = mp(x + 1, y);
	}
	if (hu && !hd) {
		fay[mp(x, y)] = findy(mp(x - 1, y));
		down[findy(mp(x - 1, y))] = mp(x + 1, y);
	}
	if (!hu && hd) {
		fay[mp(x, y)] = findy(mp(x + 1, y));
		up[findy(mp(x + 1, y))] = mp(x - 1, y);
	}
	if (hu && hd) {
		pii f1 = findy(mp(x - 1, y));
		pii f2 = findy(mp(x + 1, y));
		fay[mp(x, y)] = fay[f2] = f1;
		down[f1] = down[f2];
	}
}

char s[maxn];
int main() {
	int T;
	scanf("%d", &T);
	for (int cse = 1; cse <= T; ++cse) {
		int n, r, c, sr, sc;
		scanf("%d%d%d%d%d%s", &n, &r, &c, &sr, &sc, s);
		fax.clear(); fay.clear(); up.clear(); down.clear(); le.clear(); ri.clear();
		pii now = mp(sr, sc); fax[now] = now; fay[now] = now;
		up[now] = mp(now.first - 1, now.second); 
		down[now] = mp(now.first + 1, now.second);
		le[now] = mp(now.first, now.second - 1);
		ri[now] = mp(now.first, now.second + 1);
		for (int i = 0; i < n; ++i) {
			if (s[i] == 'N') now = up[findy(now)];
			if (s[i] == 'S') now = down[findy(now)];
			if (s[i] == 'W') now = le[findx(now)];
			if (s[i] == 'E') now = ri[findx(now)];
			int x = now.first, y = now.second;
			addx(x, y); addy(x, y);
		}
		printf("Case #%d: %d %d\n", cse, now.first, now.second);
	}
	return 0;
}
