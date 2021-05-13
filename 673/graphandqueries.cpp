using namespace std;

#include <iostream>
#include <vector>
#include <vector>

#define MAXN 500005

int N,M,Q,root[MAXN],arr[MAXN],x[MAXN],y[MAXN],boss[MAXN],tin[MAXN],tout[MAXN],n,ti;
bool vis[MAXN];
pair<int,int> st[1048576];
bool marked[MAXN];
vector<int> edges[MAXN];
vector<pair<int,int>> q;

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	root[n] = n;
	root[a] = n;
	root[b] = n;
	edges[n].push_back(a);
	edges[n++].push_back(b);
	return;
}

void dfs(int v) {
	vis[v] = true;
	tin[v] = ti++;
	for(int u : edges[v]) dfs(u);
	tout[v] = ti;
	return;
}

void upd(int x,int v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = make_pair(v,x);
		return;
	}
	int m = (l + r) >> 1;
	upd(x,v,l,m,2 * p + 1);
	upd(x,v,m + 1,r,2 * p + 2);
	st[p] = max(st[2 * p + 1],st[2 * p + 2]);
	return;
}

pair<int,int> qry(int a,int b,int l,int r,int p) {
	if(l > b || r < a) return make_pair(0,n);
	if(l >= a && r <= b) return st[p];
	int m = (l + r) >> 1;
	return max(qry(a,b,l,m,2 * p + 1),qry(a,b,m + 1,r,2 * p + 2));
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M >> Q;
	n = N;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		root[i] = i;
	}
	for(int i = 0;i < M;++i) {
		cin >> x[i] >> y[i];
		x[i]--;y[i]--;
	}
	int t = M;
	for(int i = 0;i < Q;++i) {
		int a,b;
		cin >> a >> b;
		b--;
		if(a == 2) {
			marked[b] = true;
		}
		q.push_back({a,b});
	}
	for(int i = 0;i < M;++i) {
		if(!marked[i]) {
			merge(x[i],y[i]);
		}
	}
	for(int i = q.size() - 1;i >= 0;--i) {
		if(q[i].first == 1) {
			boss[i] = findR(q[i].second);
		}else{
			merge(x[q[i].second],y[q[i].second]);
		}
	}
	for(int i = n - 1;i >= 0;--i) {
		if(vis[i]) continue;
		dfs(i);
	}
	for(int i = 0;i < N;++i) {
		upd(tin[i],arr[i],0,MAXN,0);
	}
	for(int i = 0;i < q.size();++i) {
		if(q[i].first == 1) {
			int b = boss[i];
			pair<int,int> m = qry(tin[b],tout[b] - 1,0,MAXN,0);
			cout << m.first << "\n";
			upd(m.second,0,0,MAXN,0);
		}
	}
	return 0;
}