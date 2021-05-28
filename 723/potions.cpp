using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005

int N;
long long arr[MAXN];

long long st[524288],lazy[524288];

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
	st[p] = min(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void update(int x,int y,long long v) {
	update(x,y,v,0,MAXN,0);
}

long long getMin(int a,int b,int l,int r,int p) {
	if(lazy[p]) {
		st[p] += lazy[p];
		if(l != r) {
			lazy[2 * p + 1] += lazy[p];
			lazy[2 * p + 2] += lazy[p];
		}
		lazy[p] = 0;
	}
	if(l > b || r < a) return 1e9;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) >> 1;
	return min(getMin(a,b,l,m,2 * p + 1),getMin(a,b,m + 1,r,2 * p + 2));
}

long long getMin(int a,int b) {
	return getMin(a,b,0,MAXN,0);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N;
	vector<pair<int,int>> v;
	int ans = 0;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		if(arr[i] >= 0) {
			ans++;
			update(i,N - 1,arr[i]);
		}else{
			v.push_back({-arr[i],-i});
		}
	}
	sort(v.begin(),v.end());
	for(auto p : v) {
		int i = -p.second;
		if(getMin(i,N - 1) + arr[i] >= 0) {
			ans++;
			update(i,N - 1,arr[i]);
		}
	}
	cout << ans << endl;
	return 0;
}