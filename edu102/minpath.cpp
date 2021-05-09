using namespace std;

#include <iostream>
#include <vector>
#include <queue>

#define MAXN 200005
#define INF 1e15

int N,M;
long long dist[MAXN][2][2];
vector<pair<int,long long>> edges[MAXN];

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		a--;b--;
		edges[a].push_back({b,c});
		edges[b].push_back({a,c});
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < 2;++j) {
			for(int k = 0;k < 2;++k) {
				dist[i][j][k] = INF;
			}
		}
	}
	dist[0][0][0] = 0;
	priority_queue<pair<long long,pair<int,pair<int,int>>>> pq;
	pq.push({0,{0,{0,0}}});
	while(!pq.empty()) {
		pair<long long,pair<int,pair<int,int>>> cur = pq.top();
		pq.pop();
		long long curD = -cur.first;
		int curN = cur.second.first;
		int b1 = cur.second.second.first;
		int b2 = cur.second.second.second;
		if(curD != dist[curN][b1][b2]) continue;
		for(int i = 0;i < edges[curN].size();++i) {
			pair<int,long long> nxt = edges[curN][i];
			int n = nxt.first;
			long long d = nxt.second;
			if(!b1) {
				if(curD < dist[n][1][b2]) {
					dist[n][1][b2] = curD;
					pq.push({-curD,{n,{1,b2}}});
				}
			}
			if(!b2) {
				if(curD + 2 * d < dist[n][b1][1]) {
					dist[n][b1][1] = curD + 2 * d;
					pq.push({-curD - 2 * d,{n,{b1,1}}});
				}
			}
			if(!b1 && !b2) {
				if(curD + d < dist[n][1][1]) {
					dist[n][1][1] = curD + d;
					pq.push({-curD - d,{n,{1,1}}});
				}
			}
			if(curD + d < dist[n][b1][b2]) {
				dist[n][b1][b2] = curD + d;
				pq.push({-curD - d,{n,{b1,b2}}});
			}
		}
	}
	for(int i = 1;i < N;++i) {
		cout << dist[i][1][1] << " ";
	}
	return 0;
}