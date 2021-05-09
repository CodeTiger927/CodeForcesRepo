using namespace std;

#include <iostream>
#include <vector>
#include <stack>
#include <array>

#define MAXN 500005

int N,Q,K,sz[MAXN],root[MAXN],t,days[MAXN];
vector<pair<int,int>> st[1048576];
vector<int> queries[MAXN + 5];
vector<array<int,4>> v;

int findR(int x) {
	return x == root[x] ? x : findR(root[x]);
}

void merge(int a,int b,stack<pair<pair<int,int>,pair<int,int>>>& s) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a,b);
	s.push({{b,b},{a,sz[a]}});
	root[b] = a;
	sz[a] += sz[b];
	return;
}

void undo(stack<pair<pair<int,int>,pair<int,int>>>& s) {
	while(!s.empty()) {
		auto d = s.top();
		s.pop();
		root[d.first.first] = d.first.second;
		sz[d.second.first] = d.second.second;
	}
	return;
}

void insert(int l,int r,int u,int v,int a,int b,int p) {
	if(l > b || r < a) return;
	if(a >= l && b <= r) {
		st[p].push_back({u,v});
		return;
	}
	int m = (a + b) >> 1;
	insert(l,r,u,v,a,m,2 * p + 1);
	insert(l,r,u,v,m + 1,b,2 * p + 2);
}

void dfs(int l,int r,int p) {
	// cout << l << " " << r << " " << p << endl;
	stack<pair<pair<int,int>,pair<int,int>>> s;
	for(auto p : st[p]) {
		merge(p.first,p.second,s);
	}
	if(l == r) {
		for(auto q : queries[l]) {
			cout << sz[findR(q)] << "\n";
		}
		undo(s);
		return;
	}
	int m = (l + r) >> 1;
	dfs(l,m,2 * p + 1);
	dfs(m + 1,r,2 * p + 2);
	undo(s);
	return;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> Q >> K;
	for(int i = 0;i < N;++i) {
		sz[i] = 1;
		root[i] = i;
	}
	for(int i = 0;i < Q;++i) {
		int q;
		cin >> q;
		if(q == 1) {
			int a,b;
			cin >> a >> b;
			a--;b--;
			v.push_back({t,i,a,b});
		}else if(q == 2) {
			int x;
			cin >> x;
			x--;
			
			queries[i].push_back(x);
		}else{
			days[++t] = i;
		}
	}
	days[++t] = Q;
	for(auto q : v) {
		insert(q[1],days[min(t,q[0] + K)],q[2],q[3],0,MAXN,0);
	}
	dfs(0,MAXN,0);
	return 0;
}