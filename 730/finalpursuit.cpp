using namespace std;

#include <iostream>
#include <vector>
#include <set>

#define MAXN 100005

int N,M,p[MAXN],ans[MAXN],tmp[MAXN];
vector<int> edges[MAXN];
set<int> s[MAXN];
bool used[MAXN];

void solve() {
	cin >> N;
	M = 1 << N;
	for(int i = 0;i < M;++i) {
		edges[i].clear();
		s[i].clear();
		used[i] = 0;
	}
	for(int i = 0;i < N * M / 2;++i) {
		int a,b;
		cin >> a >> b;
		edges[a].push_back(b);
		edges[b].push_back(a);
		s[a].insert(b);
		s[b].insert(a);
	}
	used[0] = true;
	for(int i = 1;i < M;++i) {
		vector<int> v;
		for(int j = 0;j < N;++j) {
			int n = i ^ (1 << j);
			if(n < i) v.push_back(n);
		}
		if(v.size() == 1) {
			int n = v[0];
			for(int j = 0;j < edges[p[n]].size();++j) {
				int u = edges[p[n]][j];
				if(used[u]) continue;
				p[i] = u;
				used[u] = true;
				break;
			}
		}else{
			int n = v[0];
			for(int j = 0;j < edges[p[n]].size();++j) {
				int u = edges[p[n]][j];
				if(used[u]) continue;
				if(s[u].count(p[v[1]])) {
					p[i] = u;
					used[u] = true;
					break;
				}
			}
		}
	}
	for(int i = 0;i < M;++i) {
		cout << p[i] << " \n"[i == M - 1];
	}
	if(N & (N - 1)) {
		cout << -1 << endl;
		return;
	}
	for(int i = 0;i < M;++i) {
		int cur = 0;
		for(int j = 0;j < N;++j) {
			cur ^= j * ((i >> j) & 1);
		}
		ans[p[i]] = cur;
	}
	for(int i = 0;i < M;++i) {
		cout << ans[i] << " \n"[i == M - 1];
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
}