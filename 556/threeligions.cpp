using namespace std;

#include <iostream>
#include <cstring>

#define MAXN 100005
#define MAXM 255

int N,M,nxt[MAXN][26],tmp[MAXN],sz[3],arr[3][MAXM],dp[MAXM][MAXM][MAXM];
string str;

int main() {
	cin >> N >> M >> str;
	for(int i = 0;i < 26;++i) {
		tmp[i] = N + 1;
		nxt[N][i] = nxt[N + 1][i] = N + 1;
	}
	for(int i = N - 1;i >= 0;--i) {
		tmp[str[i] - 'a'] = i + 1;
		for(int j = 0;j < 26;++j) {
			nxt[i][j] = tmp[j];
		}
	}
	for(int i = 0;i < MAXM;++i) {
		for(int j = 0;j < MAXM;++j) {
			for(int k = 0;k < MAXM;++k) {
				dp[i][j][k] = N + 1;
			}
		}
	}
	dp[0][0][0] = 0;
	for(int i = 0;i < M;++i) {
		char c,b;
		int a;
		cin >> c >> a;
		a--;
		if(c == '-') {
			sz[a]--;
		}else{
			cin >> b;
			arr[a][sz[a]++] = b - 'a';
			if(a == 0) {
				for(int j = 0;j <= sz[1];++j) {
					for(int k = 0;k <= sz[2];++k) {
						dp[sz[a]][j][k] = N + 1;
						dp[sz[a]][j][k] = min(dp[sz[a]][j][k],nxt[dp[sz[a] - 1][j][k]][arr[a][sz[a] - 1]]);
						if(j > 0) dp[sz[a]][j][k] = min(dp[sz[a]][j][k],nxt[dp[sz[a]][j - 1][k]][arr[1][j - 1]]);
						if(k > 0) dp[sz[a]][j][k] = min(dp[sz[a]][j][k],nxt[dp[sz[a]][j][k - 1]][arr[2][k - 1]]);
					}
				}
			}else if(a == 1) {
				for(int j = 0;j <= sz[0];++j) {
					for(int k = 0;k <= sz[2];++k) {
						dp[j][sz[a]][k] = N + 1;
						dp[j][sz[a]][k] = min(dp[j][sz[a]][k],nxt[dp[j][sz[a] - 1][k]][arr[a][sz[a] - 1]]);
						if(j > 0) dp[j][sz[a]][k] = min(dp[j][sz[a]][k],nxt[dp[j - 1][sz[a]][k]][arr[0][j - 1]]);
						if(k > 0) dp[j][sz[a]][k] = min(dp[j][sz[a]][k],nxt[dp[j][sz[a]][k - 1]][arr[2][k - 1]]);
					}
				}
			}else{
				for(int j = 0;j <= sz[0];++j) {
					for(int k = 0;k <= sz[1];++k) {
						dp[j][k][sz[a]] = N + 1;
						dp[j][k][sz[a]] = min(dp[j][k][sz[a]],nxt[dp[j][k][sz[a] - 1]][arr[a][sz[a] - 1]]);
						if(j > 0) dp[j][k][sz[a]] = min(dp[j][k][sz[a]],nxt[dp[j - 1][k][sz[a]]][arr[0][j - 1]]);
						if(k > 0) dp[j][k][sz[a]] = min(dp[j][k][sz[a]],nxt[dp[j][k - 1][sz[a]]][arr[1][k - 1]]);
					}
				}
			}
		}
		cout << (dp[sz[0]][sz[1]][sz[2]] <= N ? "YES" : "NO") << endl;
	}

}