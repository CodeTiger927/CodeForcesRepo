using namespace std;

#include <iostream>
#include <vector>

#define MAXN 500005

int N,lazy[1048576];
pair<int,int> st[1048576];


pair<int,int> merge(pair<int,int> a,pair<int,int> b) {
	if(a.first != b.first) return min(a,b);
	return make_pair(a.first,a.second + b.second);
}

void build(int l,int r,int p) {
	if(l == r) {
		st[p] = make_pair(0,1);
		return;
	}
	int m = (l + r) >> 1;
	build(l,m,2 * p + 1);
	build(m + 1,r,2 * p + 2);
	st[p] = merge(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void push(int p) {
	if(lazy[p]) {
		st[p].first += lazy[p];
		if(2 * p + 2 < 1048576) {
			lazy[2 * p + 1] += lazy[p];
			lazy[2 * p + 2] += lazy[p];
		}
		lazy[p] = 0;
	}
	return;
}

void upd(int a,int b,int v,int l,int r,int p) {
	push(p);
	if(a > r || b < l) return;
	if(l >= a && r <= b) {
		st[p].first += v;
		if(l != r) {
			lazy[2 * p + 1] += v;
			lazy[2 * p + 2] += v;
		}
		return;
	}
	int m = (l + r) >> 1;
	upd(a,b,v,l,m,2 * p + 1);
	upd(a,b,v,m + 1,r,2 * p + 2);
	st[p] = merge(st[2 * p + 1],st[2 * p + 2]);
	return;
}

int qry(int a,int b,int l,int r,int p) {
	push(p);
	if(a > r || b < l) return 0;
	if(l >= a && r <= b) {
		if(st[p].first) return 0;
		return st[p].second;
	}
	int m = (l + r) >> 1;
	int res = qry(a,b,l,m,2 * p + 1) + qry(a,b,m + 1,r,2 * p + 2);
	return res;
}

vector<int> last[MAXN];

int main() {
	cin >> N;
	build(0,N,0);
	for(int i = 1;i <= N;++i) {
		last[i].push_back(0);
	}
	long long ans = 0;
	for(int i = 1;i <= N;++i) {
		// cout << "Hello " << i << endl;
		int cur;
		cin >> cur;
		int k = last[cur].size();
		if(k >= 1) {
			upd(last[cur][k - 1],i - 1,1,0,N,0);
		}
		if(k >= 3) {
			upd(last[cur][k - 3],last[cur][k - 2] - 1,-1,0,N,0);
		}
		if(k >= 4) {
			upd(last[cur][k - 4],last[cur][k - 3] - 1,1,0,N,0);
		}
		ans += qry(0,i - 1,0,N,0);
		last[cur].push_back(i);
	}
	cout << ans << endl;
	return 0;
}