using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005

int N,cmp;
long long P,arr[MAXN];

long long gcd(long long a,long long b) {
	if(a == 0) return b;
	if(b == 0) return a;
	if(a == 1 || b == 1) return 1;
	if(a > b) swap(a,b);
	return gcd(b % a,a);
}

long long st[524288];

void update(int x,long long v,int l,int r,int p) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = v;
		return;
	}
	int m = (l + r) / 2;
	update(x,v,l,m,2 * p + 1);
	update(x,v,m + 1,r,2 * p + 2);
	st[p] = gcd(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void update(int x,long long v) {
	update(x,v,0,MAXN,0);
}

long long getSum(int a,int b,int l,int r,int p) {
	if(l > b || r < a) return 0;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) / 2;
	return gcd(getSum(a,b,l,m,2 * p + 1),getSum(a,b,m + 1,r,2 * p + 2));
}

long long getSum(int a,int b) {
	return getSum(a,b,0,MAXN,0);
}

// Disjoint Union Find DSU
int root[MAXN],szDSU[MAXN],le[MAXN],ri[MAXN];

// Call this first please
void initDSU() {
	cmp = N;
	for(int i = 0;i < N;++i) {
		root[i] = i;		
		szDSU[i] = 1;
		le[i] = ri[i] = i;
	}
}

int findR(int x) {
	if(root[x] != root[root[x]]) {
		root[x] = findR(root[x]);
	}
	return root[x];
}

void mergeDSU(int a,int b) {
	int aR = findR(a);
	int bR = findR(b);
	if(aR == bR) return;
	cmp--;
	if(szDSU[aR] > szDSU[bR]) swap(aR,bR);
	szDSU[bR] += szDSU[aR];
	le[bR] = min(le[bR],le[aR]);
	ri[bR] = max(ri[bR],ri[aR]);
	root[aR] = bR;
	return;
}

void solve() {
	long long ans = 0;
	cin >> N >> P;
	vector<pair<long long,int>> v;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		v.push_back({arr[i],i});
		update(i,arr[i]);
	}
	initDSU();
	sort(v.begin(),v.end());
	
	for(int i = 0;i < N;++i) {
		
		if(v[i].first >= P) break;
		int curI = v[i].second;
		int l = le[findR(curI)] - 1;
		while(l >= 0) {
			if(getSum(l,curI) == arr[curI]) {
				ans += arr[curI];
				mergeDSU(l,curI);
				l = le[findR(l)] - 1;
			}else{
				break;
			}
		}
		int r = ri[findR(curI)] + 1;
		while(r < N) {
			if(getSum(curI,r) == arr[curI]) {
				ans += arr[curI];
				mergeDSU(r,curI);
				r = ri[findR(r)] + 1;
			}else{
				break;
			}
		}
	}
	ans += 1ll * (cmp - 1) * P;
	cout << ans << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}