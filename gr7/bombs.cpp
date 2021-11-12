using namespace std;

#include <iostream>

#define MAXN 300005

long long st[1048576],lazy[1048576];

void update(int x,int y,long long v,int l,int r,int p) {
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

void update(int x,int y,long long v) {
	update(x,y,v,0,MAXN,0);
}

long long getMax(int a,int b,int l,int r,int p) {
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

long long getMax(int a,int b) {
	return getMax(a,b,0,MAXN,0);
}

// st,i = # of numbers >= x - # of bombs. If it's ever positive then ree

int N,a[MAXN],b[MAXN],rev[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 0;i < N;++i) {
		cin >> a[i];
		rev[a[i]] = i;
	}
	for(int i = 0;i < N;++i) {
		cin >> b[i];
	}
	int x = N + 1;
	for(int i = 0;i < N;++i) {
		while(getMax(0,N - 1) <= 0) {
			update(0,rev[--x],1);
		}
		cout << x << " \n"[i == N - 1];
		update(0,b[i] - 1,-1);
	}
	return 0;
}