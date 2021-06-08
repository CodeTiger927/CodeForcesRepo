using namespace std;

#include <iostream>
#include <cstring>

#define MOD 1000000007

int N,M;

void solve() {
	cin >> N >> M;
	long long ans = 1;
	bool hasZero = false;
	for(int i = 0;i < N;++i) {
		string str;
		cin >> str;
		for(int j = 0;j < M;++j) {
			if(str[j] == '#') {
				ans = (ans << 1) % MOD;
			}else{
				hasZero = true;
			}
		}
	}
	cout << ans - 1 + hasZero << endl;
	return;
}

int main() {
	int T;
	cin >> T;
	while(T--) solve();
}