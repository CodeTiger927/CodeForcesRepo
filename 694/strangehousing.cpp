using namespace std;

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define MAXN 300005

int N,M,color[MAXN];
vector<int> edges[MAXN];
bool visited[MAXN];

void solve() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		edges[i].clear();
		visited[i] = false;
		color[i] = 2;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	queue<int> q;
	q.push(0);
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		if(color[cur] != 2) continue;
		color[cur] = 0;
		for(int i = 0;i < edges[cur].size();++i) {
			int nxt = edges[cur][i];
			if(color[nxt] != 2) continue;
			color[nxt] = 1;
			for(int j = 0;j < edges[nxt].size();++j) {
				if(color[edges[nxt][j]] == 2) q.push(edges[nxt][j]);
			}
		}
	}
	vector<int> v;
	for(int i = 0;i < N;++i) {
		if(color[i] == 2) {
			cout << "NO" << endl;
			return;
		}else if(color[i] == 0) {
			v.push_back(i + 1);
		}
	}
	cout << "YES" << endl;
	cout << v.size() << endl;
	for(int i = 0;i < v.size();++i) {
		cout << v[i] << " ";
	}
	cout << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}