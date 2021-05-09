using namespace std;

#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

#define MAXN 1005

int N,ans[MAXN],cnt,arr[MAXN][MAXN],belong[MAXN];
set<int> sets[MAXN];
vector<pair<int,int>> edges;

int solve(vector<int> all) {
	if(all.size() == 1) return all[0];
	int cur = ++cnt;
	ans[cur] = *prev(sets[all[0]].end());
	
	vector<int> groups[MAXN];
	for(int i = 0;i < MAXN;++i) {
		groups[i].clear();
	}
	for(int i = 0;i < all.size();++i) {
		belong[i] = -1;
		sets[all[i]].erase(ans[cur]);
	}
	int cnt2 = 0;
	for(int i = 0;i < all.size();++i) {
		for(int j = 0;j < i;++j) {
			if(arr[all[i]][all[j]] < ans[cur]) {
				belong[i] = belong[j];
				break;
			}
		}
		if(belong[i] == -1) belong[i] = cnt2++;
		groups[belong[i]].push_back(all[i]);
	}
	for(int i = 0;i < cnt2;++i) {
		int nxt = solve(groups[i]);
		edges.push_back({nxt,cur});
	}
	return cur;
}

int main() {
	cin >> N;
	vector<int> all;
	for(int i = 1;i <= N;++i) {
		all.push_back(i);
		for(int j = 1;j <= N;++j) {
			cin >> arr[i][j];
			sets[i].insert(arr[i][j]);
		}
		ans[i] = *(sets[i].begin());
		sets[i].erase(sets[i].begin());
	}
	cnt = N;
	int root = solve(all);
	cout << cnt << endl;
	for(int i = 1;i <= cnt;++i) {
		cout << ans[i] << " ";
	}
	cout << endl;
	cout << root << endl;
	for(int i = 0;i < edges.size();++i) {
		cout << edges[i].first << " " << edges[i].second << endl;
	}
}