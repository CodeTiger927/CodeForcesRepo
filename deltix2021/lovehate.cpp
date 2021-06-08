using namespace std;

#include <iostream>
#include <cstring>
#include <random>
#include <cstring>
#include <time.h>

#define MAXN 200005

int N,M,P,dp[32768],ans;
string res;
bool like[MAXN][60];

int main() {
	ans = -1;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> N >> M >> P;
	for(int i = 0;i < N;++i) {
		string str;
		cin >> str;
		for(int j = 0;j < M;++j) {
			like[i][j] = str[j] - '0';
		}
	}
	mt19937 rnd(time(NULL));
	for(int ITER = 0;ITER < 50;++ITER) {
		int i = uniform_int_distribution<int>(0,N - 1)(rnd);
		vector<int> v;
		for(int j = 0;j < M;++j) {
			if(like[i][j]) v.push_back(j);
		}
		int n = v.size();
		memset(dp,0,sizeof(dp));
		for(int j = 0;j < N;++j) {
			int mask = 0;
			for(int k = 0;k < n;++k) {
				if(!like[j][v[k]]) mask |= (1 << k);
			}
			dp[mask]++;
		}
		for(int j = 0;j < n;++j) {
			for(int k = 0;k < (1 << n);++k) {
				if(k & (1 << j)) dp[k] += dp[k ^ (1 << j)];
			}
		}
		for(int j = 0;j < (1 << n);++j) {
			if(dp[j] < (N + 1) / 2) continue;
			int cur = v.size() - __builtin_popcount(j);
			if(cur > ans) {
				ans = cur;
				res = string(M,'0');
				for(int k = 0;k < n;++k) {
					if(!(j & (1 << k))) res[v[k]] = '1';
				}
			}
		}
	}
	cout << res << endl;
	return 0;
}