using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,M;
vector<int> edges[MAXN];
bool vis[MAXN],vis2[MAXN];

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		edges[i].clear();
		vis[i] = vis2[i] = false;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
	}
	vector<int> ans;
	for(int i = 0;i < N;++i) {
		if(vis2[i]) {
			ans.push_back(i + 1);
			continue;
		}
		for(int u : edges[i]) {
			if(vis[i]) {
				vis2[u] = true;
			}else{
				vis[u] = true; 
			}
		}
	}
	cout << ans.size() << endl;
	for(int x : ans) cout << x << " ";
	cout << endl;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}