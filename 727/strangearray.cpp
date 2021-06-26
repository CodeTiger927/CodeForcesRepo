using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

struct node {
	int l,r,lz,mi,ma;
	node *lp,*rp;
	node(int _l,int _r):l(_l),r(_r),mi(0),ma(0),lz(0) {
		if(l == r) {
			mi = ma = -l;
			return;
		}
		int m = (l + r) >> 1;
		lp = new node(l,m);
		rp = new node(m + 1,r);
		mi = min(lp -> mi,rp -> mi);
		ma = max(lp -> ma,rp -> ma);
	}
	void push() {
		if(!lz) return;
		mi += lz;
		ma += lz;
		if(l != r) {
			lp -> lz += lz;
			rp -> lz += lz;
		}
		lz = 0;
		return;
	}

	void upd(int a,int b,int x) {
		push();
		if(a > r || b < l) return;
		if(a <= l && b >= r) {
			lz += x;
			push();
			return;
		}
		lp -> upd(a,b,x);
		rp -> upd(a,b,x);
		mi = min(lp -> mi,rp -> mi);
		ma = max(lp -> ma,rp -> ma);
		return;
	}

	int getMin(int a,int b) {
		push();
		if(a > r || b < l) return MAXN;
		if(a <= l && b >= r) {
			return mi;
		}
		return min(lp -> getMin(a,b),rp -> getMin(a,b));
	}

	int getMax(int a,int b) {
		push();
		if(a > r || b < l) return -MAXN;
		if(a <= l && b >= r) {
			return ma;
		}
		return max(lp -> getMax(a,b),rp -> getMax(a,b));
	}
};

int N,arr[MAXN],ans[MAXN];
vector<int> ind[MAXN];
node* st = new node(0,MAXN);

void activate(int x) {st -> upd(x,N,2);}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		ind[arr[i]].push_back(i);
	}
	for(int i = 1;i <= N;++i) {
		for(int j : ind[i]) {
			int cur = st -> getMin(j,N) - st -> getMax(0,j);
			ans[j] = (cur < 0 ? (-cur) / 2 : (cur) / 2);
		}
		for(int j : ind[i]) {
			activate(j);
		}
		for(int j : ind[i]) {
			int cur = st -> getMax(j,N) - st -> getMin(0,j);
			ans[j] = max(ans[j],(cur < 0 ? (1 - cur) / 2 : (cur - 1) / 2));
		}
	}
	for(int i = 1;i <= N;++i) {
		cout << ans[i] << " \n"[i == N];
	}
	return 0;
}