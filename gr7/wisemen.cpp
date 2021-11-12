using namespace std;

#include <iostream>
#include <vector>
#include <functional>
#include <map>
#include <algorithm>

#define MAXN 18

long long N,g[MAXN],dp[1 << MAXN][MAXN],dp2[MAXN][1 << MAXN],dp3[1 << MAXN],dp4[MAXN][1 << MAXN],ans[1 << MAXN];

int main() {
	cin >> N;
	for(int i = 0;i < N;++i) {
		for(int j = 0;j < N;++j) {
			char c;
			cin >> c;
			g[i] |= (c == '1') << j;
		}
	}
	for(int i = 0;i < N;++i) {
		dp[1 << i][i] = 1;
	}
	for(int i = 0;i < (1 << N);++i) {
		for(int j = 0;j < N;++j) {
			dp2[__builtin_popcount(i)][i] += dp[i][j];
			for(int k = 0;k < N;++k) {
				if(!(g[j] & (1 << k)) || i & (1 << k)) continue;
				dp[i | (1 << k)][k] += dp[i][j];
			}
		}
	}
	for(int i = 1;i <= N;++i) {
		for(int j = 0;j < N;++j) {
			for(int k = 0;k < (1 << N);++k) {
				if(!(k & (1 << j))) continue;
				dp2[i][k] += dp2[i][k ^ (1 << j)];
			}
		}
	}
	map<vector<int>,vector<int>> m;
	for(int i = 0;i < (1 << (N - 1));++i) {
		vector<int> cur;
		for(int j = 0;j < N;++j) {
			int l = 1;
			while(i & (1 << j)) {
				l++;
				j++;
			}
			cur.push_back(l);
		}
		sort(cur.begin(),cur.end());
		m[cur].push_back(i);
	}
	vector<int> v;
	for(int i = 0;i < (1 << N);++i) {
		dp3[i] = 1;
	}
	function<void(int,int)> f = [&](int sum,int last) {
		if(sum == N) {
			long long res = 0;
			for(int i = 0;i < (1 << N);++i) {
				res += (__builtin_popcount(i) & 1 ? -1 : 1) * dp3[i];
			}
			for(auto c : m[v]) {
				ans[c] += res;
			}
			return;
		}
		if(sum + last > N) return;
		for(int i = 0;i < (1 << N);++i) {
			dp4[sum][i] = dp3[i];
		}
		for(int i = last;i <= N - sum;++i) {
			if(sum + i != N && sum + i + i > N) continue;
			v.push_back(i);
			for(int j = 0;j < (1 << N);++j) {
				dp3[j] *= dp2[i][j];
			}
			f(sum + i,i);
			for(int j = 0;j < (1 << N);++j) {
				dp3[j] = dp4[sum][j];
			}
			v.pop_back();
		}
	};
	f(0,1);
	// for(int i = 0;i < (N - 1);++i) {
	// 	for(int j = 0;j < (1 << (N - 1));++j) {
	// 		if(j & (1 << i)) continue;
	// 		ans[j] -= ans[j ^ (1 << i)];
	// 	}
	// }
	// Idk where I went wrong but apparently answer is sometimes negative :clown: so there's the abs
	for(int i = 0;i < (1 << (N - 1));++i) {
		cout << (ans[i]) << " \n"[i == (1 << (N - 1)) - 1];
	}
	return 0;
}