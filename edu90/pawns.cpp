using namespace std;

#include <iostream>
#include <set>

#define MAXN 200005

int st[1048576],lazy[1048576];

void update(int x,int y,int v,int l,int r,int p) {
	if(lazy[p]) {
		st[p] += lazy[p]; 
		if(l != r) {
			lazy[2 * p + 1] += lazy[p];
			lazy[2 * p + 2] += lazy[p];
		}
		lazy[p] = 0;
	}
	if(l > y || r < x) return;

	if(l >= x && r <= y) {
		st[p] += v;
		if(l != r) {
			lazy[2 * p + 1] += v;
			lazy[2 * p + 2] += v;
		}
		return;
	}
	int m = (l + r) >> 1;
	update(x,y,v,l,m,2 * p + 1);
	update(x,y,v,m + 1,r,2 * p + 2);
	st[p] = max(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void update(int x,int y,int v) {
	update(x,y,v,0,2 * MAXN,0);
}

int getMax(int a,int b,int l,int r,int p) {
	if(lazy[p]) {
		st[p] += lazy[p];
		if(l != r) {
			lazy[2 * p + 1] += lazy[p];
			lazy[2 * p + 2] += lazy[p];
		}
		lazy[p] = 0;
	}
	if(l > b || r < a) return 0;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) >> 1;
	return max(getMax(a,b,l,m,2 * p + 1),getMax(a,b,m + 1,r,2 * p + 2));
}

int getMax(int a,int b) {
	return getMax(a,b,0,2 * MAXN,0);
}

int N,M,K,cnt[2 * MAXN];
set<int> s;
set<pair<int,int>> sp;

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K >> M;
	for(int i = 0;i < 2 * N;++i) {
		update(i,i,i);
	}
	for(int i = 0;i < M;++i) {
		int x,y;
		cin >> x >> y;
		int pos = abs(x - K) + y - 1;
		if(sp.count({x,y})) {
			sp.erase({x,y});
			if(--cnt[pos] == 0) s.erase(pos);
			update(0,pos + 1,-1);
		}else{
			++cnt[pos];
			sp.insert({x,y});
			s.insert(pos);
			update(0,pos + 1,1);
		}
		if(s.empty()) {
			cout << 0 << endl;
			continue;
		}
		int ans = max(0,getMax(0,*s.rbegin() + 1) - N - 1);
		cout << ans << endl;
	}
	return 0;
}