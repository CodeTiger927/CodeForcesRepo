using namespace std;

#include <iostream>
#include <set>

#define MAXN 405
#define MOD 998244353

int N,arr[26];
int dp[2][MAXN][MAXN][3][3],sum1[MAXN][MAXN],sum2[MAXN][MAXN],sum3[MAXN][MAXN];

int add(int x,int y) {
	if((x + y) >= MOD) return (x + y - MOD);
	return (x + y);
}

int sub(int x,int y) {
	if(x < y) return (x + MOD - y);
	return (x - y);
}

int main() {
	cin >> N;
	for(int i = 0;i < 26;++i) {
		cin >> arr[i];
	}
	for(int i = 0;i < 26;++i) {
		for(int j = 0;j < 26;++j) {
			for(int k = 0;k < 26;++k) {
				if(i == k) continue;
				multiset<int> ms = {i,j,k};
				dp[3 % 2][ms.count(0)][ms.count(1)][min(j,2)][min(k,2)]++;
			}
		}
	}
	for(int i = 4;i <= N;++i) {
		for(int j = 0;j < N;++j) {
			for(int k = 0;k < N;++k) {
				for(int x = 0;x < 3;++x) {
					for(int y = 0;y < 3;++y) {
						dp[0][j][k][x][y] = dp[1][j][k][x][y];
						dp[1][j][k][x][y] = 0;	
					}
				}
			}
		}
		for(int j = 0;j < N;++j) {
			for(int k = 0;k < N;++k) {
				for(int x = 0;x < 3;++x) {
					for(int y = 0;y < 3;++y) {
						int curN = dp[0][j][k][x][y];
						if(curN == 0) continue;
						for(int z = 0;z < 3;++z) {
							int& cur = dp[1][j + (z == 0)][k + (z == 1)][y][z];
							cur = add(cur,(1ll * curN * ((z == 2 ? 24 : 1) - (z == x))) % MOD);
						}	
					}
				}
			}
		}
	}

	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			for(int a = 0;a < 3;++a) {
				for(int b = 0;b < 3;++b) {
					sum1[i][j] = add(sum1[i][j],dp[1][i][j][a][b]);
				}
			}
		}
	}

	for(int i = 0;i < N;++i) {
		sum2[i][N - 1] = sum1[i][N - 1];
		for(int j = N - 2;j >= 0;--j) {
			sum2[i][j] = add(sum1[i][j],sum2[i][j + 1]);
		}
	}

	for(int i = 0;i < N;++i) {
		sum3[N - 1][i] = sum2[N - 1][i];
		for(int j = N - 2;j >= 0;--j) {
			sum3[j][i] = add(sum2[j][i],sum3[j + 1][i]);
		}
	}

	int ans = sum3[0][0];
	for(int i = 0;i < 26;++i) {
		for(int j = 0;j < N;++j) {
			for(int k = arr[i] + 1;k < N;++k) {
				ans = sub(ans,sum1[k][j]);
			}
		}
	}
	for(int i = 0;i < 26;++i) {
		for(int j = 0;j < i;++j) {
			ans = add(ans,sum3[arr[i] + 1][arr[j] + 1]);
		}
	}
	cout << ans << endl;
}