using namespace std;

#include <iostream>

#define MAXN 100005

long long dp[MAXN];

struct node {
	int l,r,val,lazy;
	node* lp;
	node* rp;
	node(int l,int r): l(l),r(r) {
		val = lazy = 0;
		if(l != r) {
			int m = (l + r) >> 1;
			lp = new node(l,m);
			rp = new node(m + 1,r);
			val = max(lp -> val,rp -> val);
		}else{
			val = dp[l];
		}
	}

	void push() {
		if(!lazy) return;
		val += lazy;
		if(l != r) {
			lp -> lazy += lazy;
			rp -> lazy += lazy;
		}
		lazy = 0;
		return;
	}

	void upd(int a,int b,int v) {
		push();
		if(l > b || r < a) return;
		if(l >= a && r <= b) {
			lazy += v;			
			push();
			return;
		}
		int m = (l + r) >> 1;
		lp -> upd(a,b,v);
		rp -> upd(a,b,v);
		val = max(lp -> val,rp -> val);
	}

	int qry(int a,int b) {
		push();
		if(l > b || r < a) return 0;
		if(l >= a && r <= b) {
			return val;
		}
		int m = (l + r) >> 1;
		return max(lp -> qry(a,b),rp -> qry(a,b));
	}
};

int N,K,arr[MAXN],pre[MAXN],nxt[MAXN],last[MAXN];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> K;
	long long res = 0;
	for(int i = 1;i <= N;++i) {
		cin >> arr[i];
		pre[i] = last[arr[i]];
		nxt[last[arr[i]]] = i;
		last[arr[i]] = i;
		if(pre[i]) res += i - pre[i];
	}
	for(int i = 0;i < K;++i) {
		node n(0,N);
		long long cur = 0;
		for(int j = 1;j <= N;++j) {
			if(pre[j]) {
				cur += pre[j] - j;
				n.upd(pre[j],j - 1,j - pre[j]);
			}
			if(nxt[j]) {
				cur += nxt[j] - j;
				n.upd(j,nxt[j] - 1,j - nxt[j]);
			}
			dp[j] = n.qry(0,j - 1) + cur;
		}
	}
	cout << res - dp[N] << endl;
	return 0;
}