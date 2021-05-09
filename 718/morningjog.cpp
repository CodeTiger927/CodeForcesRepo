using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>

#define MAXN 105

int N,M,arr[MAXN][MAXN],ans[MAXN][MAXN];
vector<int> le[MAXN];

void solve() {
	vector<pair<int,pair<int,int>>> v;
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		le[i].clear();
		for(int j = 0;j < M;++j) {
			cin >> arr[i][j];
			ans[i][j] = -1;
			v.push_back({arr[i][j],{i,j}});
		}
	}
	sort(v.begin(),v.end());
	for(int i = 0;i < M;++i) {
		pair<int,int> cur = v[i].second;
		ans[cur.first][i] = v[i].first;
	}
	for(int i = M;i < N * M;++i) {
		le[v[i].second.first].push_back(v[i].second.second);
	}
	for(int i = 0;i < N;++i) {
		int ptr = 0;
		for(int j = 0;j < M;++j) {
			if(ans[i][j] != -1) continue;
			ans[i][j] = arr[i][le[i][ptr++]];
		}
	}


	for(int i = 0;i < N;++i) {
		for(int j = 0;j < M;++j) {
			cout << ans[i][j] << " ";
		}
		cout << endl;
	}
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}