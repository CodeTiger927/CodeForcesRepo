using namespace std;

#include <iostream>
#include <set>
#include <assert.h>
#include <cstring>

#define MAXN 2005

int N,M;
int dx[8] = {1,0,-1,0,1,1,-1,-1};
int dy[8] = {0,1,0,-1,1,-1,1,-1};
int f[MAXN];
long long dp[MAXN][MAXN],ans;
bool arr[MAXN][MAXN];
set<int> s[MAXN];

struct Line {
	mutable long long k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(long long x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const long long inf = LLONG_MAX;
	long long div(long long a, long long b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(long long k, long long m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	long long query(long long x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

long long dist(long long x1,long long y1,long long x2,long long y2) {
	if(x1 == -1 || x2 == -1) return 1e15;
	return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M;
	for(int i = 0;i <= N;++i) {
		string str;
		cin >> str;
		for(int j = 0;j <= M;++j) {
			arr[i][j] = str[j] - '0';
		}
	}
	memset(f,-1,sizeof(f));
	for(int i = 0;i <= N;++i) {
		// (a^2 + b^2) - 2(ax + by) + (x^2 + y^2)
		// slope = -2by
		// constant = -2ax + (a^2 + b^2)
		for(int j = 0;j <= M;++j) {
			dp[i][j] = 1e15;
			if(arr[i][j]) f[j] = i;
		}
		LineContainer lc;
		for(int j = 0;j <= M;++j) {
			if(~f[j]) {
				long long slope = (-2ll) * j;
				long long constant = (-2ll) * f[j] * i + (j * j + f[j] * f[j]);
				lc.add(-slope,-constant);
			}
		}
		for(int j = 0;j <= M;++j) {
			if(lc.size()) dp[i][j] = -lc.query(j) + (i * i + j * j);
		}
	}
	memset(f,-1,sizeof(f));
	for(int i = N;i >= 0;--i) {
		// (a^2 + b^2) - 2(ax + by) + (x^2 + y^2)
		// slope = -2by
		// constant = -2ax + (a^2 + b^2)
		for(int j = 0;j <= M;++j) {
			if(arr[i][j]) f[j] = i;
		}
		LineContainer lc;
		for(int j = 0;j <= M;++j) {
			if(~f[j]) {
				long long slope = (-2ll) * j;
				long long constant = (-2ll) * f[j] * i + (j * j + f[j] * f[j]);
				lc.add(-slope,-constant);
			}
		}
		for(int j = 0;j <= M;++j) {
			if(lc.size()) dp[i][j] = min(dp[i][j],-lc.query(j) + (i * i + j * j));
			ans += dp[i][j];
		}
	}
	cout << ans << endl;
	return 0;
}