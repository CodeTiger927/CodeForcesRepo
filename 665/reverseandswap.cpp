using namespace std;

#include <iostream>

#define MAXN 262144

int N,Q,X;
long long st[524288];

long long getSum(int a,int b,int l,int r,int p) {
	if(a > r || b < l) return 0;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) >> 1;
	return getSum(a,b,l,m,2 * p + 1) + getSum(a,b,m + 1,r,2 * p + 2);
}

void upd(int x,int v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = v;
		return;
	}
	int m = (l + r) >> 1;
	upd(x,v,l,m,2 * p + 1);
	upd(x,v,m + 1,r,2 * p + 2);
	st[p] = st[2 * p + 1] + st[2 * p + 2];
	return;
}

long long answer(int a,int b,int l,int r,int x) {
	if(a > r || b < l) return 0;
	if(l >= a && r <= b) {
		int d = r - l;
		int nx = (x | d) - d;
		l ^= nx;
		r ^= nx;
		return getSum(l,r,0,MAXN - 1,0);
	}
	int m = (l + r) >> 1;
	return answer(a,b,l,m,x) + answer(a,b,m + 1,r,x);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> Q;
	for(int i = 0;i < (1 << N);++i) {
		cin >> st[MAXN + i - 1];
	}
	for(int i = MAXN - 2;i >= 0;--i) {
		st[i] = st[(i << 1) + 1] + st[(i << 1) + 2];
	}
	for(int i = 0;i < Q;++i) {
		int t;
		cin >> t;
		if(t == 1) {
			int x,k;
			cin >> x >> k;
			x--;
			upd(x ^ X,k,0,MAXN - 1,0);
		}else if(t == 2) {
			int k;
			cin >> k;
			X ^= (1 << k) - 1;
		}else if(t == 3) {
			int k;
			cin >> k;
			X ^= (1 << k);
		}else{
			int l,r;
			cin >> l >> r;
			l--;r--;
			cout << answer(l,r,0,MAXN - 1,X) << "\n";
		}
	}
	return 0;
}