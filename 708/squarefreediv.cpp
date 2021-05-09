using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#define MAXN 200005

int spf[10000005];

void sieve() {
	for(int i = 1;i <= 1e7;i++) {
		spf[i] = i;
	}
	for(int i = 4;i <= 1e7;i += 2) {
		spf[i] = 2;
	}
	for(int i = 3;i * i <= 1e7;i++) {
		if(spf[i] == i) {
			for(int j = i * i;j <= 1e7;j += i) {
				if(spf[j] == j) spf[j] = i;
			}
		}
	}
	return;
}


int N,K,arr[MAXN],le[MAXN][25],dp[MAXN][25],um[10000005];


void solve() {
	scanf("%d %d",&N,&K);
	for(int i = 0;i < N;++i) {
		scanf("%d",&arr[i]);
		int bound = 0;
		int big = 1;
		int cur = arr[i];
		while(spf[cur] != 1) {
			int curD = spf[cur];
			int cnt = 0;
			while(spf[cur] == curD) {
				cnt++;
				cur /= curD;
			}
			if(cnt & 1) {
				big *= curD;
			}
		}
		arr[i] = big;
	}
	for(int i = 0;i <= K;++i) {
		int ptr = 0;
		int sum = 0;
		for(int j = 0;j < N;++j) {
			um[arr[j]] = 0;
		}
		for(int j = 0;j < N;++j) {
			um[arr[j]]++;
			if(um[arr[j]] != 1) sum++;
			while(sum > i) {
				um[arr[ptr]]--;
				if(um[arr[ptr++]] != 0) sum--;
			}
			le[j][i] = ptr;
		}
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j <= K;++j) {
			dp[i][j] = i;
			for(int k = 0;k <= j;++k) {
				dp[i][j] = min(dp[i][j],dp[le[i - 1][j - k]][k] + 1);
			}
		}
	}
	printf("%d\n",dp[N][K]);
	return;
}

int main() {
	sieve();
	int T;
	scanf("%d",&T);
	while(T--) solve();
	return 0;
}