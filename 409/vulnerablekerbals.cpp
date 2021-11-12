using namespace std;

#include <iostream>
#include <vector>

#define MAXN 200005

int N,M;
bool blocked[MAXN];
long long dp[MAXN],cnt[MAXN],best[MAXN];
vector<int> v,v2,v3[MAXN],ans;

long long inv(long long a,long long b = M) {
	return 1 < a ? b - inv(b % a,a) * b / a : 1;
}

int gcd(int a, int b) {
    while(b) b ^= a ^= b ^= a %= b;
    return a;
}

long long d(long long a,long long b) {
	int g = gcd(gcd(a,b),M);
	a /= g;
	b /= g;
	return (a * inv(b,M / g) % (M / g));
}

int main() {
	cin >> N >> M;
	for(int i = 0;i < N;++i) {
		int cur;
		cin >> cur;
		blocked[cur] = true;
	}
	long long cur = M;
	for(int i = 2;i <= M;++i) {
		int s = 1;
		if(cur % i == 0) {
			while(cur % i == 0) {
				s *= i;
				v.push_back(s);
				v2.push_back(i);
				cur /= i;
			}
		}
	}
	for(int i = 0;i < M;++i) {
		if(blocked[i]) continue;
		int b = 0;
		for(int j = 0;j < v.size();++j) {
			if(i % v[j] == 0) {
				b |= 1 << j;
			}
		}
		cnt[b]++;
		v3[b].push_back(i);
	}
	for(int i = 0;i < (1 << v.size());++i) {
		bool flag = false;
		for(int j = 1;j < v2.size();++j) {
			if(i & (1 << j) && !(i & (1 << (j - 1))) && v2[j] == v2[j - 1]) flag = true;
		}
		if(flag) continue;
		for(int j = 0;j < v2.size();++j) {
			if(i & (1 << j)) {
				if(dp[i - (1 << j)] > dp[i]) {
					best[i] = j;
					dp[i] = dp[i - (1 << j)];
				}
			}
		}
		dp[i] += cnt[i];
	}
	cur = (1 << v2.size()) - 1;
	cout << dp[cur] << endl;
	while(cur) {
		for(int j : v3[cur]) {
			ans.push_back(j);
		}
		cur -= 1 << best[cur];
	}
	for(int j : v3[cur]) {
		ans.push_back(j);
	}
	ans.push_back(1);
	for(int i = ans.size() - 2;i >= 0;--i) {
		cout << d(ans[i],ans[i + 1]) << " ";
	}
	cout << endl;
	return 0;
}