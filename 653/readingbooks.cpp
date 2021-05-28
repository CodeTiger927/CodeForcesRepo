using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define INF 0x7e7e7e7e

int N,M,K;
vector<pair<int,int>> a[4],v[4];
vector<int> ans;

int f(int x,bool store) {
	int res = v[x].back().first;
	if(store) ans.push_back(v[x].back().second);
	v[x].pop_back();
	return res;
}

int solve(int x,bool store) {
	for(int i = 0;i < 4;++i) v[i] = a[i];

	int res = 0;
	for(int i = 0;i < x;++i) {
		res += f(3,store);
	}
	for(int i = x;i < K;++i) {
		for(int j = 1;j <= 2;++j) {
			if(v[j].empty()) return INF - x;
			res += f(j,store);
		}
	}
	for(int i = 2 * K - x;i < M;++i) {
		int b = -1;
		for(int j = 0;j < 4;++j) {
			if(!v[j].empty() && (b == -1 || v[j].back() < v[b].back())) b = j;
		}
		if(b == -1) return INF - x;
		res += f(b,store);
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		int t,x,y;
		cin >> t >> x >> y;
		a[(x << 1) + y].push_back({t,i + 1});
	}
	for(int i = 0;i < 4;++i) {
		sort(a[i].begin(),a[i].end(),greater<pair<int,int>>());
	}
	int l = max(0,2 * K - M);
	int r = min(K,(int)a[3].size());

	while(l < r) {
		int m = (l + r) >> 1;
		if(solve(m,0) > solve(m + 1,0)) {
			l = m + 1;
		}else{
			r = m;
		}
	}
	if(l > r) {
		cout << -1 << endl;
		return 0;
	}
	int res = solve(l,1);
	if(ans.size() != M) {
		cout << -1 << endl;
		return 0;
	}
	cout << res << endl;
	for(int x : ans) cout << x << " ";
	cout << endl;
}