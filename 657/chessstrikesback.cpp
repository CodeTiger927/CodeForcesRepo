using namespace std;

#include <iostream>
#include <set>

#define MAXN 400005

int N,M,Q;
set<int> s[MAXN];
pair<bool,pair<int,int>> st[1 << 20];

pair<bool,pair<int,int>> combine(pair<bool,pair<int,int>> a,pair<bool,pair<int,int>> b) {
	return {a.first || b.first || (a.second.first < b.second.second),{min(a.second.first,b.second.first),max(a.second.second,b.second.second)}};
}

int main() {
	cin >> N >> M >> Q;
	for(int i = 0;i < (1 << 20);++i) {
		if(i < MAXN) s[i].insert((i & 1 ? 0 : MAXN));
		st[i].second.first = MAXN;
	}
	for(int i = 0;i < Q;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		if(s[a].count(b)) {
			s[a].erase(b);
		}else{
			s[a].insert(b);
		}
		if(a & 1) {
			st[(1 << 19) + a].second.second = *s[a].rbegin();
		}else{
			st[(1 << 19) + a].second.first = *s[a].begin();
		}
		for(int i = (a + (1 << 19)) >> 1;i;i >>= 1) st[i] = combine(st[i << 1],st[i << 1 | 1]);
		cout << (st[1].first ? "NO" : "YES") << "\n";
	}
	return 0;
}