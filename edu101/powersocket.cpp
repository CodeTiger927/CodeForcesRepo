using namespace std;

#include <iostream>
#include <algorithm>

#define MAXN 200005

long long st[4 * MAXN],lazy[4 * MAXN];

void update(int x,int y,long long v,int l,int r,int p) {
	if(lazy[p]) {
		st[p] += 1ll * (r - l + 1) * lazy[p]; 
		if(l != r) {
			lazy[2 * p + 1] += lazy[p];
			lazy[2 * p + 2] += lazy[p];
		}
		lazy[p] = 0;
	}
	if(l > y || r < x) return;

	if(l >= x && r <= y) {
		st[p] += 1ll * (r - l + 1) * v;
		if(l != r) {
			lazy[2 * p + 1] += v;
			lazy[2 * p + 2] += v;
		}
		return;
	}
	int m = (l + r) >> 1;
	update(x,y,v,l,m,2 * p + 1);
	update(x,y,v,m + 1,r,2 * p + 2);
	st[p] = st[2 * p + 1] + st[2 * p + 2];
	return;
}

void update(int x,int y,long long v) {
	update(x,y,v,0,MAXN,0);
}

long long getSum(int a,int b,int l,int r,int p) {
	if(lazy[p]) {
		st[p] += lazy[p] * (r - l + 1);
		if(l != r) {
			lazy[2 * p + 1] += lazy[p];
			lazy[2 * p + 2] += lazy[p];
		}
		lazy[p] = 0;
	}
	if(l > b || r < a) return 0;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) >> 1;
	return getSum(a,b,l,m,2 * p + 1) + getSum(a,b,m + 1,r,2 * p + 2);
}

long long getSum(int a,int b) {
	return getSum(a,b,0,MAXN,0);
}

int N,K,arr[MAXN];

int main() {
	cin >> N >> K;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(arr,arr + N);
	update(0,0,1);
	int curl = 0;
	int ans = 1e9;
	for(int i = N - 1;i >= 0;--i) {
		while(curl < MAXN && getSum(0,curl) == 0) curl++;
		update(curl,curl,-1);
		update(curl + 2,curl + 1 + arr[i] / 2,1);
		update(curl + 2,curl + 1 + (arr[i] - 1) / 2,1);
		int l = 0;
		int r = MAXN - 1;
		while(l < r) {
			int m = (l + r) >> 1;
			if(getSum(0,m) >= K) {
				r = m;
			}else{
				l = m + 1;
			}
		}
		if(getSum(0,ans) >= K) ans = min(ans,l);
	}
	cout << (ans == 1e9 ? -1 : ans) << endl;
	return 0;
}