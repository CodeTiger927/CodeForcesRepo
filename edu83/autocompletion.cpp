using namespace std;

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

#define MAXN 1000005

long long N,M,lvl,st[MAXN],pos[MAXN],dp[MAXN];
vector<pair<char,int>> edges[MAXN];
multiset<long long> s;
bool term[MAXN];

void updg(long long x) {
	lvl += x;
}

void upd(int x,long long v) {
	s.erase(s.find(st[x]));
	st[x] = v - lvl;
	s.insert(st[x]);
}

long long get() {
	return *s.begin() + lvl;
}

void dfs(int v,int d,int last) {
	dp[v] = last + 1;
	if(term[v]) dp[v] = min(dp[v],get());
	upd(d,dp[v] + 1);
	if(term[v]) updg(1);
	sort(edges[v].begin(),edges[v].end());
	for(auto [_,u] : edges[v]) {
		dfs(u,d + 1,dp[v]);
	}
	upd(d,1e9);
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	s.insert(st[0] = 1e9);
	for(int i = 1;i <= N;++i) {
		int p;
		char c;
		cin >> p >> c;
		edges[p].push_back({c,i});
		st[i] = 1e9;
		s.insert(st[i]);
	}
	cin >> M;
	for(int i = 0;i < M;++i) {
		cin >> pos[i];
		term[pos[i]] = true;
	}
	dfs(0,0,-1);
	for(int i = 0;i < M;++i) {
		cout << dp[pos[i]] << " \n"[i == M - 1];
	}
	return 0;
}