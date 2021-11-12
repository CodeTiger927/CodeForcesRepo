using namespace std;

#include <iostream>
#include <array>
#include <map>
#include <set>

#define MAXK 65
#define MAXN 2005
#define MOD 1000000007

int K,N;
array<long long,6> dp[MAXK];
set<long long> s[MAXK];
map<long long,int> m;
map<long long,array<long long,6>> arr;

array<long long,6> comb(array<long long,6>& a,array<long long,6>& b) {
	long long s1 = a[0] + a[1] + a[2] + a[3] + a[4] + a[5];
	long long s2 = b[0] + b[1] + b[2] + b[3] + b[4] + b[5];
	array<long long,6> res;
	for(int i = 0;i < 6;++i) {
		res[i] = ((s1 - a[i] - a[5 - i]) % MOD) * ((s2 - b[i] - b[5 - i]) % MOD) % MOD;
	}
	return res;
}

int lg(long long x) {
	for(int i = 0;i <= K;++i) {
		if((1ll << (i + 1)) > x) return i;
	}
	return -1;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin >> K >> N;
	for(int i = 0;i < N;++i) {
		long long v,t;
		string str;
		cin >> v >> str;
		if(str == "white") {
			t = 0;
		}else if(str == "yellow") {
			t = 5;
		}else if(str == "green") {
			t = 1;
		}else if(str == "blue") {
			t = 4;
		}else if(str == "red") {
			t = 2;
		}else{
			t = 3;
		}
		m[v] = t;
		arr[v] = {0,0,0,0,0,0};
		arr[v][t] = 1;
		s[lg(v)].insert(v);
	}
	dp[K - 1] = {1,1,1,1,1,1};
	for(int i = K - 2;i >= 0;--i) {
		dp[i] = comb(dp[i + 1],dp[i + 1]);
	}
	s[0].insert(1);
	for(int i = K - 1;i >= 0;--i) {
		for(long long j : s[i]) {
			array<long long,6> cur = {1,1,1,1,1,1};
			if(i != K - 1) {
				array<long long,6> l = (s[i + 1].count(2ll * j)) ? arr[2ll * j] : dp[i + 1];
				array<long long,6> r = (s[i + 1].count(2ll * j + 1)) ? arr[2ll * j + 1] : dp[i + 1];
				cur = comb(l,r);
			}
			if(m.count(j)) {
				int c = m[j];
				for(int k = 0;k < 6;++k) {
					if(k != c) cur[k] = 0;
				}
			}
			arr[j] = cur;
			if(i) s[i - 1].insert(j >> 1);
		}
	}
	cout << (arr[1][0] + arr[1][1] + arr[1][2] + arr[1][3] + arr[1][4] + arr[1][5]) % MOD << endl;
	return 0;
}