using namespace std;

#include <iostream>
#include <queue>
#include <vector>

#define MAXN 200005
#define INF 1e9

int dp[MAXN][2][55],N,M;
vector<pair<int,int>> edges[MAXN];

int sq(int x) {
	return x * x;
}

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
		for(int j = 0;j < 55;++j) {
			dp[i][0][j] = dp[i][1][j] = INF;
		}
	}
	priority_queue<pair<int,pair<int,pair<int,int>>>> pq;
	pq.push({0,{0,{0,0}}});
	dp[0][0][0] = 0;
	while(!pq.empty()) {
		pair<int,pair<int,pair<int,int>>> cur = pq.top();
		pq.pop();
		int curN = cur.second.first;
		bool curB = cur.second.second.first;
		int lastD = cur.second.second.second;
		int curD = -cur.first;
		if(dp[curN][curB][lastD] != curD) continue;
		for(int i = 0;i < edges[curN].size();++i) {
			pair<int,int> nxt = edges[curN][i];
			if(curB) {
				if(dp[curN][curB][lastD] + sq(lastD + nxt.second) < dp[nxt.first][0][0])  {
					dp[nxt.first][0][0] = dp[curN][curB][lastD] + sq(lastD + nxt.second);
					pq.push({-dp[nxt.first][0][0],{nxt.first,{0,0}}});
				}
			}else{
				if(dp[curN][curB][lastD] < dp[nxt.first][1][nxt.second]) {
					dp[nxt.first][1][nxt.second] = dp[curN][curB][lastD];
					pq.push({-dp[nxt.first][1][nxt.second],{nxt.first,{1,nxt.second}}});
				}
			}
		}
	}
	for(int i = 0;i < N;++i) {
		cout << (dp[i][0][0] == INF ? -1 : dp[i][0][0]) << " ";
	}
	cout << endl;
	return 0;
}