using namespace std;

#include <iostream>
#include <vector>
#include <queue>

#define MAXN 500005

int N,M,w[MAXN],b[MAXN],dp[MAXN],col[MAXN];
vector<int> ew[MAXN],eb[MAXN];

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int x,y,t;
		cin >> x >> y >> t;
		x--;y--;
		if(t) {
			ew[y].push_back(x);
		}else{
			eb[y].push_back(x);
		}
	}
	for(int i = 0;i < N - 1;++i) {
		w[i] = b[i] = dp[i] = N;
	}
	queue<int> q;
	q.push(N - 1);
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : eb[u]) {
			if(b[v] < N) continue;
			b[v] = dp[u] + 1;
			if(max(b[v],w[v]) < N) {
				q.push(v);
				dp[v] = max(b[v],w[v]);
			}
		}
		for(int v : ew[u]) {
			if(w[v] < N) continue;
			w[v] = dp[u] + 1;
			if(max(w[v],b[v]) < N) {
				q.push(v);
				dp[v] = max(b[v],w[v]);
			}
		}
	}
	cout << (dp[0] == N ? -1 : dp[0]) << endl;
	for(int i = 0;i < N;++i) {
		cout << (b[i] > w[i] ? 0 : 1);
	}
	cout << endl;
	return 0;
}