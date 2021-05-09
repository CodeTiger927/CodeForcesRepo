using namespace std;

#include <iostream>
#include <set>
#include <algorithm>
#include <vector>

#define MAXN 300005

int N,nxt[MAXN],pre[MAXN];
long long hei[MAXN],arr[MAXN],dp[MAXN];

long long st1[1048576],st2[1048576];

void update(int x,long long v,int l,int r,int p,long long* st) {
	if(l > x || r < x) return;
	if(l == r) {
		st[p] = v;
		return;
	}
	int m = (l + r) / 2;
	update(x,v,l,m,2 * p + 1,st);
	update(x,v,m + 1,r,2 * p + 2,st);
	st[p] = max(st[2 * p + 1],st[2 * p + 2]);
	return;
}

void update(int x,long long v,long long* st) {
	update(x,v,0,MAXN,0,st);
}

long long getMax(int a,int b,int l,int r,int p,long long* st) {
	if(l > b || r < a) return -1e16;
	if(l >= a && r <= b) return st[p];
	int m = (l + r) / 2;
	return max(getMax(a,b,l,m,2 * p + 1,st),getMax(a,b,m + 1,r,2 * p + 2,st));
}

long long getMax(int a,int b,long long* st) {
	return getMax(a,b,0,MAXN,0,st);
}

int main() {
	cin >> N;
	vector<int> v;
	for(int i = 0;i < N;++i) {
		update(i,-1e16,st1);
		cin >> hei[i];
		nxt[i] = pre[i] = -1;
		v.push_back(i);
	}
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
	}
	sort(v.begin(),v.end(),[&](int a,int b) {return hei[a] < hei[b];});
	set<int> s;
	for(int i = 0;i < N;++i) {
		auto itr = s.upper_bound(v[i]);
		if(itr == s.begin()) {
			nxt[v[i]] = *s.begin();
		}else if(itr == s.end()) {
			if(s.size() != 0) {
				pre[v[i]] = *prev(s.end());
			}
		}else{
			nxt[v[i]] = *itr;
			pre[v[i]] = *prev(itr);
		}
		s.insert(v[i]);
	}

	dp[0] = arr[0];
	set<int> le;
	le.insert(-hei[0]);
	update(hei[0],dp[0],st1);
	update(0,dp[0],st2);
	for(int i = 1;i < N;++i) {
		long long cur = getMax(pre[i],i - 1,st2) + arr[i];
		if(pre[i] == -1) {
			cur = max(cur,arr[i]);
		}
		update(hei[i],cur,st1);
		le.insert(-hei[i]);
		for(auto itr = le.begin();itr != le.end();) {
			if(-*itr > hei[i]) {
				update(-*itr,-1e16,st1);
				le.erase(itr++);
			}else{
				break;
			}
		}
		dp[i] = getMax(0,hei[i],st1);
		// cout << "before " << dp[i] << endl;
		// dp[i] = max(dp[i],dp[i - 1] + arr[i]);
		update(i,dp[i],st2);
		// cout << i << " " << dp[i] << endl;
	}
	cout << dp[N - 1] << endl;
	return 0;
}