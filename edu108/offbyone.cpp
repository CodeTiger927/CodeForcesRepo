using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#define MAXN 400005

pair<long long,long long> norm(long long x,long long y) {
	long long g = __gcd(x,y);
	return {x / g,y / g};
}

int N,vis[MAXN];
vector<pair<int,int>> edges[MAXN],ans;
map<pair<long long,long long>,int> m;

int dfs(int v) {
	vis[v] = 1;
	int cur = -1;
	for(auto e : edges[v]) {
		int u = e.first;
		int id = e.second;
		if(vis[u] == 1) continue;
		int nw = id;
		if(!vis[u]) {
			int tmp = dfs(u);
			if(tmp != -1) {
				ans.push_back({tmp,nw});
				nw = -1;
			}
		}
		if(nw != -1) {
			if(cur != -1) {
				ans.push_back({nw,cur});
				cur = -1;
			}else{
				cur = nw;
			}
		}
	}
	vis[v] = 2;
	return cur;
}

int main() {
	cin >> N;
	for(int i = 1;i <= N;++i) {
		long long a,b,c,d;
		cin >> a >> b >> c >> d;
		pair<long long,long long> p1 = norm((a + b) * d,b * c);
		pair<long long,long long> p2 = norm(a * d,(c + d) * b);
		if(m.find(p1) == m.end()) {
			m[p1] = m.size();
		}
		if(m.find(p2) == m.end()) {
			m[p2] = m.size();
		}
		edges[m[p1]].push_back({m[p2],i});
		edges[m[p2]].push_back({m[p1],i});
	}
	for(int i = 0;i < m.size();++i) {
		if(!vis[i]) dfs(i);
	}
	cout << ans.size() << endl;
	for(pair<int,int> p : ans) cout << p.first << " " << p.second << endl;
	return 0;
}