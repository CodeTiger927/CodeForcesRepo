using namespace std;

#include <iostream>
#include <set>
#include <vector>
#include <cstring>

#define MAXN 300005
#define MOD 998244353

int N,M,rev[MAXN],upd[MAXN],L[MAXN],R[MAXN];
vector<long long> dp[21][22];
long long fact[MAXN],invf[MAXN],knap[21][42];
vector<int> edges[MAXN];

long long inv(long long a,long long b = MOD) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

long long nCr(long long a,long long b) {
	if(b > a || b < 0 || a < 0) return 0;
	return (fact[a] * invf[b] % MOD) * invf[a - b] % MOD;
}

vector<int> comp[MAXN];
int root[MAXN];

int findR(int x) {
	return x == root[x] ? x : root[x] = findR(root[x]);
}

void merge(int a,int b) {
	a = findR(a);
	b = findR(b);
	if(a == b) return;
	if(comp[a].size() < comp[b].size()) swap(a,b);
	root[b] = a;
	for(int x : comp[b]) comp[a].push_back(x);
	return;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	fact[0] = invf[0] = 1;
	for(int i = 1;i < MAXN;++i) {
		fact[i] = i * fact[i - 1] % MOD;
		invf[i] = inv(fact[i]);
	}

	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		root[i] = i;
		comp[i].push_back(i);
		cin >> L[i] >> R[i];
		upd[L[i]]++;
		upd[R[i] + 1]--;
	}
	for(int i = 0;i < M;++i) {
		int a,b;
		cin >> a >> b;
		a--;b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
		merge(a,b);
	}

	vector<int> roots;
	int t = 0;
	for(int r = 0;r < N;++r) { 
		if(findR(r) != r || comp[r].size() == 1) continue;
		roots.push_back(r);
		int n = comp[r].size();
		for(int i = 0;i <= n;++i) {
			dp[t][i].resize(1 << n);
		}
		for(int i = 0;i < n;++i) {
			rev[comp[r][i]] = i;
		}
		for(int i = 0;i < (1 << n);++i) {
			bool work = true;
			int cnt = 0;
			for(int j = 0;j < n;++j) {
				if(!work) break;
				if(i & (1 << j)) {
					cnt++;
					for(int u : edges[comp[r][j]]) {
						if((i & (1 << rev[u]))) {
							work = false;
							break;
						}
					}
				}
			}
			if(work) dp[t][cnt][i]++;

		}
		for(int i = 0;i <= n;++i) {
			// SOS dp
			for(int j = 0;j < n;++j) {
				for(int k = 0;k < (1 << n);++k) {
					if(k & (1 << j)) {
						dp[t][i][k] += dp[t][i][k ^ (1 << j)];
						if(dp[t][i][k] >= MOD) dp[t][i][k] -= MOD;
					}
				}
			}
		}
		t++;
	}
	
	int cnt = 0;
	set<int> on;
	long long ans = 0;
	int sum = 0;
	for(int i = 1;i <= N;++i) {
		sum += upd[i];
		int spec = 0;
		memset(knap,0,sizeof(knap));
		knap[0][0] = 1;
		int m = 0;
		for(int j = 0;j < t;++j) {
			int mask = 0;
			for(int k = 0;k < comp[roots[j]].size();++k) {
				int c = comp[roots[j]][k];
				if(i >= L[c] && i <= R[c]) {
					spec++;
					mask |= (1 << k);
				}
			}
			for(int a = 0;a <= m;++a) {
				for(int b = 0;b <= comp[roots[j]].size();++b) {
					if(a + b >= 41) continue;
					knap[j + 1][a + b] += knap[j][a] * dp[j][b][mask] % MOD;
					if(knap[j + 1][a + b] >= MOD) knap[j + 1][a + b] -= MOD;
				}
			}
			m = min(40,(int)comp[roots[j]].size() + m);
		}
		for(int j = 0;j < 41;++j) {
			ans += knap[t][j] * nCr(sum - spec,i - j) % MOD;
			if(ans >= MOD) ans -= MOD;
		}
	}
	cout << ans << endl;
	return 0;
}