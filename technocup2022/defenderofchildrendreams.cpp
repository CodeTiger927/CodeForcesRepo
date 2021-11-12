using namespace std;

#include <iostream>

#define MAXN 1005

int N,K,g[MAXN][MAXN];

int solve(int l,int r,int d) {
	// cout << l << " " << r << " " << d << endl;
	if(l == r) return 0;
	int s = (r - l + K) / K;
	int res = 0;
	for(int i = l;i <= r;i += s) {
		res = max(res,solve(i,min(r,i + s - 1),d + 1));
		for(int j = i;j <= min(r,i + s - 1);++j) {
			for(int k = l;k < i;++k) {
				g[j][k] = g[k][j] = d + 1;
			}
		}
	}
	return res + 1;
}

int main() {
	cin >> N >> K;
	cout << solve(0,N - 1,0) << endl;
	for(int i = 0;i < N;++i) {
		for(int j = i + 1;j < N;++j) {
			cout << g[i][j] << " ";
		}
	}
	cout << endl;
	return 0;
}