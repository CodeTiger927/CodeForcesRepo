using namespace std;

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstring>

#define MAXN 100005
#define MAXA 200005
#define MAXM 90
#define SQRTM 450
#define MOD 1000000007

int N,Q,spf[MAXA],rev[MAXA],st[262144][MAXM],last[MAXA],tmp[MAXM],arr[MAXN];
vector<pair<int,long long>> st2[262144];
vector<int> ps;

long long pow(long long x,long long b) {
	if(b == 0) return 1ll;
	if(b == 1) return x;
	long long res = pow(x,b / 2);
	if(b & 1) {
		return x * (res * res % MOD) % MOD;
	}
	return res * res % MOD;
}

void sieve() {
	spf[1] = 1;
	for(int i = 2;i < MAXA;++i) {
		if(!spf[i]) {
			spf[i] = i;
			if(i > SQRTM) continue;
			for(int j = i * i;j < MAXA;j += i) {
				if(!spf[j]) spf[j] = i;
			}
			rev[i] = ps.size();
			if(i < SQRTM) ps.push_back(i);
		}
	}
	return;
}

void update(int x,int v,int l,int r,int p) {
	if(x < l || x > r) return;
	if(l == r) {
		while(spf[v] != 1) {
			int curP = spf[v];
			int cnt = 0;
			while(spf[v] == curP) {
				cnt++;
				v /= curP;
			}
			if(curP < SQRTM) {
				st[p][rev[curP]] = cnt;
			}
		}
		return;
	}
	int m = (l + r) >> 1;
	update(x,v,l,m,2 * p + 1);
	update(x,v,m + 1,r,2 * p + 2);
	for(int i = 0;i < MAXM;++i) {
		st[p][i] = max(st[2 * p + 1][i],st[2 * p + 2][i]);
	}
	return;
}

void query(int a,int b,int l,int r,int p,int* res) {
	if(a > r || b < l) return;
	if(l >= a && r <= b) {
		for(int i = 0;i < MAXM;++i) {
			res[i] = max(res[i],st[p][i]);
		}
		return;
	}
	int m = (l + r) >> 1;
	query(a,b,l,m,2 * p + 1,res);
	query(a,b,m + 1,r,2 * p + 2,res);
	return;
}

void update2(int x,pair<int,long long> v,int l,int r,int p) {
	if(x < l || x > r) return;
	st2[p].push_back(v);
	if(l == r) return;
	int m = (l + r) >> 1;
	update2(x,v,l,m,2 * p + 1);
	update2(x,v,m + 1,r,2 * p + 2);
}

void sortTree() {
	for(int i = 0;i < 262144;++i) {
		sort(st2[i].begin(),st2[i].end());
		for(int j = 1;j < st2[i].size();++j) {
			st2[i][j].second = (st2[i][j].second * st2[i][j - 1].second) % MOD;
		}
	}
	return;
}

long long query2(int a,int b,int l,int r,int p) {
	if(a > r || b < l) return 1ll;
	if(l >= a && r <= b) {
		if(st2[p].size() == 0) return 1ll;
		int l = 0;
		int r = st2[p].size() - 1;
		while(l < r) {
			int m = (l + r + 1) >> 1;
			if(st2[p][m].first < a) {
				l = m;
			}else{
				r = m - 1;
			}
		}
		if(l < st2[p].size() && st2[p][l].first < a) return st2[p][l].second;
		return 1ll;
	}
	int m = (l + r) >> 1;
	long long res = query2(a,b,l,m,2 * p + 1) * query2(a,b,m + 1,r,2 * p + 2) % MOD;
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	sieve();
	cin >> N;
	memset(last,-1,sizeof(last));
	long long lastAns = 0;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		update(i,arr[i],0,MAXN,0);
		while(arr[i] != 1 && spf[arr[i]] < SQRTM) {
			arr[i] /= spf[arr[i]];
		}
		if(arr[i] != 1) {
			update2(i,{last[arr[i]],arr[i]},0,MAXN,0);
			last[arr[i]] = i;
		}
	}
	sortTree();
	cin >> Q;
	for(int i = 0;i < Q;++i) {
		memset(tmp,0,sizeof(tmp));
		int l,r;
		cin >> l >> r;
		l = (lastAns + l) % N;
		r = (lastAns + r) % N;
		if(l > r) swap(l,r);
		query(l,r,0,MAXN,0,tmp);
		long long ans = 1;
		for(int j = 0;j < MAXM;++j) {
			ans = ans * pow(ps[j],tmp[j]) % MOD;
		}
		ans = ans * query2(l,r,0,MAXN,0) % MOD;
		cout << ans << "\n";
		lastAns = ans;
	}
	return 0;
}