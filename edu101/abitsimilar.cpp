using namespace std;

#include <iostream>
#include <cstring>
#include <set>

#define MOD 756594295766537
#define MOD2 338946368122867
#define base 97
#define base2 131

int N,K;
string str;
set<pair<long long,long long>> hashes;

void solve() {
	cin >> N >> K >> str;
	if(N == 1 && K == 1) {
		cout << "YES" << endl;
		cout << str << endl;
		return;
	}
	hashes.clear();
	long long cur = 0;
	long long cur2 = 0;
	long long running = 1;
	long long running2 = 1;
	for(int i = K - 2;i >= 0;--i) {
		cur += ('1' - str[i]) * running;
		cur2 += ('1' - str[i]) * running2;
		if(cur >= MOD) cur -= MOD;
		running = (running * base) % MOD;
		if(cur2 >= MOD2) cur2 -= MOD2;
		running2 = (running2 * base2) % MOD2;
	}
	for(int i = K - 1;i < N;++i) {
		if(i != K - 1) cur -= ('1' - str[i - K]) * running;
		if(cur < 0) cur += MOD;
		cur = (cur * base) % MOD;
		cur += ('1' - str[i]);
		if(cur >= MOD) cur -= MOD;

		if(i != K - 1) cur2 -= ('1' - str[i - K]) * running2;
		if(cur2 < 0) cur2 += MOD2;
		cur2 = (cur2 * base2) % MOD2;
		cur2 += ('1' - str[i]);
		if(cur2 >= MOD2) cur2 -= MOD2;
		hashes.insert({cur,cur2});
	}
	for(int i = 0;i < N;++i) {
		if(K < 30 && i >> K) break;
		long long curH = 0;
		long long curH2 = 0;
		running = 1;
		running2 = 1;
		for(int j = 0;j < 22;++j) {
			if(i & (1 << j)) {
				curH += running;
				curH2 += running2;
				if(curH >= MOD) curH -= MOD;
				if(curH2 >= MOD2) curH2 -= MOD2;
			}
			running = (running * base) % MOD;
			running2 = (running2 * base2) % MOD2;
		}
		if(hashes.find({curH,curH2}) == hashes.end()) {
			string ans = "";
			for(int j = 0;j < K;++j) {
				ans += '0';
			}
			for(int j = 0;j < 22;++j) {
				if(i & (1 << j)) {
					ans[K - 1 - j] = '1';
				}
			}
			cout << "YES" << endl;
			cout << ans << endl;
			return;
		}
	}
	cout << "NO" << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}