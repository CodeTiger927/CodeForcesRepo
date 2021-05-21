using namespace std;

#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <algorithm>

#define MAXN 200005

mt19937 mt_rand(chrono::high_resolution_clock::now().time_since_epoch().count());

long long MOD[3];

struct hsh {
	long long val[3];
	hsh() {
		val[0] = val[1] = val[2] = 0;
	}
	hsh(long long x) {
		val[0] = x % MOD[0];
		val[1] = x % MOD[1];
		val[2] = x % MOD[2];
	}
	hsh operator+(hsh x) {
		hsh res;
		res.val[0] = (val[0] + x.val[0]) % MOD[0];
		res.val[1] = (val[1] + x.val[1]) % MOD[1];
		res.val[2] = (val[2] + x.val[2]) % MOD[2];
		return res;
	}
	bool operator==(const hsh& x) {
		return (val[0] == x.val[0] && val[1] == x.val[1] && val[2] == x.val[2]);
	}
};

int N,M,K;
hsh val[MAXN],v[10][10],s;
vector<pair<int,int>> edges[MAXN];

long long dfs(int a,hsh x) {
	long long res = 0;
	for(int i = 1;i <= a;++i) {
		hsh n = x + v[a][i];
		if(a == K) {
			res += (n == s);
		}else{
			res += dfs(a + 1,n);
		}
	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	MOD[0] = 1000000007;
	MOD[1] = 998244353;
	MOD[2] = uniform_int_distribution<int>(1e8,1e9)(mt_rand);
	cin >> N >> M >> K;
	for(int i = 0;i < N;++i) {
		val[i] = hsh(uniform_int_distribution<long long>(1,1e18)(mt_rand));
		s = s + val[i];
	}
	for(int i = 0;i < M;++i) {
		int a,b,w;
		cin >> a >> b >> w;
		a--;b--;
		edges[a].push_back({w,b});
	}
	for(int i = 0;i < N;++i) {
		int n = edges[i].size();
		sort(edges[i].begin(),edges[i].end());
		for(int j = 0;j < n;++j) {
			v[n][j + 1] = v[n][j + 1] + val[edges[i][j].second];
		}
	}
	hsh init(0);
	cout << dfs(1,init) << endl;
	return 0;
}