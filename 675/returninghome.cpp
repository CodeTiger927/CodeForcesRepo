using namespace std;

#include <iostream>
#include <vector>
#include <set>
#include <queue>

#define MAXN 100005

int N,M;
long long ex,ey,dist[MAXN],x[MAXN],y[MAXN];
set<pair<long long,int>> xs,ys;
vector<int> edges[MAXN];

long long calcD(int a,int b) {
	return min(abs(x[a] - x[b]),abs(y[a] - y[b]));
}

int main() {
	cin >> N >> M >> x[0] >> y[0] >> ex >> ey;
	xs.insert({x[0],0});
	ys.insert({y[0],0});
	for(int i = 1;i <= M;++i) {
		cin >> x[i] >> y[i];
		dist[i] = 1e15;
		xs.insert({x[i],i});
		ys.insert({y[i],i});
	}
	for(auto itr = xs.begin();itr != xs.end();++itr) {
		if(itr != xs.begin()) {
			edges[itr -> second].push_back(prev(itr) -> second);
		}
		if(next(itr) != xs.end()) {
			edges[itr -> second].push_back(next(itr) -> second);
		}
	}
	for(auto itr = ys.begin();itr != ys.end();++itr) {
		if(itr != ys.begin()) {
			edges[itr -> second].push_back(prev(itr) -> second);
		}
		if(next(itr) != ys.end()) {
			edges[itr -> second].push_back(next(itr) -> second);
		}
	}

	priority_queue<pair<long long,int>> pq;
	pq.push({0,0});
	while(!pq.empty()) {
		pair<long long,int> cur = pq.top();
		pq.pop();		long long curD = -cur.first;
		int v = cur.second;
		if(dist[v] != curD) continue;
		for(int u : edges[v]) {
			long long nd = curD + calcD(u,v);
			if(nd < dist[u]) {
				dist[u] = nd;
				pq.push({-nd,u});
			}
		}
	}
	long long ans = 1e15;
	for(int i = 0;i <= M;++i) {
		ans = min(ans,dist[i] + abs(x[i] - ex) + abs(y[i] - ey));
	}
	cout << ans << endl;
	return 0;
}