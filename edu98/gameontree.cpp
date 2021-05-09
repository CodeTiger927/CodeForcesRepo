using namespace std;

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAXN 200005
#define MAXM 20

int N,K,sz[MAXN],parent[MAXN],pcd[MAXN],d[MAXN],dpc[MAXN][20],deep[MAXN];
bool blocked[MAXN];
vector<int> edges[MAXN],maxS[MAXN];

void dfs(int cur,int p = -1,int depth = -1) {
	sz[cur] = 1;
	if(p != -1) maxS[p][dpc[cur][depth]] = max(maxS[p][dpc[cur][depth]],d[cur]);
	for(int i = 0;i < edges[cur].size();++i) {
		int next = edges[cur][i];
		if(parent[cur] == next || blocked[next]) continue;
		parent[next] = cur;
		if(depth != -1) {
			dpc[next][depth] = dpc[cur][depth] + 1;
		}
		dfs(next,p,depth);
		sz[cur] += sz[next];
	}
}


int find_centroid(int cur) {
	parent[cur] = cur;
	dfs(cur);
	int centroid = cur;
	int bestSize = sz[cur];

	queue<int> q;
	q.push(centroid);
	while(!q.empty()) {
		int next = q.front();
		q.pop();
		int s = sz[cur] - sz[next];
		for(int i = 0;i < edges[next].size();++i) {
			int nnext = edges[next][i];
			if(nnext == parent[next] || blocked[nnext]) continue;
			s = max(s,sz[nnext]);
			q.push(nnext);
		}

		if(s < bestSize) {
			centroid = next;
			bestSize = s;
		}
	}
	return centroid;
}

int centroidDecomp(int v,int depth = 0) {
	int c = find_centroid(v);
	blocked[c] = true;
	parent[c] = c;
	dpc[c][depth] = 0;
	deep[c] = depth;
	maxS[c].assign(sz[c],0);
	dfs(c,c,depth);
	for(int i = 1;i < maxS[c].size();++i) {
		maxS[c][i] = max(maxS[c][i],maxS[c][i - 1]);
	}

	for(int u : edges[c]) {
		if(u == parent[c] || blocked[u]) continue;
		int n = centroidDecomp(u,depth + 1);
		pcd[n] = c;
	}
	return c;
}

bool check(int v,int x) {
	for(int i = deep[v], u = v;u != -1;u = pcd[u], --i) {
		if(x >= dpc[v][i] && maxS[u][min(int(maxS[u].size() - 1),x - dpc[v][i])] > x) {
			return true;
		}
	}
	return false;
}

int main() {
	cin >> N;
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	memset(d,-1,sizeof(d));
	memset(pcd,-1,sizeof(pcd));
	cin >> K;
	queue<int> q;
	for(int i = 0;i < K;++i) {
		int cur;
		cin >> cur;
		cur--;
		d[cur] = 0;
		q.push(cur);
	}
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		for(int u : edges[cur]) {
			if(d[u] == -1) {
				d[u] = d[cur] + 1;
				q.push(u);
			}
		}
	}
	centroidDecomp(0);
	for(int i = 0;i < N;++i) {
		int l = 0;
		int r = N;
		while(l <= r) {
			int m = (l + r) >> 1;
			if(check(i,m)) {
				l = m + 1;
			}else{
				r = m - 1;
			}
		}
		cout << l << " ";
	}
	cout << endl;
	return 0;
}