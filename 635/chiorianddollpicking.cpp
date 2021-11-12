using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>

#define MAXN 200005
#define MAXK 40
#define MOD 998244353

int N,M;
long long arr[MAXN],bases[MAXK],popc[1ll << 18],ans[MAXK],dp[2][MAXK][1ll << 18],aux[MAXN];
vector<int> key;

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		cin >> arr[i];
		for(int j = M - 1;j >= 0;--j) {
			if(arr[i] & (1ll << j)) {
				if(bases[j]) {
					arr[i] ^= bases[j];
				}else{
					bases[j] = arr[i];
					key.push_back(j);
					break;
				}
			}
		}
	}
	sort(key.begin(),key.end());
	for(int i = 1;i < (1ll << 18);++i) {
		popc[i] = popc[i ^ (i & -i)] + 1;
	}
	for(int i = 0;i < key.size();++i) {
		for(int j = 0;j < i;++j) {
			if(bases[key[i]] & (1ll << key[j])) bases[key[i]] ^= bases[key[j]];
		}
	}
	long long pow = 1;
	int K = key.size();
	for(int i = 0;i < N - K;++i) {
		pow = (pow << 1) % MOD;
	}
	for(int i = 0;i < K;++i) {
		for(int j = 0,t = 0;j < M;++j) {
			if(bases[j]) continue;
			aux[key[i]] |= !!(bases[key[i]] & (1ll << j)) * (1ll << (t++));
		}
	}
	if(K <= 18) {
		for(int i = 0;i < (1ll << K);++i) {
			long long cur = 0;
			for(int j = 0;j < K;++j) {
				if(i & (1ll << j)) cur ^= bases[key[j]];
			}
			ans[__builtin_popcountll(cur)]++;
		}
	}else{
		dp[0][0][0] = 1;
		for(int i = 1;i <= K;++i) {
			for(int j = 0;j <= K;++j) {
				for(int k = 0;k < 1ll << (M - K);++k) {
					long long x = aux[key[i - 1]];
					dp[i & 1][j][k] = (dp[(i - 1) & 1][j][k] + (j > 0 ? dp[(i - 1) & 1][j - 1][k ^ x] : 0));
					if(dp[i & 1][j][k] >= MOD) dp[i & 1][j][k] -= MOD;
					// cout << i << " " << j << " " << k << " " << dp[i & 1][j][k] << endl;
					if(i == K) ans[j + popc[k]] = (ans[j + popc[k]] + dp[i & 1][j][k]) % MOD;
				}
			}
		}
	}
	for(int i = 0;i <= M;++i) {
		cout << (ans[i] * pow) % MOD << " \n"[i == M];
	}
	return 0;
}