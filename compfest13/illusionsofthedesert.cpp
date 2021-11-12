// HLD + LCA + Euler Tour + Segtree
// Very versatile

using namespace std;

#include <iostream>
#include <vector>
#include <cstring>

#define MAXN 100005

vector<int> edges[MAXN];
// sn is the logN
int parent[MAXN][20],sz[MAXN],depth[MAXN],in[MAXN],out[MAXN],sn;

// Temporary
bool visited[MAXN];
int t = 0;

void init(int s) {
	memset(visited,0,sizeof(visited));
	sn = s;
}

int dfs(int u = 0) {
	sz[u] = 1;
	visited[u] = true;
	in[u] = t++;
	for(int i = 0;i < edges[u].size();i++) {
		int c = edges[u][i];
		if(visited[c]) continue;

		visited[c] = true;
		parent[c][0] = u;
		depth[c] = depth[u] + 1;
		sz[u] += dfs(c);
	}
	out[u] = t;
	return sz[u];
}

void preCompSparseMatrix() {
	for(int i = 1;i < 20;i++) {
		for(int j = 0;j < sn;j++) {
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
		}
	}
}

int LCA(int u,int v) {
	if(depth[v] < depth[u]) return LCA(v,u);

	int dif = depth[v] - depth[u];
	for(int i = 0;i < 20;i++) {
		if((dif >> i) & 1) {
			v = parent[v][i];
		}
	}

	if(u == v) {
		return u;
	}

	for(int i = 19;i >= 0;i--) {
		if(parent[u][i] != parent[v][i]) {
			u = parent[u][i];
			v = parent[v][i];
		}
	}

	return parent[u][0];
}

long long st[262144];

void update(int x,long long v,int l,int r,int p) {
	if(l > x || r < x) return;
	st[p] += v;
	if(l == r) return;
	int m = (l + r) / 2;
	update(x,v,l,m,2 * p + 1);
	update(x,v,m + 1,r,2 * p + 2);
	st[p] = st[2 * p + 1] + st[2 * p + 2];
	return;
}

void update(int x,long long v) {
	update(x,v,0,MAXN,0);
}

long long getSum(int a,int b,int l,int r,int p) {
	if(l > b || r < a) return 0;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) / 2;
	return getSum(a,b,l,m,2 * p + 1) + getSum(a,b,m + 1,r,2 * p + 2);
}

long long getSum(int a,int b) {
	return getSum(a,b,0,MAXN,0);
}

int N,Q;
long long arr[MAXN];

long long get(int a,int b) {
	int l = LCA(a,b);
	// cout << b << " " << in[b] << " " << getSum(0,in[b]) << endl;
	return getSum(0,in[a]) + getSum(0,in[b]) - 2ll * getSum(0,in[l]) + arr[l];
}

void change(int a,long long b) {
	update(in[a],b);
	update(out[a],-b);
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		arr[i] = abs(arr[i]);
	}
	for(int i = 0;i < N - 1;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	// Add Edges first
	init(N); // 20 is logN
	dfs(0);
	preCompSparseMatrix();
	for(int i = 0;i < N;++i) {
		change(i,arr[i]);
	}

	for(int i = 0;i < Q;++i) {
		int a,b,c;
		cin >> a >> b >> c;
		c = abs(c);
		if(a == 1) {
			b--;
			change(b,c - arr[b]);
			arr[b] = c;
		}else{
			b--;c--;
			// cout << get(b,c) << endl;
			cout << 2ll * get(b,c) - arr[b] - arr[c]  << "\n";
		}
	}
	return 0;
}