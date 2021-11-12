using namespace std;

#include <iostream>
#include <deque>
#include <algorithm>
#include <cstring>

#define MAXN 10005
#define MAXM 1005

int N,M,G,R,d[MAXN],dist[MAXN][MAXM];
deque<pair<int,int>> dq;

void upd(int a,int t,int val) {
	if(t > G) return;
	if(t == G) {
		++val;
		t = 0;
	}
	if(dist[a][t] == -1) {
		dist[a][t] = val;
		if(t) {
			dq.push_front({a,t});
		}else{
			dq.push_back({a,t});
		}
	}
	return;
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < M;++i) {
		cin >> d[i];
	}
	cin >> G >> R;
	sort(d,d + M);
	memset(dist,-1,sizeof(dist));
	dq.push_back({0,0});
	dist[0][0] = 0;
	while(!dq.empty()) {
		pair<int,int> cur = dq.front();
		dq.pop_front();
		// cout << cur.first << " " << cur.second << endl;
		if(cur.first) {
			upd(cur.first - 1,cur.second + d[cur.first] - d[cur.first - 1],dist[cur.first][cur.second]);
		}
		if(cur.first + 1 < M) {
			// cout << cur.second + d[cur.first + 1] - d[cur.first] << endl;
			upd(cur.first + 1,cur.second + d[cur.first + 1] - d[cur.first],dist[cur.first][cur.second]);
		}
	}

	long long ans = 1e18;
	for(int i = 0;i < G;++i) {
		if(dist[M - 1][i] == -1) continue;
		ans = min(ans,1ll * dist[M - 1][i] * (G + R) + i - (i ? 0 : R)); 
	}
	cout << (ans == 1e18 ? -1 : ans) << endl;
	return 0;
}