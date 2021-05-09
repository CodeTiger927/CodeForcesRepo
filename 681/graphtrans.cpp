using namespace std;

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define MAXN 200005
#define MAXK 19
#define MOD 998244353

int N,M;
long long dp[MAXN * MAXK];
pair<int,int> dp2[MAXN * 2];
vector<pair<int,long long>> edges[MAXN * MAXK];
vector<pair<int,pair<int,int>>> edges2[MAXN * 2];
vector<pair<int,int>> v;

long long calc(pair<int,int> p) {
	long long ans = 1;
	for(int i = 0;i < p.first;++i) {
		ans = (ans << 1) % MOD;
	}
	ans = (ans + p.second) % MOD;
	return ans;
}

long long solve1() {
	memset(dp,-1,sizeof(dp));
	for(auto e : v) {
		for(int j = 0;j < MAXK;++j) {
			if(j & 1) {
				edges[e.second + N * j].push_back({e.first + N * j,1});
			}else{
				edges[e.first + N * j].push_back({e.second + N * j,1});
			}
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < MAXK - 1;++j) {
			edges[i + N * j].push_back({i + N * (j + 1),1ll << j});
		}
	}
	dp[0] = 0;
	priority_queue<pair<long long,int>> pq;
	pq.push({-dp[0],0});
	while(!pq.empty()) {
		pair<long long,int> cur = pq.top();
		pq.pop();
		long long d = -cur.first;
		int v = cur.second;
		if(d != dp[v]) continue;
		for(auto e : edges[v]) {
			long long nd = e.second + dp[v];
			if(dp[e.first] != -1 && nd >= dp[e.first]) continue;
			dp[e.first] = nd;
			pq.push({-nd,e.first});
		}
	}
	long long ans = 1e9;
	for(int i = 0;i < MAXK;++i) {
		if(dp[N - 1 + N * i] != -1) {
			ans = min(ans,dp[N - 1 + N * i]);
		}
	}
	if(ans == 1e9) return -1;
	return ans;
}

long long solve2() {
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < MAXK;++j) {
			dp2[i + N * j] = {1e7,1e7};
		}
	}
	dp2[0] = {0,0};
	for(auto e : v) {
		edges2[e.first].push_back({e.second,{0,1}});
		edges2[e.second + N].push_back({e.first + N,{0,1}});
	}
	for(int i = 0;i < N;++i) {
		edges2[i].push_back({i + N,{1,0}});
		edges2[i + N].push_back({i,{1,0}});
	}
	priority_queue<pair<pair<int,int>,int>> pq;
	pq.push({{0,0},0});
	while(!pq.empty()) {
		pair<pair<int,int>,int> cur = pq.top();
		pq.pop();
		pair<int,int> d = {-cur.first.first,-cur.first.second};
		int v = cur.second;
		if(dp2[v] != d) continue;
		for(auto e : edges2[v]) {
			pair<int,int> nd = {d.first + e.second.first,d.second + e.second.second};
			if(nd >= dp2[e.first]) continue;
			dp2[e.first] = nd;
			pq.push({{-nd.first,-nd.second},e.first});
		}
	}
	long long ans = calc(min(dp2[N - 1],dp2[2 * N - 1]));
	return ans;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		v.push_back({a,b});
	}
	long long ans = solve1();
	if(ans != -1) {
		cout << ans << endl;
		return 0;
	}
	ans = solve2() - 1;
	cout << ans << endl;
	return 0;
}