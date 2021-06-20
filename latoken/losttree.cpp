// O(N - max_depth - last_layer + 1)

using namespace std;

#include <iostream>
#include <vector>
#include <assert.h>

#define MAXN 2005

int N,res[MAXN],dep[MAXN],cnt;
vector<int> lvls[MAXN];
bool vis[MAXN];
vector<pair<int,int>> edges;

void ask(int x) {
	cnt++;
	cout << "? " << x << endl;
	for(int i = 1;i <= N;++i) {
		cin >> res[i];
	}
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	ask(1);
	int maxD = 0;
	int odd = 0;
	for(int i = 1;i <= N;++i) {
		dep[i] = res[i];
		lvls[dep[i]].push_back(i);
		maxD = max(maxD,dep[i]);
		if(dep[i] == 1) edges.push_back({1,i});
		if(dep[i] & 1) odd++;
	}
	int start = 2 - (odd < (N - 1 - odd));
	for(int i = start;i <= maxD;i += 2) {
		for(int j : lvls[i]) {
			ask(j);
			for(int k = 2;k <= N;++k) {
				if(res[k] == 1) edges.push_back({j,k});
			}
		}
	}
	
	cout << "!" << endl;
	assert(edges.size() == N - 1);
	assert(cnt <= (N + 1) / 2);
	for(int i = 0;i < N - 1;++i) {
		cout << edges[i].first << " " << edges[i].second << endl;
	}
	return 0;
}