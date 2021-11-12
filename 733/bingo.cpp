using namespace std;

#include <iostream>

#define MAXN 24
#define MOD 31607
#define INV 3973

int N;
unsigned short dp[MAXN][1 << 23],dp2[MAXN][1 << 21],arr[MAXN][MAXN],com[MAXN][MAXN],lo[(1 << 23)],pre[MAXN][2][2];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		lo[1 << i] = i;
		for(int j = 0;j < N;++j) {
			cin >> arr[i][j];
			arr[i][j] = arr[i][j] * INV % MOD;
			com[i][j] = (MOD + 1 - arr[i][j]) % MOD;
		}
	}
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < 2;++j) {
			for(int k = 0;k < 2;++k) {
				pre[i][j][k] = 1;
				for(int l = 0;l < N;++l) {
					if(!((l == i && j) || (l == N - 1 - i && k))) {
						pre[i][j][k] = pre[i][j][k] * arr[l][i] % MOD;
					}
				}
			}
		}
	}
	for(int i = 0;i < N;++i) {
		dp2[i][0] = 1;
		for(int j = 1;j < (1 << N);++j) {
			dp2[i][j] = dp2[i][j ^ (j & -j)] * arr[i][lo[j & -j]] % MOD;
		}
	}
	for(int i = N + 2;i >= 0;--i) {
		for(int j = 0;j < 1 << i;++j) {
			if(i == N + 2) {
				dp[i][j] = 1;
				int mask = 0;
				for(int k = 2;k < N + 2;++k) {
					if(j & (1 << k)) mask |= 1 << (k - 2);
				}
				for(int k = 0;k < N;++k) {
					int cur = mask;
					if(j & 1) cur |= 1 << k;
					if(j & 2) cur |= 1 << (N - k - 1);
					dp[i][j] = dp[i][j] * (MOD + 1 - dp2[k][((1 << N) - 1) ^ cur]) % MOD;
				}
			}else if(i > 1) {
				dp[i][j] = (MOD + dp[i + 1][j] - dp[i + 1][j | (1 << i)] * pre[i - 2][j & 1][!!(j & 2)] % MOD) % MOD;
			}else if(i == 1) {
				int cur = 1;
				for(int k = 0;k < N;++k) {
					if(!(N & 1 && k == (N >> 1) && j)) {
						cur = cur * arr[k][N - 1 - k] % MOD;
					}
				}
				dp[i][j] = (MOD + dp[i + 1][j] - dp[i + 1][j | (1 << i)] * cur % MOD) % MOD;
			}else{
				int cur = 1;
				for(int k = 0;k < N;++k) {
					cur = cur * arr[k][k] % MOD;
				}
				dp[i][j] = (MOD + dp[i + 1][j] - dp[i + 1][j | (1 << i)] * cur % MOD) % MOD;
			}
		}
	}
	cout << (1 + MOD - dp[0][0]) % MOD << endl;
	return 0;
}