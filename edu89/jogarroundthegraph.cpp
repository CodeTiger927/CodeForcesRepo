using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>

#define MAXN 2005
#define MOD 1000000007

int N,M,Q,u[MAXN],v[MAXN];
long long mw[MAXN],d[MAXN],nd[MAXN],dp[MAXN],w[MAXN];

struct frac {
	long long x,y;
	frac(long long a,long long b){
		if(b < 0) a = -a,b = -b;
		x = a,y = b;
	}
};

bool operator <=(const frac &a, const frac &b){
	return a.x * b.y <= a.y * b.x;
}

long long add(long long a,long long b) {
	return (a + b) % MOD;
}

long long mul(long long a,long long b){
	return a * 1ll * b % MOD;
}

struct line{
	long long m,c;
	frac intersectX(const line &l) {return frac(c - l.c, l.m - m);}
};

long long calc(long long a1,long long d,long long n){
	return mul(mul(n,500000004), add(mul(2,a1), mul(add(n, -1), d)));
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> Q;
	for(int i = 0;i < M;++i) {
		cin >> u[i] >> v[i] >> w[i];
		u[i]--;v[i]--;
		mw[u[i]] = max(mw[u[i]],w[i]);
		mw[v[i]] = max(mw[v[i]],w[i]);
	}
	long long ans = 0;
	for(int i = 1;i < N;++i) {
		d[i] = -1e18;
	}
	for(int i = 0;i < M;++i) {
		long long mx = 0;
		for(int j = 0;j < N;++j) {
			mx = max(mx,d[j]);
		}
		if(i) {
			ans += mx;
			if(ans >= MOD) ans -= MOD;
		}
		for(int j = 0;j < N;++j) {
			nd[j] = d[j];
		}
		for(int j = 0;j < M;++j) {
			nd[v[j]] = max(nd[v[j]],d[u[j]] + w[j]);
			nd[u[j]] = max(nd[u[j]],d[v[j]] + w[j]);
		}
		for(int j = 0;j < N;++j) {
			d[j] = nd[j];
		}
	}
	vector<line> lines;
	for(int i = 0;i < N;++i) {
		lines.push_back({mw[i],d[i]});
	}
	
	sort(lines.begin(),lines.end(),[&](const line &a, const line &b) {
		if(a.m != b.m) return a.m < b.m;
		return a.c > b.c;
	});
	
	lines.resize(unique(lines.begin(),lines.end(),[&](const line &a, const line &b) {return a.m == b.m;}) - lines.begin());
	
	vector<line> ch;
	for(auto cur : lines) {
		while(ch.size() >= 2 && cur.intersectX(ch.back()) <= ch.back().intersectX(ch[(int)ch.size() - 2])) {
			ch.pop_back();
		}
		ch.push_back(cur);
	}

	long long prv = 0;
	Q -= M;
	// cout << ch[0].m << " " << ch[0].c << " " << ch[1].m << " " << ch[1].c << endl;
	for(int i = 0;i < ch.size() - 1;++i) {
		frac f = ch[i].intersectX(ch[i + 1]);
		if(f.x < 0) continue;
		long long lst = min((long long)Q,f.x / f.y);
		if(lst < prv) continue;
		ans = add(ans, calc((ch[i].c + ch[i].m * prv) % MOD, ch[i].m % MOD, lst - prv + 1));
		prv = lst + 1;
	}
	ans = add(ans, calc((ch.back().c + ch.back().m * prv) % MOD, ch.back().m % MOD, Q - prv + 1));
	cout << ans << endl;
	return 0;
}