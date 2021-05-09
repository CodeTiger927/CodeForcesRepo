using namespace std;

#include <iostream>
#include <queue>
#include <vector>

#define MAXN 405
#define MOD 998244353

int N,M,dist[MAXN][MAXN];
vector<int> edges[MAXN];

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}

	for(int i = 0;i < N;++i) {
		queue<int> q;
		q.push(i);
		dist[i][i] = 1;
		while(!q.empty()) {
			int cur = q.front();
			q.pop();
			for(int j = 0;j < edges[cur].size();++j) {
				int nxt = edges[cur][j];
				if(dist[i][nxt]) continue;
				dist[i][nxt] = dist[i][cur] + 1;
				q.push(nxt);
			}
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			int cnt = 0;
			long long ans = 1;
			for(int k = 0;k < N;++k) {
				if(dist[i][k] + dist[j][k] - 1 == dist[i][j]) cnt++;
			}
			if(cnt > dist[i][j]) ans = 0;
			for(int k = 0;k < N;++k) {
				if(dist[i][k] + dist[k][j] - 1 == dist[i][j]) continue;
				int cnt2 = 0;
				for(int l = 0;l < edges[k].size();++l) {
					int nxt = edges[k][l];
					if(dist[i][k] == dist[i][nxt] + 1 && dist[j][k] == dist[j][nxt] + 1) {
						cnt2++;
					}
				}
				ans = (ans * cnt2) % MOD;
			}
			cout << ans << " ";
		}
		cout << endl;
	}
	return 0;
}