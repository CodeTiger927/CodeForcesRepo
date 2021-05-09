using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAXN 100005

int N,M,K,deg[MAXN];
vector<int> edges[MAXN];

void solve() {
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		deg[i] = 0;
		edges[i].clear();
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		deg[a]++;deg[b]++;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	if(K > 500) {
		cout << -1 << endl;
		return;
	}
	queue<int> q;
	for(int i = 0;i < N;++i) {
		if(deg[i] < K) q.push(i);
		sort(edges[i].begin(),edges[i].end());
	}
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		if(deg[cur] == K - 1) {
			vector<int> cand;
			for(int u : edges[cur]) if(deg[u] >= K - 1) cand.push_back(u);
			cand.push_back(cur);
			if(cand.size() == K) {
				bool work = true;
				for(int i = 0;i < cand.size();++i) {
					for(int j = i + 1;j < cand.size();++j) {
						auto itr = lower_bound(edges[cand[i]].begin(),edges[cand[i]].end(),cand[j]);
						work &= (itr != edges[cand[i]].end() && *itr == cand[j]);
					}
				}
				if(work) {
					cout << 2 << endl;
					for(int u : cand) cout << (u + 1) << " ";
					cout << endl;
					return;
				}
			}
		}

		for(int u : edges[cur]) {
			deg[u]--;
			if(deg[u] == K - 1) q.push(u);
		}
		deg[cur] = -1;
	}
	vector<int> le;
	for(int i = 0;i < N;++i) {
		if(deg[i] >= K) le.push_back(i);
	}
	if(le.size()) {
		cout << 1 << " " << le.size() << endl;
		for(int u : le) cout << (u + 1) << " ";
		cout << endl;
	}else{
		cout << -1 << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}